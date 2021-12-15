#include "eprogram.h"

#include <algorithm>
#include <filesystem>
#include <iostream>

#include "EiffelClasses/euserclass.h"
#include "EiffelClasses/eclassrtl.h"
#include "EiffelClasses/eclassany.h"
#include "EiffelClasses/eclassconsoleio.h"

EProgram* EProgram::current;
std::vector<SemanticError> EProgram::semanticErrors;
std::vector<CompileError> EProgram::compileErrors;

EProgram::EProgram() {}

EProgram::EProgram(const program_strct* programNode) {
    EProgram::current = this;

    std::cout << "START [SEMANTIC PART]" << std::endl;

    // Start semantic analysis stages ...
    // ... STAGE 0 : Create classes with their attributes and routines
    if (EProgram::semanticErrors.empty()) {
        std::cout << " - Start semantic stage 0 (define classes) ... ";
        this->runSemanticStage_0(programNode);

        if (EProgram::semanticErrors.empty())   { std::cout << "Done!" << std::endl; }
        else                                    { std::cout << "Failed!" << std::endl; }
    }

    // ... STAGE 1 : Validate attributes and routines names and data types
    if (EProgram::semanticErrors.empty()) {
        std::cout << " - Start semantic stage 1 (validate classes components) ... ";
        this->runSemanticStage_1();

        if (EProgram::semanticErrors.empty())   { std::cout << "Done!" << std::endl; }
        else                                    { std::cout << "Failed!" << std::endl; }
    }

    // ... STAGE 2 : Collect features information for each class
    if (EProgram::semanticErrors.empty()) {
        std::cout << " - Start semantic stage 2 (resolve inheritance of classes) ... ";
        this->runSemanticStage_2();

        if (EProgram::semanticErrors.empty())   { std::cout << "Done!" << std::endl; }
        else                                    { std::cout << "Failed!" << std::endl; }
    }

    // ... STAGE 3 : Examine locals and bodies of each method of user classes
    if (EProgram::semanticErrors.empty()) {
        std::cout << " - Start semantic stage 3 (resolve routine bodies of user classes) ... ";
        this->runSemanticStage_3();

        if (EProgram::semanticErrors.empty())   { std::cout << "Done!" << std::endl; }
        else                                    { std::cout << "Failed!" << std::endl; }
    }

    // ... STAGE 4 : Check that classes initializes their attributes
    if (EProgram::semanticErrors.empty()) {
        std::cout << " - Start semantic stage 4 (check attributes initialization) ... ";
        this->runSemanticStage_4();

        if (EProgram::semanticErrors.empty())   { std::cout << "Done!" << std::endl; }
        else                                    { std::cout << "Failed!" << std::endl; }
    }

    std::cout << "END [SEMANTIC PART]" << std::endl << std::endl;
}

EClass* EProgram::getClassBy(const std::string& className) {
    auto resultIterator = this->_classes.find(className);
    return (resultIterator != this->_classes.end() ? resultIterator->second.get() : nullptr);
}

std::vector<EClass*> EProgram::classes() const {
    std::vector<EClass*> result;
    for (const auto& classInfo : this->_classes) {
        result.push_back(classInfo.second.get());
    }

    return result;
}

void EProgram::runSemanticStage_0(const program_strct* programNode) {
    // Add RTL classes
    EClassANY classANY              = EClassANY();
    EClassCONSOLEIO classCONSOLEIO  = EClassCONSOLEIO();

    this->_classes[classANY.name()] = std::make_shared<EClassANY>(classANY);
    this->_classes[classCONSOLEIO.name()] = std::make_shared<EClassCONSOLEIO>(classCONSOLEIO);

    // Add user classes
    class_decl_seq_strct* classDeclSeqElem = programNode->class_decl_seq;
    while (classDeclSeqElem != NULL && EProgram::semanticErrors.empty()) {
        if (this->_classes.count(classDeclSeqElem->value->id_name) != 0) {
            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::CLASSES__NAME_CLASHES_WITH_OTHER_CLASS_NAME, std::string("class \"") + classDeclSeqElem->value->id_name + "\""));
            break;
        }

        this->_classes[classDeclSeqElem->value->id_name] = std::make_shared<EUserClass>(EUserClass(classDeclSeqElem->value));
        classDeclSeqElem = classDeclSeqElem->next;
    }

}

void EProgram::runSemanticStage_1() {
    for (const auto& classInfo : this->_classes) {
        classInfo.second.get()->validateSelfFeatures();
        classInfo.second.get()->checkThatAllParentsAreExist();

        EUserClass* userClass = dynamic_cast<EUserClass*>(classInfo.second.get());
        if (userClass) {
            userClass->fillConstantTableWithSelfFeatures();
        }
    }
}

void EProgram::runSemanticStage_2() {
    for (auto& classInfo : this->_classes) {
        classInfo.second.get()->setupFeaturesTable();
        classInfo.second.get()->setupCreators();

        EUserClass* userClass = dynamic_cast<EUserClass*>(classInfo.second.get());
        if (userClass) {
            userClass->addFeaturesTableInfoToConstantTable();
        }
    }
}

void EProgram::runSemanticStage_3() {
    for (auto& classInfo : this->_classes) {
        EUserClass* userClass = dynamic_cast<EUserClass*>(classInfo.second.get());
        if (userClass) {
            userClass->resolveRoutines();
        }
    }
}

void EProgram::runSemanticStage_4() {
    for (auto& classInfo : this->_classes) {
        EUserClass* userClass = dynamic_cast<EUserClass*>(classInfo.second.get());
        if (userClass) {
            userClass->resolveRoutines();
        }
    }
}

bool EProgram::compileToJVM(const std::string& jvmFilepath) {
    std::cout << "START [COMPILATION PART]" << std::endl;

    // Create output directory
    std::string outputDirectoryPath = "out";
    std::filesystem::create_directory(outputDirectoryPath);

    for (auto& classInfo : this->_classes) {
        EUserClass* userClass = dynamic_cast<EUserClass*>(classInfo.second.get());
        if (userClass) {
            std::cout << " - Compiling class \"" << userClass->name() << "\" ... ";

            userClass->compile(outputDirectoryPath);

            if (EProgram::compileErrors.empty())    { std::cout << "Done!" << std::endl; }
            else                                    { std::cout << "Failed!" << std::endl; }
        }
    }

    std::cout << "END [COMPILATION PART]" << std::endl;

    return true;
}
