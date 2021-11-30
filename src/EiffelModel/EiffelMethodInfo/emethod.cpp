#include "emethod.h"
#include "../EiffelCore/eprogram.h"

#include <iostream>

EMethod* EMethod::create(const std::string& ownerClassName, feature_decl_strct* featureDecl) {
    EMethod* result = new EMethod();

    // Set routine body
    result->_routineBody = featureDecl->routine_body;

    return result;
}

bool EMethod::initSelf() {
    // Add "Current" as local parameter (same as "this" in Java)
    this->_locals.push_back( ELocalVariable::create("current", EProgram::current->getClassBy(this->_ownerClassName)->getType()) );

    // Add formal parameters
    ids_with_type_seq_strct* formalParamsSeqElem = this->_node->feature_param_seq;
    while (formalParamsSeqElem != NULL) {
        identifiers_comma_seq_strct* identifiersCommaSeqElem = formalParamsSeqElem->identifiers_comma_seq;

        while (identifiersCommaSeqElem != NULL) {
            this->_locals.push_back( ELocalVariable::create(identifiersCommaSeqElem->value, EType::create(formalParamsSeqElem->type)) );
            identifiersCommaSeqElem = identifiersCommaSeqElem->next;
        }

        formalParamsSeqElem = formalParamsSeqElem->next;
    }

    // Add local parameters
    ids_with_type_seq_strct* localsSeqElem = this->_node->local_variables;
    while (localsSeqElem != NULL) {
        identifiers_comma_seq_strct* identifiersCommaSeqElem = localsSeqElem->identifiers_comma_seq;

        while (identifiersCommaSeqElem != NULL) {
            this->_locals.push_back( ELocalVariable::create(identifiersCommaSeqElem->value, EType::create(localsSeqElem->type)) );
            identifiersCommaSeqElem = identifiersCommaSeqElem->next;
        }

        localsSeqElem = localsSeqElem->next;
    }

    return true;
}

std::string EMethod::name() { return this->_name; }
