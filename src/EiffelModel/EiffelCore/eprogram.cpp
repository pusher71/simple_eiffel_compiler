#include "eprogram.h"
#include <iostream>

EProgram* EProgram::current;
std::vector<SemanticError> EProgram::semanticErrors;

EProgram::EProgram() {
}

EProgram* EProgram::create(const program_strct* programNode) {
    EProgram* result = new EProgram();
    EProgram::current = result;

    // Create classes with their fields and methods
    result->runSemanticStage_0(programNode);
    result->runSemanticStage_1();
    result->runSemanticStage_2();

    return result;
}

EClass* EProgram::getClassBy(const std::string& className) {
    return this->_classes[className];
}

void EProgram::runSemanticStage_0(const program_strct* programNode) {
    class_decl_seq_strct* classDeclSeqElem = programNode->class_decl_seq;
    while (classDeclSeqElem != NULL && EProgram::semanticErrors.empty()) {
        if (this->_classes.count(classDeclSeqElem->value->id_name) != 0) {
            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::CLASSES__DUPLICATE_CLASS_NAMES, classDeclSeqElem->value->id_name));
            break;
        }

        this->_classes[classDeclSeqElem->value->id_name] = EClass::create(classDeclSeqElem->value);
        classDeclSeqElem = classDeclSeqElem->next;
    }
}

void EProgram::runSemanticStage_1() {
}

void EProgram::runSemanticStage_2() {
}

bool EProgram::compileToJVM(const std::string& jvmFilepath) {
    for (auto& mapElem : this->_classes) {
        mapElem.second->compile();
    }

    return true;
}
