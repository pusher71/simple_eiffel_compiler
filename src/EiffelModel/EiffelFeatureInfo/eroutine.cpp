#include "eroutine.h"
#include "../EiffelCore/eprogram.h"

#include <iostream>

ERoutine::ERoutine(const std::string& featureName, const EClass* ownerClass, feature_decl_strct* featureDecl)
    : EFeature(featureName, ownerClass, featureDecl),
      _routineBody(featureDecl->routine_body),
      _current(EInnerVariable(0, EType(ownerClass->name())))
{
    // Add formal parameters as inner variables of routine
    this->_defineFormalParameters(featureDecl->feature_param_seq);

    // Add local variables as inner variables of routine
    this->_defineLocalVariables(featureDecl->local_variables);

    // Add "result" local variable
    if (this->_returnType != nullptr) {
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

void ERoutine::validate() const {
    EFeature::validate();

    this->_validateFormalParams();  // Validate formal parameters
    this->_validateLocalVars();     // Validate local variables
}

void ERoutine::_validateFormalParams() const {
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

        // ... With same class feature
        for (const auto& featureInfo : EProgram::current->getClassBy(this->_ownerClassName)->features()) {
            if (formalParamName == featureInfo.second->name() && featureInfo.second->name() != this->_name) {
                std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" ";
                errorMessage += ":: formal parameter <" + std::to_string(formalParamInfo.second.index() - 1) + "> clashes ";
                errorMessage += "with feature \"" + featureInfo.second->ownerClassName() + "::" + featureInfo.second->name() + "\"";

                EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::FEATURES__FORMAL_PARAM_NAME_CLASHES_WITH_NAME_OF_SAME_CLASS_FEATURE, errorMessage));
            }
        }

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

void ERoutine::_validateLocalVars() const {
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
        for (const auto& featureInfo : EProgram::current->getClassBy(this->_ownerClassName)->features()) {
            if (localVarName == featureInfo.second->name() && featureInfo.second->name() != this->_name) {
                std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" ";
                errorMessage += ":: local variable <" + std::to_string(localVarInfo.second.index() - this->_formalParameters.size() - 1) + "> clashes ";
                errorMessage += "with feature \"" + featureInfo.second->ownerClassName() + "::" + featureInfo.second->name() + "\"";

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

        // Validate data type
        invalidUserTypeName = "";

        if (!localVarInfo.second.type().isUserDefinedSubtypeValid(invalidUserTypeName)) {
            std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" ";
            errorMessage += ":: no user defined subtype \"" + invalidUserTypeName + "\" ";
            errorMessage += "for local variable <" + std::to_string(localVarInfo.second.index() - this->_formalParameters.size() - 1) + ">";

            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::FEATURES__LOCAL_VAR_INVALID_TYPE, errorMessage));
        }
    }
}
