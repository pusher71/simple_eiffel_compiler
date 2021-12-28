#include "eprogram.h"

#include <algorithm>
#include <filesystem>
#include <iostream>

#include "EiffelClasses/euserclass.h"
#include "EiffelClasses/eclassrtl.h"
#include "EiffelClasses/RTLclasses/eclassany.h"
#include "EiffelClasses/RTLclasses/eclassconsoleio.h"
#include "EiffelClasses/RTLclasses/eclassboolean.h"
#include "EiffelClasses/RTLclasses/eclassinteger.h"
#include "EiffelClasses/RTLclasses/eclassnatural.h"
#include "EiffelClasses/RTLclasses/eclasscharacter.h"
#include "EiffelClasses/RTLclasses/eclassstring.h"
#include "EiffelClasses/RTLclasses/eclassarray.h"

EProgram*   EProgram::current = nullptr;

std::vector<SemanticError> EProgram::semanticErrors;
std::vector<CompileError> EProgram::compileErrors;

EUserClass* EProgram::mainClass = nullptr;
std::string EProgram::eiffelMainFunctionName() { return "MAKE"; }
std::string EProgram::javaMainFunctionName() { return "main"; }
std::string EProgram::javaMainFunctionDescriptor() { return "([Ljava/lang/String;)V"; }

std::string EProgram::javaDefaultConstructorName() { return "<init>"; }
std::string EProgram::javaDefaultConstructorDescriptor() { return "()V"; }

EProgram::EProgram() {}

EProgram::EProgram(const program_strct* programNode, const std::string& mainClassName) {
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
        this->runSemanticStage_3(mainClassName);

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
    this->_classes[EClassANY::classRTLname()] = std::make_shared<EClassANY>(EClassANY());
    this->_classes[EClassCONSOLEIO::classRTLname()] = std::make_shared<EClassCONSOLEIO>(EClassCONSOLEIO());

    this->_classes[EClassBOOLEAN::classRTLname()] = std::make_shared<EClassBOOLEAN>(EClassBOOLEAN());
    this->_classes[EClassINTEGER::classRTLname()] = std::make_shared<EClassINTEGER>(EClassINTEGER());
    this->_classes[EClassNATURAL::classRTLname()] = std::make_shared<EClassNATURAL>(EClassNATURAL());
    this->_classes[EClassCHARACTER::classRTLname()] = std::make_shared<EClassCHARACTER>(EClassCHARACTER());
    this->_classes[EClassSTRING::classRTLname()] = std::make_shared<EClassSTRING>(EClassSTRING());
    this->_classes[EClassARRAY::classRTLname()] = std::make_shared<EClassARRAY>(EClassARRAY());

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
    }
}

void EProgram::runSemanticStage_3(const std::string& mainClassName) {
    for (auto& classInfo : this->_classes) {
        EUserClass* userClass = dynamic_cast<EUserClass*>(classInfo.second.get());
        if (userClass) {
            userClass->addFeaturesTableInfoToConstantTable();
            userClass->resolveRoutines();

            if (userClass->name() == mainClassName) { userClass->becomeMainClass(); }
        }
    }

    if (EProgram::mainClass == nullptr) {
        std::string errorMessage = "Unknown class with name \"" + mainClassName + "\"";

        EProgram::semanticErrors.push_back(SemanticError(PROGRAM__MAIN_CLASS_ISNT_SET, errorMessage));
    }
}

void EProgram::runSemanticStage_4() {
    for (auto& classInfo : this->_classes) {
        EUserClass* userClass = dynamic_cast<EUserClass*>(classInfo.second.get());
        if (userClass) {
            // userClass->resolveRoutines();
        }
    }
}

bool EProgram::compileToJVM(const std::string& mainClassName, const std::string& compilerExeFilePath) {
    std::cout << "START [COMPILATION PART]" << std::endl;

    // Create output directory
    std::filesystem::path outputDirectoryPath = "out";
    std::filesystem::remove_all(outputDirectoryPath);
    std::filesystem::create_directory(outputDirectoryPath);

    // Create java manifest file
    std::filesystem::create_directory(outputDirectoryPath / "META-INF");
    std::ofstream manifestFile(outputDirectoryPath / "META-INF" / "MANIFEST.MF");

    manifestFile << "Manifest-Version: 1.0\n";
    manifestFile << "Created-By: 1.7.0_06 (Oracle Corporation)\n";
    manifestFile << "Main-Class: eiffel." + mainClassName + "\n";

    // Copy RTL classes to the output directory
    std::filesystem::path secToolsDirectoryPath = std::filesystem::path(compilerExeFilePath).parent_path() / "sec_tools";

    if (!std::filesystem::exists(secToolsDirectoryPath)) {
        std::cerr << "INPUT ERROR :: No \"sec_tools\" directory found near eiffel compiler executable." << std::endl;
        return false;
    }
    else if (!std::filesystem::exists(secToolsDirectoryPath / "to_out")) {
        std::cerr << "INPUT ERROR :: No \"to_out\" directory found in \"sec_tools\" directory near eiffel compiler executable." << std::endl;
        return false;
    }
    else if (!std::filesystem::exists(secToolsDirectoryPath / "to_out" / "rtl")) {
        std::cerr << "INPUT ERROR :: No \"rtl\" directory found in \"sec_tools/to_out\" directory near eiffel compiler executable." << std::endl;
        return false;
    }

    std::filesystem::path rtlDirectoryPath = secToolsDirectoryPath / "rtl";
    std::filesystem::copy(secToolsDirectoryPath / "to_out", outputDirectoryPath, std::filesystem::copy_options::recursive);

    // Compile each user class
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
