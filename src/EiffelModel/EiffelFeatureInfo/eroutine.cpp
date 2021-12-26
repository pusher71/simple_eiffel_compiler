#include "eroutine.h"
#include "eattribute.h"
#include "../EiffelCore/etype.h"
#include "../EiffelCore/eprogram.h"

#include "../EiffelCore/EiffelClasses/euserclass.h"

#include "../../flex/utilities/chararray_utilities.h"

extern "C" unsigned int curr_node_index;
extern "C" {
    struct type_strct* create_type(unsigned int         node_index,
                                   enum type_enum       type,
                                   char*                id_name,
                                   struct type_strct*   arrayelem_type);
}

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
        this->_resolveInstruction(*ownerClass, instructionSeqElem->value);
        instructionSeqElem = instructionSeqElem->next;
    }
}

void ERoutine::_resolveInstruction(EUserClass& userClass, instruction_strct* instruction) {
    switch (instruction->type) {
        case instruction_create:
            this->_resolveCreateInstruction(userClass, instruction);
            break;
        case instruction_assign:
            this->_resolveAssignInstruction(userClass, instruction);
            break;
        case instruction_if:
            this->_resolveIfInstruction(userClass, instruction);
            break;
        case instruction_loop:
            this->_resolveLoopInstruction(userClass, instruction);
            break;
        case instruction_expr:
            this->_resolveExprAsInstruction(userClass, instruction);
            break;
    }
}

void ERoutine::_resolveCreateInstruction(EUserClass& userClass, instruction_strct* createInstruction) {
    // Resolve variable of creation
    const EClass* fieldOrLocalOwnerClassInfo = nullptr;

    for (const auto& attributeMetaInfo : userClass.attributesMetaInfo()) {
        if (attributeMetaInfo->finalName() == createInstruction->first_id_name) {
            std::string ownerClassFullName = EProgram::current->getClassBy(this->ownerClassName())->fullName();
            createInstruction->field_ref = userClass._constants.appendFieldRefStr(ownerClassFullName, attributeMetaInfo->finalName(), attributeMetaInfo->implementation()->returnType().descriptor());

            fieldOrLocalOwnerClassInfo = EProgram::current->getClassBy( attributeMetaInfo->implementation()->returnType().firstElemClassName() );
        }
    }

    if (fieldOrLocalOwnerClassInfo == nullptr) {
        for (const auto& localVar : this->_localVariables) {
            if (localVar.first == createInstruction->first_id_name) {
                createInstruction->local_var_number = localVar.second.index();
                const auto& createdVarType = EType(localVar.second.type());

                fieldOrLocalOwnerClassInfo = EProgram::current->getClassBy( localVar.second.type().firstElemClassName() );
            }
        }
    }

    if (fieldOrLocalOwnerClassInfo != nullptr) {
        createInstruction->const_class = userClass._constants.appendConstClass( userClass._constants.appendUtf8(fieldOrLocalOwnerClassInfo->fullName()) );
        createInstruction->owner_class_full_name = new char[fieldOrLocalOwnerClassInfo->fullName().size()+1];
        strcpy(createInstruction->owner_class_full_name, fieldOrLocalOwnerClassInfo->fullName().c_str());

        userClass._constants.appendMethodRefStr(fieldOrLocalOwnerClassInfo->fullName(), "<init>", "()V");
    }

    if (fieldOrLocalOwnerClassInfo == nullptr) {
        std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" ";
        errorMessage += std::string(":: unknown id \"") + createInstruction->first_id_name + "\"";

        EProgram::semanticErrors.push_back(SemanticError(INSTR_CREATE__FIELD_OR_LOCAL_WITH_UNKNOWN_ID, errorMessage));
    }
    else if (createInstruction->second_id_name == NULL && !EProgram::current->getClassBy(fieldOrLocalOwnerClassInfo->name())->_creators.empty()) {
        std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" :: ";
        errorMessage += "field or local variable with name \"" + std::string(createInstruction->first_id_name) + "\" of class \"" + fieldOrLocalOwnerClassInfo->fullName() + "\"";

        EProgram::semanticErrors.push_back(SemanticError(INSTR_CREATE__CALL_REMOVED_DEFAULT_CREATOR, errorMessage));
    }
    else if (createInstruction->second_id_name != NULL) {
        const auto& creatorInfo = std::find_if(fieldOrLocalOwnerClassInfo->_creators.begin(), fieldOrLocalOwnerClassInfo->_creators.end(), [&](const auto& creatorInfo) { return (creatorInfo.first == createInstruction->second_id_name); });

        if (creatorInfo == fieldOrLocalOwnerClassInfo->_creators.end()) {
            std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" ";
            errorMessage += std::string(":: unknown id \"") + createInstruction->second_id_name + "\"";

            EProgram::semanticErrors.push_back(SemanticError(INSTR_CREATE__UNKNOWN_CREATOR, errorMessage));
        }
        else {
            createInstruction->creator_method_ref = userClass._constants.appendMethodRefStr(fieldOrLocalOwnerClassInfo->fullName(), createInstruction->second_id_name, creatorInfo->second->descriptor());
        }
    }
}

void ERoutine::_resolveAssignInstruction(EUserClass& userClass, instruction_strct* assignInstruction) {
    // Resolve name of left variable
    // userClass._featuresTable.
}

void ERoutine::_resolveIfInstruction(EUserClass& userClass, instruction_strct* ifInstruction) {

}

void ERoutine::_resolveLoopInstruction(EUserClass& userClass, instruction_strct* loopInstruction) {
}

void ERoutine::_resolveExprAsInstruction(EUserClass& userClass, instruction_strct* exprAsInstruction) {
    this->_resolveExpr(userClass, exprAsInstruction->instruction_as_expr);

    if (exprAsInstruction->instruction_as_expr->result_type != NULL) {
        std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\"";

        EProgram::semanticErrors.push_back(SemanticError(INSTR_AS_EXPR__INSTRUCTION_RETURNS_SOME_VALUE, errorMessage));
    }
}

void ERoutine::_resolveExpr(EUserClass& userClass, expr_strct* expr) {
    short intLiteral = 0;
    std::string stringLiteral = "";
    char* userClassName = nullptr;

    switch(expr->type) {
        case expr_liter_bool:
            expr->result_type = create_type(curr_node_index++, dtype_boolean, NULL, NULL);
            break;
        case expr_liter_int:
            expr->result_type = create_type(curr_node_index++, dtype_integer, NULL, NULL);

            intLiteral = expr->liter_int;
            if (intLiteral != expr->liter_int) { expr->constant_link = userClass.constants().appendInteger(expr->liter_int); }

            break;
        case expr_liter_char:
            expr->result_type = create_type(curr_node_index++, dtype_character, NULL, NULL);
            break;
        case expr_liter_str:
            expr->result_type = create_type(curr_node_index++, dtype_string, NULL, NULL);

            for (int i=0; i<chaarlen(expr->liter_str); i++) { stringLiteral += chaargetchr(expr->liter_str, i); }
            expr->constant_link = userClass.constants().appendString( userClass.constants().appendUtf8(stringLiteral) );

            break;
        case expr_liter_void:
            expr->result_type = create_type(curr_node_index++, dtype_void, NULL, NULL);
            break;

        case expr_current:
            userClassName = new char[userClass.name().size()+1];
            strcpy(userClassName, userClass.name().c_str());
            expr->result_type = create_type(curr_node_index++, dtype_user_defined, userClassName, NULL);

            break;
        case expr_call_selffeature:
            this->_resolveCallSelffeatureExpr(userClass, expr);
            break;
        case expr_call_precursor:
            this->_resolveCallPrecursorExpr(userClass, expr);
            break;
        case expr_subcall:
            this->_resolveCallSubcallExpr(userClass, expr);
            break;
        case expr_create:
            this->_resolveCreateExpr(userClass, expr);
            break;

        case expr_arrelem:
            break;
        case expr_plus:
            break;
        case expr_bminus:
            break;
        case expr_mul:
            break;
        case expr_idiv:
            break;
        case expr_uminus:
            break;

        case expr_less:
            break;
        case expr_great:
            break;
        case expr_less_equal:
            break;
        case expr_great_equal:
            break;
        case expr_equal:
            break;
        case expr_notequal:
            break;

        case expr_and:
            break;
        case expr_or:
            break;
        case expr_not:
            break;
        case expr_xor:
            break;
    }
}

void ERoutine::_resolveCallSelffeatureExpr(EUserClass& userClass, expr_strct* expr) {
    // Resolve call target
    bool isFound = false;
    std::string ownerClassFullName = EProgram::current->getClassBy(this->ownerClassName())->fullName();

    for (const auto& attributeMetaInfo : userClass.attributesMetaInfo()) {
        if (attributeMetaInfo->finalName() == expr->method_id_name) {
            expr->field_ref = userClass._constants.appendFieldRefStr(ownerClassFullName, attributeMetaInfo->finalName(), attributeMetaInfo->implementation()->returnType().descriptor());
            expr->result_type = attributeMetaInfo->implementation()->returnType().getRawTypeCopy();

            isFound = true;
            break;
        }
    }

    if (!isFound) {
        for (const auto& routineMetaInfo : userClass.routinesMetaInfo()) {
            if (routineMetaInfo->finalName() == expr->method_id_name) {
                expr->method_ref = userClass._constants.appendMethodRefStr(ownerClassFullName, routineMetaInfo->finalName(), routineMetaInfo->implementation()->descriptor());
                expr->result_type = routineMetaInfo->implementation()->returnType().getRawTypeCopy();

                isFound = true;
                break;
            }
        }
    }

    if (!isFound) {
        for (const auto& formalParam : this->_formalParameters) {
            if (formalParam.first == expr->method_id_name) {
                expr->inner_var_number = formalParam.second.index();
                expr->result_type = formalParam.second.type().getRawTypeCopy();

                isFound = true;
                break;
            }
        }
    }

    if (!isFound) {
        for (const auto& localVar : this->_localVariables) {
            if (localVar.first == expr->method_id_name) {
                expr->inner_var_number = localVar.second.index();
                expr->result_type = localVar.second.type().getRawTypeCopy();

                isFound = true;
                break;
            }
        }
    }

    if (!isFound) {
        std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" ";
        errorMessage += std::string(":: unknown id \"") + expr->method_id_name + "\" ";
        errorMessage += std::string("in class \"") + userClass.name() + "\"";

        EProgram::semanticErrors.push_back(SemanticError(INSTR_AS_EXPR__METHOD_OR_VAR_CALL_WITH_UNKNOWN_ID, errorMessage));
    }

    // Resolve arguments
    argument_seq_strct* argumentSeqElem = expr->argument_seq;
    while (argumentSeqElem != NULL) {
        this->_resolveExpr(userClass, argumentSeqElem->value);
        argumentSeqElem = argumentSeqElem->next;
    }
}

void ERoutine::_resolveCallPrecursorExpr(EUserClass& userClass, expr_strct* expr) {
}

void ERoutine::_resolveCallSubcallExpr(EUserClass& userClass, expr_strct* expr) {
    // Resolve call target
    this->_resolveExpr(userClass, expr->expr_left);

    if (expr->expr_left->result_type->id_name == NULL) {
        std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" ";
        errorMessage += std::string(":: subcall id \"") + expr->method_id_name + "\"";

        EProgram::semanticErrors.push_back(SemanticError(INSTR_AS_EXPR__SUBCALL_WITH_PRIMITIVE_TYPE_OPERAND, errorMessage));
    }

    EClass* targetOwnerClassInfo = EProgram::current->getClassBy(expr->expr_left->result_type->id_name);
    bool isFound = false;

    for (const auto& attributeMetaInfo : targetOwnerClassInfo->attributesMetaInfo()) {
        if (attributeMetaInfo->finalName() == expr->method_id_name) {
            expr->field_ref = userClass._constants.appendFieldRefStr(targetOwnerClassInfo->fullName(), attributeMetaInfo->finalName(), attributeMetaInfo->implementation()->returnType().descriptor());
            expr->result_type = attributeMetaInfo->implementation()->returnType().getRawTypeCopy();

            isFound = true;
            break;
        }
    }

    if (!isFound) {
        for (const auto& routineMetaInfo : targetOwnerClassInfo->routinesMetaInfo()) {
            if (routineMetaInfo->finalName() == expr->method_id_name) {
                expr->method_ref = userClass._constants.appendMethodRefStr(targetOwnerClassInfo->fullName(), routineMetaInfo->finalName(), routineMetaInfo->implementation()->descriptor());
                expr->result_type = routineMetaInfo->implementation()->returnType().getRawTypeCopy();

                isFound = true;
                break;
            }
        }
    }

    if (!isFound) {
        std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" ";
        errorMessage += std::string(":: unknown id \"") + expr->method_id_name + "\" ";
        errorMessage += std::string("in class \"") + expr->expr_left->result_type->id_name + "\"";

        EProgram::semanticErrors.push_back(SemanticError(INSTR_AS_EXPR__METHOD_OR_VAR_CALL_WITH_UNKNOWN_ID, errorMessage));
    }

    // Resolve arguments
    argument_seq_strct* argumentSeqElem = expr->argument_seq;
    while (argumentSeqElem != NULL) {
        this->_resolveExpr(userClass, argumentSeqElem->value);
        argumentSeqElem = argumentSeqElem->next;
    }
}

void ERoutine::_resolveCreateExpr(EUserClass& userClass, expr_strct* expr) {
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
