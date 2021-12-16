#include "eroutine.h"
#include "../EiffelCore/eprogram.h"

#include "../EiffelCore/EiffelClasses/euserclass.h"

ERoutine::ERoutine(const std::string& featureName, EUserClass* ownerClass, feature_decl_strct* featureDecl)
    : EFeature(featureName, ownerClass, featureDecl),
      _routineBody(featureDecl->routine_body),
      _current(EInnerVariable(0, EType(ownerClass->name())))
{
    // Add formal parameters as inner variables of routine
    this->_defineFormalParameters(featureDecl->feature_param_seq);

    // Add local variables as inner variables of routine
    this->_defineLocalVariables(featureDecl->local_variables);

    // Add "result" local variable
    if (this->_returnType != EType::voidType()) {
        short resultLocalIndex = this->_formalParameters.size() + this->_localVariables.size() + 1;
        this->_localVariables.insert({"result", EInnerVariable(resultLocalIndex, this->_returnType)});
    }
}

ERoutine::ERoutine(const std::string&                                   featureName,
                   const EClass*                                        ownerClass,
                   const EType&                                         returnType,
                   const std::vector<std::pair<std::string, EType>>&    formalParameters,
                   const std::vector<std::pair<std::string, EType>>&    localVariables)
    :   EFeature(featureName, ownerClass, returnType),
        _routineBody(nullptr),
        _current(EInnerVariable(0, EType(ownerClass->name())))
{
    // Add formal parameters
    short formalParamIndex = 1;

    for (const auto& formalParamInfo : formalParameters) {
        this->_formalParameters.insert({ formalParamInfo.first, EInnerVariable(formalParamIndex, EType(formalParamInfo.second)) });
        formalParamIndex++;
    }

    // Add local variables
    short localVarIndex = formalParamIndex;

    for (const auto& localVarInfo : localVariables) {
        this->_localVariables.insert({ localVarInfo.first, EInnerVariable(formalParamIndex, EType(localVarInfo.second)) });
        localVarIndex++;
    }
}

void ERoutine::_defineFormalParameters(const ids_with_type_seq_strct* formalParameters) {
    ids_with_type_seq_strct* formalParamsSeqElem = this->_node->feature_param_seq;
    short formalParamListIndex = 0;

    while (formalParamsSeqElem != NULL) {
        identifiers_comma_seq_strct* identifiersCommaSeqElem = formalParamsSeqElem->identifiers_comma_seq;

        while (identifiersCommaSeqElem != NULL) {
            short formalParamIndex = this->_formalParameters.size()+1;

            auto sameFormalParameterInfo = this->_formalParameters.find(identifiersCommaSeqElem->value);
            if (sameFormalParameterInfo == this->_formalParameters.end()) {
                this->_formalParameters.insert({ identifiersCommaSeqElem->value, EInnerVariable(formalParamIndex, EType(formalParamsSeqElem->type)) });
            }
            else {
                std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" ";
                errorMessage += ":: formal parameter <" + std::to_string(formalParamListIndex) + "> clashes ";
                errorMessage += "with other formal parameter <" + std::to_string(sameFormalParameterInfo->second.index() - 1) + ">";

                EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::FEATURES__FORMAL_PARAM_NAME_CLASHES_WITH_NAME_OF_OTHER_FORMAL_PARAM, errorMessage));
            }

            formalParamListIndex++;

            identifiersCommaSeqElem = identifiersCommaSeqElem->next;
        }

        formalParamsSeqElem = formalParamsSeqElem->next;
    }
}

void ERoutine::_defineLocalVariables(const ids_with_type_seq_strct* localVariables) {
    ids_with_type_seq_strct* localsSeqElem = this->_node->local_variables;
    short localVarListIndex = 0;

    while (localsSeqElem != NULL) {
        identifiers_comma_seq_strct* identifiersCommaSeqElem = localsSeqElem->identifiers_comma_seq;

        while (identifiersCommaSeqElem != NULL) {
            short localVarIndex = this->_formalParameters.size() + this->_localVariables.size() + 1;

            auto sameLocalVarInfo = this->_localVariables.find(identifiersCommaSeqElem->value);
            if (sameLocalVarInfo == this->_localVariables.end()) {
                this->_localVariables.insert({ identifiersCommaSeqElem->value, EInnerVariable(localVarIndex, EType(localsSeqElem->type)) });
            }
            else {
                std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" ";
                errorMessage += ":: local variable <" + std::to_string(localVarListIndex) + "> clashes ";
                errorMessage += "with other local variable <" + std::to_string(sameLocalVarInfo->second.index() - this->_formalParameters.size() - 1) + ">";

                EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::FEATURES__LOCAL_VAR_NAME_CLASHES_WITH_NAME_OF_OTHER_LOCAL_VAR, errorMessage));
            }

            localVarListIndex++;

            identifiersCommaSeqElem = identifiersCommaSeqElem->next;
        }

        localsSeqElem = localsSeqElem->next;
    }
}

ERoutine::~ERoutine() {}

EFeature::EFeatureType ERoutine::featureType() const { return efeature_routine; }

const EInnerVariable* ERoutine::getInnerVar(short index) const {
    if (index < 0 || index > this->_formalParameters.size() + this->_localVariables.size()) {
        return nullptr;
    }
    else if (index == 0) {
        return &this->_current;
    }
    else {
        EInnerVariable* result = nullptr;

        std::map<std::string, EInnerVariable> innerVariables(_formalParameters.begin(), _formalParameters.end());
        innerVariables.insert(this->_localVariables.begin(), this->_localVariables.end());

        for (const auto& innerVarInfo : innerVariables) {
            if (innerVarInfo.second.index() == index) {
                result = (EInnerVariable*)&innerVarInfo.second;
            }
        }

        return result;
    }
}

std::map<std::string, EInnerVariable> ERoutine::formalParameters() const { return this->_formalParameters; }

unsigned short ERoutine::formalParamsCount() const { return this->_formalParameters.size(); }

void ERoutine::validateDataTypes() {
    EFeature::validateDataTypes();

    this->_validateFormalParamDataTypes();
    this->_validateLocalVarDataTypes();
}

void ERoutine::_validateFormalParamDataTypes() const {
    // Validate formal parameters
    std::string invalidUserTypeName;
    for (const auto& formalParamInfo : this->_formalParameters) {
        // Validate data type
        invalidUserTypeName = "";

        if (!formalParamInfo.second.type().isUserDefinedSubtypeValid(invalidUserTypeName)) {
            std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" ";
            errorMessage += ":: no user defined subtype \"" + invalidUserTypeName + "\" ";
            errorMessage += "for formal parameter <" + std::to_string(formalParamInfo.second.index() - 1) + ">";

            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::FEATURES__FORMAL_PARAM_INVALID_TYPE, errorMessage));
        }
    }
}

void ERoutine::_validateLocalVarDataTypes() const {
    // Validate local variables
    std::string invalidUserTypeName;
    for (const auto& localVarInfo : this->_localVariables) {
        // Validate data type
        invalidUserTypeName = "";

        if (!localVarInfo.second.type().isUserDefinedSubtypeValid(invalidUserTypeName) && localVarInfo.first != "result") {
            std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" ";
            errorMessage += ":: no user defined subtype \"" + invalidUserTypeName + "\" ";
            errorMessage += "for local variable <" + std::to_string(localVarInfo.second.index() - this->_formalParameters.size() - 1) + ">";

            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::FEATURES__LOCAL_VAR_INVALID_TYPE, errorMessage));
        }
    }
}

void ERoutine::checkOnInnerVarsNameClashing() const {
    this->_checkOnFormalParamNameClashing();
    this->_checkOnLocalVarNameClashing();
}

void ERoutine::_checkOnFormalParamNameClashing() const {
    // Validate formal parameters
    std::string invalidUserTypeName;
    for (const auto& formalParamInfo : this->_formalParameters) {
        std::string formalParamName = formalParamInfo.first;

        // Validate on name clashing ...
        // ... With class
        if (EProgram::current->getClassBy(formalParamName) != nullptr) {
            std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" ";
            errorMessage += ":: formal parameter <" + std::to_string(formalParamInfo.second.index() - 1) + "> clashes ";
            errorMessage += "with class \"" + formalParamName + "\"";

            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::FEATURES__FORMAL_PARAM_NAME_CLASHES_WITH_CLASS_NAME, errorMessage));
        }

        // ... With self feature
        if (formalParamName == this->_name) {
            std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" ";
            errorMessage += ":: formal parameter <" + std::to_string(formalParamInfo.second.index() - 1) + "> clashes ";
            errorMessage += "with feature \"" + this->_ownerClassName + "::" + this->_name + "\"";

            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::FEATURES__FORMAL_PARAM_NAME_CLASHES_WITH_NAME_OF_SELF_FEATURE, errorMessage));
        }

        // ... With feature in the class features table
        for (const auto& featureMetaInfo : EProgram::current->getClassBy(this->_ownerClassName)->_featuresTable) {
            if (formalParamName == featureMetaInfo.finalName() && featureMetaInfo.finalName() != this->_name) {
                std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" ";
                errorMessage += ":: formal parameter <" + std::to_string(formalParamInfo.second.index() - 1) + "> clashes ";
                errorMessage += "with feature \"" + featureMetaInfo.finalName() + "\" of parent \"" + featureMetaInfo.parentClassName() + "\"";

                EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::FEATURES__FORMAL_PARAM_NAME_CLASHES_WITH_NAME_OF_SAME_CLASS_FEATURE, errorMessage));
            }
        }
    }
}

void ERoutine::_checkOnLocalVarNameClashing() const {
    // Validate local variables
    std::string invalidUserTypeName;
    for (const auto& localVarInfo : this->_localVariables) {
        std::string localVarName = localVarInfo.first;

        // Validate on name clashing ...
        // ... With class
        if (EProgram::current->getClassBy(localVarName) != nullptr) {
            std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" ";
            errorMessage += ":: local variable <" + std::to_string(localVarInfo.second.index() - this->_formalParameters.size() - 1) + "> clashes ";
            errorMessage += "with class \"" + localVarName + "\"";

            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::FEATURES__LOCAL_VAR_NAME_CLASHES_WITH_CLASS_NAME, errorMessage));
        }

        // ... With self feature
        if (localVarName == this->_name) {
            std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" ";
            errorMessage += ":: local variable <" + std::to_string(localVarInfo.second.index() - this->_formalParameters.size() - 1) + "> clashes ";
            errorMessage += "with feature \"" + this->_ownerClassName + "::" + this->_name + "\"";

            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::FEATURES__LOCAL_VAR_NAME_CLASHES_WITH_NAME_OF_SELF_FEATURE, errorMessage));
        }

        // ... With same class feature
        for (const auto& featureMetaInfo : EProgram::current->getClassBy(this->_ownerClassName)->_featuresTable) {
            if (localVarName == featureMetaInfo.finalName() && featureMetaInfo.finalName() != this->_name) {
                std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" ";
                errorMessage += ":: local variable <" + std::to_string(localVarInfo.second.index() - this->_formalParameters.size() - 1) + "> clashes ";
                errorMessage += "with feature \"" + featureMetaInfo.finalName() + "\" of parent \"" + featureMetaInfo.parentClassName() + "\"";

                EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::FEATURES__LOCAL_VAR_NAME_CLASHES_WITH_NAME_OF_SAME_CLASS_FEATURE, errorMessage));
            }
        }

        // ... With formal variable
        for (const auto& formalParamInfo : this->_formalParameters) {
            if (localVarInfo.first == formalParamInfo.first) {
                std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" ";
                errorMessage += ":: local variable <" + std::to_string(localVarInfo.second.index() - this->_formalParameters.size() - 1) + "> clashes ";
                errorMessage += "with formal parameter <" + std::to_string(formalParamInfo.second.index() - 1) + ">";

                EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::FEATURES__LOCAL_VAR_NAME_CLASHES_WITH_NAME_OF_FORMAL_PARAM, errorMessage));
            }
        }
    }
}

void ERoutine::resolveBody() {
    EUserClass* ownerClass = (EUserClass*)EProgram::current->getClassBy(this->_ownerClassName);

    instruction_seq_strct* instructionSeqElem = this->_routineBody;
    instructionSeqElem = instructionSeqElem->next; // First instruction is NULL instruction

    while (instructionSeqElem != NULL) {
        switch (instructionSeqElem->value->type) {
            case instruction_create:
                this->_resolveCreateInstruction(*ownerClass, instructionSeqElem);
                break;
            case instruction_assign:
                this->_resolveAssignInstruction(*ownerClass, instructionSeqElem);
                break;
            case instruction_if:
                this->_resolveIfInstruction(*ownerClass, instructionSeqElem);
                break;
            case instruction_loop:
                this->_resolveLoopInstruction(*ownerClass, instructionSeqElem);
                break;
            case instruction_expr:
                this->_resolveInstructionAsExpr(*ownerClass, instructionSeqElem);
                break;
        }

        instructionSeqElem = instructionSeqElem->next;
    }
}

void ERoutine::_resolveCreateInstruction(EUserClass& userClass, instruction_seq_strct* createInstruction) {
}

void ERoutine::_resolveAssignInstruction(EUserClass& userClass, instruction_seq_strct* assignInstruction) {
    // Resolve name of left variable
    // userClass._featuresTable.
}

void ERoutine::_resolveIfInstruction(EUserClass& userClass, instruction_seq_strct* ifInstruction) {
}

void ERoutine::_resolveLoopInstruction(EUserClass& userClass, instruction_seq_strct* loopInstruction) {
}

void ERoutine::_resolveInstructionAsExpr(EUserClass& userClass, instruction_seq_strct* instructionAsExpr) {
}

bool ERoutine::isConformingTo(const EFeature& other) const {
    bool result = false;

    ERoutine* otherRoutine = dynamic_cast<ERoutine*>((EFeature*)(&other));
    if (otherRoutine != nullptr) {
        if (this->_returnType.canCastTo(otherRoutine->_returnType) &&
            this->_returnType.isExpanded() == otherRoutine->_returnType.isExpanded())
        {
            bool areFormalParamsConforming = (this->_formalParameters.size() == otherRoutine->_formalParameters.size());

            for (int i=0; i<this->_formalParameters.size() && areFormalParamsConforming; i++) {
                areFormalParamsConforming &= this->getInnerVar(i+1)->type().canCastTo(otherRoutine->getInnerVar(i+1)->type());
                areFormalParamsConforming &= this->getInnerVar(i+1)->type().isExpanded() == otherRoutine->getInnerVar(i+1)->type().isExpanded();
            }

            result = areFormalParamsConforming;
        }
    }

    return result;
}

std::string ERoutine::descriptor() const {
    std::string result = "(";
    for (const auto& formalParamInfo : this->_formalParameters) {
        result += formalParamInfo.second.type().descriptor();
    }
    result += ")" + this->_returnType.descriptor();

    return result;
}

std::string ERoutine::toString() const {
    std::string result = EFeature::toString() + "(";

    // for (const auto& formalTypeInfo : this->_formalParameters) {
    for (int i=1; i<=this->_formalParameters.size(); i++) {
        result += this->getInnerVar(i)->type().toString() + ", ";
    }

    if (!this->_formalParameters.empty()) {
        result = result.substr(0, result.size()-2);
    }

    result += ")";

    return result;
}
