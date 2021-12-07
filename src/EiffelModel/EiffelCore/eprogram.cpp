#include "eprogram.h"

#include <algorithm>
#include "euserclass.h"
#include "RTL/eclassrtl.h"
#include "RTL/eclassany.h"
#include "RTL/eclassconsoleio.h"

EProgram* EProgram::current;
std::vector<SemanticError> EProgram::semanticErrors;

EProgram::EProgram() {}

EProgram::EProgram(const program_strct* programNode) {
    EProgram::current = this;

    this->runSemanticStage_0(programNode); // Create classes with their attributes and routines

    if (EProgram::semanticErrors.empty()) { this->runSemanticStage_1(); }   // Validate attributes and routines names and data types
    if (EProgram::semanticErrors.empty()) { this->runSemanticStage_2(); }   // Collect features information for each class
    if (EProgram::semanticErrors.empty()) { this->runSemanticStage_3(); }   // Examine locals and bodies of each method of user classes
}

EClass* EProgram::getClassBy(const std::string& className) {
    auto resultIterator = this->_classes.find(className);
    return (resultIterator != this->_classes.end() ? resultIterator->second.get() : nullptr);
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
            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::CLASSES__NAME_CLASHES_WITH_USER_CLASS_NAME, classDeclSeqElem->value->id_name));
            break;
        }

        this->_classes[classDeclSeqElem->value->id_name] = std::make_shared<EUserClass>(EUserClass(classDeclSeqElem->value));
        classDeclSeqElem = classDeclSeqElem->next;
    }
}

void EProgram::runSemanticStage_1() {
    for (const auto& classInfo : this->_classes) {
        for (const auto& featureInfo : classInfo.second.get()->features()) {
            featureInfo.second.get()->validate();
        }
    }
}

void EProgram::runSemanticStage_2() {
    for (auto& classInfo : this->_classes) {
        classInfo.second.get()->setupAcceptableFeaturesTable();
    }
}

void EProgram::runSemanticStage_3() {
}

bool EProgram::compileToJVM(const std::string& jvmFilepath) {
    for (auto& mapElem : this->_classes) {
        EUserClass* userClass = dynamic_cast<EUserClass*>(mapElem.second.get());
        if (userClass) { userClass->compile(); }
    }

    return true;
}
