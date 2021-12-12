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
    this->runSemanticStage_0(programNode); // Create classes with their attributes and routines

    if (EProgram::semanticErrors.empty()) { this->runSemanticStage_1(); }   // Validate attributes and routines names and data types
    if (EProgram::semanticErrors.empty()) { this->runSemanticStage_2(); }   // Collect features information for each class
    if (EProgram::semanticErrors.empty()) { this->runSemanticStage_3(); }   // Examine locals and bodies of each method of user classes
    if (EProgram::semanticErrors.empty()) { this->runSemanticStage_4(); }   // Check that classes initializes their attributes

    std::cout << "END [SEMANTIC PART]" << std::endl << std::endl;
}

EClass* EProgram::getClassBy(const std::string& className) {
    auto resultIterator = this->_classes.find(className);
    return (resultIterator != this->_classes.end() ? resultIterator->second.get() : nullptr);
}

void EProgram::runSemanticStage_0(const program_strct* programNode) {
    std::cout << " - Start 1st semantic stage (define classes) ... ";

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

    if (EProgram::semanticErrors.empty())   { std::cout << "Done!" << std::endl; }
    else                                    { std::cout << "Failed!" << std::endl; }
}

void EProgram::runSemanticStage_1() {
    std::cout << " - Start 2nd semantic stage (validate types of components of classes) ... ";

    for (const auto& classInfo : this->_classes) {
        classInfo.second.get()->validateSelfFeatures();
    }

    if (EProgram::semanticErrors.empty())   { std::cout << "Done!" << std::endl; }
    else                                    { std::cout << "Failed!" << std::endl; }
}

void EProgram::runSemanticStage_2() {
    std::cout << " - Start 3rd semantic stage (resolve inheritance of classes) ... ";

    for (auto& classInfo : this->_classes) {
        classInfo.second.get()->setupAcceptableFeaturesTable();
    }

    if (EProgram::semanticErrors.empty())   { std::cout << "Done!" << std::endl; }
    else                                    { std::cout << "Failed!" << std::endl; }
}

void EProgram::runSemanticStage_3() {
    std::cout << " - Start 4th semantic stage () ... ";

    for (auto& classInfo : this->_classes) {
        EUserClass* userClass = dynamic_cast<EUserClass*>(classInfo.second.get());
        if (userClass) {
            userClass->resolveRoutines();
        }
    }

    if (EProgram::semanticErrors.empty())   { std::cout << "Done!" << std::endl; }
    else                                    { std::cout << "Failed!" << std::endl; }
}

void EProgram::runSemanticStage_4() {
    std::cout << " - Start 5th semantic stage () ... ";

    if (EProgram::semanticErrors.empty())   { std::cout << "Done!" << std::endl; }
    else                                    { std::cout << "Failed!" << std::endl; }
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
