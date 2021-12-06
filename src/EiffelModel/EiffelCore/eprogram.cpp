#include "eprogram.h"
#include <algorithm>

#include <iostream>

EProgram* EProgram::current;
std::vector<SemanticError> EProgram::semanticErrors;

EProgram::EProgram() {
}

EProgram* EProgram::create(const program_strct* programNode) {
    EProgram* result = new EProgram();
    EProgram::current = result;

    result->runSemanticStage_0(programNode);    // Create classes with their attributes and routines

    if (EProgram::semanticErrors.empty()) { result->runSemanticStage_1(); } // Validate attributes and routines names and data types
    if (EProgram::semanticErrors.empty()) { result->runSemanticStage_2(); } // Collect features information for each class
    if (EProgram::semanticErrors.empty()) { result->runSemanticStage_3(); } // Examine locals and bodies of each method of user classes

    return result;
}

EClass* EProgram::getClassBy(const std::string& className) {
    auto resultIterator = this->_classes.find(className);
    return (resultIterator != this->_classes.end() ? &resultIterator->second : nullptr);
}

void EProgram::runSemanticStage_0(const program_strct* programNode) {
    // Add RTL classes

    // Add user classes
    class_decl_seq_strct* classDeclSeqElem = programNode->class_decl_seq;
    while (classDeclSeqElem != NULL && EProgram::semanticErrors.empty()) {
        if (this->_classes.count(classDeclSeqElem->value->id_name) != 0) {
            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::CLASSES__NAME_CLASHES_WITH_USER_CLASS_NAME, classDeclSeqElem->value->id_name));
            break;
        }

        this->_classes.insert(std::pair(classDeclSeqElem->value->id_name, EClass(classDeclSeqElem->value)));
        classDeclSeqElem = classDeclSeqElem->next;
    }
}

void EProgram::runSemanticStage_1() {
    for (const auto& classInfo : this->_classes) {
        for (const auto& featureInfo : classInfo.second.features()) {
            featureInfo.second.get()->validate();
        }
    }
}

void EProgram::runSemanticStage_2() {
    for (auto& classInfo : this->_classes) {
        classInfo.second.setupAcceptableFeaturesTable();
    }
}

void EProgram::runSemanticStage_3() {
}

bool EProgram::compileToJVM(const std::string& jvmFilepath) {
    for (auto& mapElem : this->_classes) {
        mapElem.second.compile();
    }

    return true;
}
