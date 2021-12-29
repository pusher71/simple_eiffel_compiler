#include "eroutine.h"
#include "eattribute.h"
#include "../EiffelCore/etype.h"
#include "../EiffelCore/eprogram.h"

#include "../EiffelCore/eclass.h"
#include "../EiffelCore/EiffelClasses/euserclass.h"
#include "../EiffelCore/EiffelClasses/eclassrtl.h"

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
    if (this->_returnType != EType::noType()) {
        short resultLocalIndex = this->_formalParameters.size() + this->_localVariables.size() + 1;
        this->_localVariables.insert({"RESULT", EInnerVariable(resultLocalIndex, this->_returnType)});
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

        if (!localVarInfo.second.type().isUserDefinedSubtypeValid(invalidUserTypeName) && localVarInfo.first != "RESULT") {
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

    // Resolve local variables
    for (const auto& localVarInfo : this->_localVariables) {
        EClass* localVarTypeClassInfo = EProgram::current->getClassBy(localVarInfo.second.type().firstElemClassName());
        ownerClass->constants().appendMethodRefStr(localVarTypeClassInfo->fullName(), "<init>", "()V");
    }

    // Resolve routine body instructions
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
            this->_instrInfo[createInstruction].fieldRef_constLink = userClass._constants.appendFieldRefStr(ownerClassFullName, attributeMetaInfo->finalName(), "L" + EClass::javaObjectFullName() + ";");

            fieldOrLocalOwnerClassInfo = EProgram::current->getClassBy( attributeMetaInfo->implementation()->returnType().firstElemClassName() );
        }
    }

    if (fieldOrLocalOwnerClassInfo == nullptr) {
        for (const auto& localVar : this->_localVariables) {
            if (localVar.first == createInstruction->first_id_name) {
                this->_instrInfo[createInstruction].localVarNumber = localVar.second.index();
                const auto& createdVarType = EType(localVar.second.type());

                fieldOrLocalOwnerClassInfo = EProgram::current->getClassBy( localVar.second.type().firstElemClassName() );
            }
        }
    }

    if (fieldOrLocalOwnerClassInfo != nullptr) {
        this->_instrInfo[createInstruction].constClass_constLink = userClass._constants.appendConstClass( userClass._constants.appendUtf8(fieldOrLocalOwnerClassInfo->fullName()) );
        this->_instrInfo[createInstruction].ownerClassFullName = fieldOrLocalOwnerClassInfo->fullName();

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
            this->_resolveCallArguments(userClass, creatorInfo->second, createInstruction->argument_seq, 0);
            this->_instrInfo[createInstruction].creatorMethodRef_constLink = userClass._constants.appendMethodRefStr(fieldOrLocalOwnerClassInfo->fullName(), createInstruction->second_id_name, creatorInfo->second->descriptor());
        }
    }
}

void ERoutine::_resolveAssignInstruction(EUserClass& userClass, instruction_strct* assignInstruction) {
    // Resolve name of left variable
    this->_resolveExpr(userClass, assignInstruction->assign_expr);

    if (!EProgram::current->semanticErrors.empty()) { return; }

    // Resolve variable of creation
    const EClass* fieldOrLocalOwnerClassInfo = nullptr;

    for (const auto& attributeMetaInfo : userClass.attributesMetaInfo()) {
        if (attributeMetaInfo->finalName() == assignInstruction->first_id_name) {
            if (this->_exprInfo.at(assignInstruction->assign_expr).resultType.canCastTo( attributeMetaInfo->implementation()->returnType() )) {
                std::string ownerClassFullName = EProgram::current->getClassBy(this->ownerClassName())->fullName();
                this->_instrInfo[assignInstruction].fieldRef_constLink = userClass._constants.appendFieldRefStr(ownerClassFullName, attributeMetaInfo->finalName(), "L" + EClass::javaObjectFullName() + ";");

                fieldOrLocalOwnerClassInfo = EProgram::current->getClassBy( attributeMetaInfo->implementation()->returnType().firstElemClassName() );
            }
            else {
                std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" :: field \"" + attributeMetaInfo->finalName() + "\"\n";
                errorMessage += std::string("type of field or local id - \"") + attributeMetaInfo->implementation()->returnType().toString() + "\"\n";
                errorMessage += std::string("type of expr              - \"") + this->_exprInfo.at(assignInstruction->assign_expr).resultType.toString() + "\"";

                EProgram::semanticErrors.push_back(SemanticError(INSTR_ASSIGN__CANT_CAST_EXPR_TO_TYPE_OF_LOCAL, errorMessage));
            }
        }
    }

    if (fieldOrLocalOwnerClassInfo == nullptr) {
        for (const auto& localVar : this->_localVariables) {
            if (localVar.first == assignInstruction->first_id_name) {
                if (this->_exprInfo.at(assignInstruction->assign_expr).resultType.canCastTo( EType(localVar.second.type()) )) {
                    this->_instrInfo[assignInstruction].localVarNumber = localVar.second.index();
                    const auto& createdVarType = EType(localVar.second.type());

                    fieldOrLocalOwnerClassInfo = EProgram::current->getClassBy( localVar.second.type().firstElemClassName() );
                }
                else {
                    std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" :: local variable \"" + localVar.first + "\"\n";
                    errorMessage += std::string("type of field or local id - \"") + EType(localVar.second.type()).toString() + "\"\n";
                    errorMessage += std::string("type of expr              - \"") + this->_exprInfo.at(assignInstruction->assign_expr).resultType.toString() + "\"";

                    EProgram::semanticErrors.push_back(SemanticError(INSTR_ASSIGN__CANT_CAST_EXPR_TO_TYPE_OF_LOCAL, errorMessage));
                }
            }
        }
    }

    if (fieldOrLocalOwnerClassInfo == nullptr) {
        std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" ";
        errorMessage += std::string(":: unknown id \"") + assignInstruction->first_id_name + "\"";

        EProgram::semanticErrors.push_back(SemanticError(INSTR_ASSIGN__FIELD_OR_LOCAL_WITH_UNKNOWN_ID, errorMessage));
    }
}

void ERoutine::_resolveIfInstruction(EUserClass& userClass, instruction_strct* ifInstruction) {

}

void ERoutine::_resolveLoopInstruction(EUserClass& userClass, instruction_strct* loopInstruction) {
}

void ERoutine::_resolveExprAsInstruction(EUserClass& userClass, instruction_strct* exprAsInstruction) {
    this->_resolveExpr(userClass, exprAsInstruction->instruction_as_expr);

    if (this->_exprInfo[exprAsInstruction->instruction_as_expr].resultType != EType::noType()) {
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
            this->_exprInfo[expr].resultType = EType::boolType();
            break;
        case expr_liter_int:
            this->_exprInfo[expr].resultType = EType::intType();

            intLiteral = expr->liter_int;
            if (intLiteral != expr->liter_int) { this->_exprInfo[expr].liter_constLink = userClass.constants().appendInteger(expr->liter_int); }

            break;
        case expr_liter_char:
            this->_exprInfo[expr].resultType = EType::charType();
            break;
        case expr_liter_str:
            this->_exprInfo[expr].resultType = EType::stringType();

            for (int i=0; i<chaarlen(expr->liter_str); i++) { stringLiteral += chaargetchr(expr->liter_str, i); }
            this->_exprInfo[expr].liter_constLink = userClass.constants().appendString( userClass.constants().appendUtf8(stringLiteral) );

            break;
        case expr_liter_void:
            this->_exprInfo[expr].resultType = EType::voidLiterType();
            break;

        case expr_current:
            this->_exprInfo[expr].resultType = EType::classType(userClass.name());
            break;

        case expr_call_selffeature: // TODO
            this->_resolveCallSelffeatureExpr(userClass, expr);
            break;
        case expr_call_precursor: // TODO
            this->_resolveCallPrecursorExpr(userClass, expr);
            break;
        case expr_subcall: // TODO
            this->_resolveCallSubcallExpr(userClass, expr);
            break;
        case expr_create: // TODO
            this->_resolveCreateExpr(userClass, expr);
            break;

        case expr_arrelem: // TODO
            this->_resolveArrElemExpr(userClass, expr);
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
            this->_exprInfo[expr].fieldRef_constLink = userClass._constants.appendFieldRefStr(ownerClassFullName, attributeMetaInfo->finalName(), attributeMetaInfo->implementation()->descriptor());

            this->_resolveCallArguments(userClass, attributeMetaInfo->implementation(), expr->argument_seq, expr->is_field_access);

            this->_exprInfo[expr].resultType = EType(attributeMetaInfo->implementation()->returnType());
            if (attributeMetaInfo->implementation()->returnType() != EType::noType()) {
                EClass* checkcastClassInfo = EProgram::current->getClassBy(attributeMetaInfo->implementation()->returnType().firstElemClassName());

                if (dynamic_cast<EUserClass*>(checkcastClassInfo)) {
                    this->_exprInfo[expr].constClass_constLink = userClass._constants.appendConstClass( userClass._constants.appendUtf8(checkcastClassInfo->fullName()) );
                }
            }

            isFound = true;
            break;
        }
    }

    if (!isFound) {
        for (const auto& routineMetaInfo : userClass.routinesMetaInfo()) {
            if (routineMetaInfo->finalName() == expr->method_id_name) {
                this->_exprInfo[expr].methodRef_constLink = userClass._constants.appendMethodRefStr(ownerClassFullName, routineMetaInfo->finalName(), routineMetaInfo->implementation()->descriptor());

                this->_resolveCallArguments(userClass, routineMetaInfo->implementation(), expr->argument_seq, expr->is_field_access);

                this->_exprInfo[expr].resultType = EType(routineMetaInfo->implementation()->returnType());
                if (routineMetaInfo->implementation()->returnType() != EType::noType()) {
                    EClass* checkcastClassInfo = EProgram::current->getClassBy(routineMetaInfo->implementation()->returnType().firstElemClassName());

                    if (dynamic_cast<EUserClass*>(checkcastClassInfo)) {
                        this->_exprInfo[expr].constClass_constLink = userClass._constants.appendConstClass( userClass._constants.appendUtf8(checkcastClassInfo->fullName()) );
                    }
                }

                isFound = true;
                break;
            }
        }
    }

    if (!isFound) {
        for (const auto& formalParam : this->_formalParameters) {
            if (formalParam.first == expr->method_id_name) {
                this->_exprInfo[expr].innerVarNumber = formalParam.second.index();

                EClass* ownerClassInfo = EProgram::current->getClassBy(formalParam.second.type().firstElemClassName());
                EAttribute innerVarInfo("", ownerClassInfo, formalParam.second.type());
                this->_resolveCallArguments(userClass, &innerVarInfo, expr->argument_seq, expr->is_field_access);

                this->_exprInfo[expr].resultType = EType(formalParam.second.type());
                if (formalParam.second.type() != EType::noType()) {
                    EClass* checkcastClassInfo = EProgram::current->getClassBy(formalParam.second.type().firstElemClassName());

                    if (dynamic_cast<EUserClass*>(checkcastClassInfo)) {
                        this->_exprInfo[expr].constClass_constLink = userClass._constants.appendConstClass( userClass._constants.appendUtf8(checkcastClassInfo->fullName()) );
                    }
                }

                isFound = true;
                break;
            }
        }
    }

    if (!isFound) {
        for (const auto& localVar : this->_localVariables) {
            if (localVar.first == expr->method_id_name) {
                this->_exprInfo[expr].innerVarNumber = localVar.second.index();

                EClass* ownerClassInfo = EProgram::current->getClassBy(localVar.second.type().firstElemClassName());
                EAttribute innerVarInfo("", ownerClassInfo, localVar.second.type());
                this->_resolveCallArguments(userClass, &innerVarInfo, expr->argument_seq, expr->is_field_access);

                this->_exprInfo[expr].resultType = EType(localVar.second.type());
                if (localVar.second.type() != EType::noType()) {
                    EClass* checkcastClassInfo = EProgram::current->getClassBy(localVar.second.type().firstElemClassName());

                    if (dynamic_cast<EUserClass*>(checkcastClassInfo)) {
                        this->_exprInfo[expr].constClass_constLink = userClass._constants.appendConstClass( userClass._constants.appendUtf8(checkcastClassInfo->fullName()) );
                    }
                }

                isFound = true;
                break;
            }
        }
    }

    if (!isFound) {
        std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" ";
        errorMessage += std::string(":: unknown id \"") + expr->method_id_name + "\" ";
        errorMessage += std::string("in class \"") + userClass.name() + "\"";

        EProgram::semanticErrors.push_back(SemanticError(EXPR__METHOD_OR_VAR_CALL_WITH_UNKNOWN_ID, errorMessage));
    }
}

void ERoutine::_resolveCallPrecursorExpr(EUserClass& userClass, expr_strct* expr) {
}

void ERoutine::_resolveCallSubcallExpr(EUserClass& userClass, expr_strct* expr) {
    // Check if left expression is create expression without brackets
    if (expr->expr_left->type == expr_create && !expr->expr_left->is_parenthesized) {
        std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" ";
        errorMessage += std::string(":: subcall id \"") + expr->method_id_name + "\"";

        EProgram::semanticErrors.push_back(SemanticError(EXPR__SUBCALL_WITH_NONPARENTHESIZED_CREATE_EXPR_OPERAND, errorMessage));
    }

    // Resolve call target
    this->_resolveExpr(userClass, expr->expr_left);

    if (!EProgram::semanticErrors.empty()) { return; }

    if (this->_exprInfo[expr->expr_left].resultType == EType::noType() || !this->_exprInfo[expr->expr_left].resultType.isClass()) {
        std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" ";
        errorMessage += std::string(":: subcall id \"") + expr->method_id_name + "\"";

        EProgram::semanticErrors.push_back(SemanticError(EXPR__SUBCALL_WITH_PRIMITIVE_TYPE_OR_VOID_OPERAND, errorMessage));
    }

    EClass* targetOwnerClassInfo = EProgram::current->getClassBy(this->_exprInfo[expr->expr_left].resultType.firstElemClassName());
    bool isFound = false;

    for (const auto& attributeMetaInfo : targetOwnerClassInfo->attributesMetaInfo()) {
        if (attributeMetaInfo->finalName() == expr->method_id_name) {
            if (dynamic_cast<EClassRTL*>(targetOwnerClassInfo) == nullptr) {
                this->_exprInfo[expr].methodRef_constLink = userClass._constants.appendMethodRefStr(targetOwnerClassInfo->fullName(), attributeMetaInfo->featureMark().first + ":" + attributeMetaInfo->featureMark().second, "(L" + EClass::javaObjectFullName() + ";)" + attributeMetaInfo->implementation()->descriptor());
            }
            else {
                this->_exprInfo[expr].isRTLcall = true;

                this->_exprInfo[expr].fieldRef_constLink = userClass._constants.appendFieldRefStr(targetOwnerClassInfo->fullName(), attributeMetaInfo->finalName(), attributeMetaInfo->implementation()->descriptor());
            }

            this->_resolveCallArguments(userClass, attributeMetaInfo->implementation(), expr->argument_seq, expr->is_field_access);

            this->_exprInfo[expr].resultType = EType(attributeMetaInfo->implementation()->returnType());
            if (attributeMetaInfo->implementation()->returnType() != EType::noType()) {
                EClass* checkcastClassInfo = EProgram::current->getClassBy(attributeMetaInfo->implementation()->returnType().firstElemClassName());

                if (dynamic_cast<EUserClass*>(checkcastClassInfo)) {
                    this->_exprInfo[expr].constClass_constLink = userClass._constants.appendConstClass( userClass._constants.appendUtf8(checkcastClassInfo->fullName()) );
                }
            }

            isFound = true;
            break;
        }
    }

    if (!isFound) {
        for (const auto& routineMetaInfo : targetOwnerClassInfo->routinesMetaInfo()) {
            if (routineMetaInfo->finalName() == expr->method_id_name) {
                if (dynamic_cast<EClassRTL*>(targetOwnerClassInfo) == nullptr) {
                    std::string polyMethodDescriptor = routineMetaInfo->implementation()->descriptor();
                    polyMethodDescriptor = "(L" + EClass::javaObjectFullName() + ";" + polyMethodDescriptor.substr(1, polyMethodDescriptor.size()-1);

                    this->_exprInfo[expr].methodRef_constLink = userClass._constants.appendMethodRefStr(targetOwnerClassInfo->fullName(), routineMetaInfo->featureMark().first + ":" + routineMetaInfo->featureMark().second, polyMethodDescriptor);
                }
                else {
                    this->_exprInfo[expr].isRTLcall = true;
                    this->_exprInfo[expr].methodRef_constLink = userClass._constants.appendMethodRefStr(targetOwnerClassInfo->fullName(), routineMetaInfo->finalName(), routineMetaInfo->implementation()->descriptor());
                }

                this->_resolveCallArguments(userClass, routineMetaInfo->implementation(), expr->argument_seq, expr->is_field_access);

                this->_exprInfo[expr].resultType = EType(routineMetaInfo->implementation()->returnType());
                if (routineMetaInfo->implementation()->returnType() != EType::noType()) {
                    EClass* checkcastClassInfo = EProgram::current->getClassBy(routineMetaInfo->implementation()->returnType().firstElemClassName());

                    if (dynamic_cast<EUserClass*>(checkcastClassInfo)) {
                        this->_exprInfo[expr].constClass_constLink = userClass._constants.appendConstClass( userClass._constants.appendUtf8(checkcastClassInfo->fullName()) );
                    }
                }

                isFound = true;
                break;
            }
        }
    }

    if (!isFound) {
        std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" ";
        errorMessage += std::string(":: unknown id \"") + expr->method_id_name + "\" ";
        errorMessage += std::string("in class \"") + this->_exprInfo[expr->expr_left].resultType.firstElemClassName() + "\"";

        EProgram::semanticErrors.push_back(SemanticError(EXPR__METHOD_OR_VAR_CALL_WITH_UNKNOWN_ID, errorMessage));
    }

    // Resolve arguments
    argument_seq_strct* argumentSeqElem = expr->argument_seq;
    while (argumentSeqElem != NULL) {
        this->_resolveExpr(userClass, argumentSeqElem->value);
        argumentSeqElem = argumentSeqElem->next;
    }
}

void ERoutine::_resolveCreateExpr(EUserClass& userClass, expr_strct* expr) {
    // Resolve variable of creation
    const EClass* createClassInfo = nullptr;

    this->_exprInfo[expr].resultType = EType(expr->create_type);
    std::string userDefinedSubtype;
    if (!this->_exprInfo[expr].resultType.isUserDefinedSubtypeValid(userDefinedSubtype)) {
        std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" :: no user defined subtype \"" + userDefinedSubtype + "\"";
        EProgram::semanticErrors.push_back(SemanticError(EXPR__INVALID_TYPE_IN_CREATE_EXPR, errorMessage));

        return;
    }

    createClassInfo = EProgram::current->getClassBy( this->_exprInfo[expr].resultType.firstElemClassName() );
    this->_exprInfo[expr].constClass_constLink = userClass._constants.appendConstClass( userClass._constants.appendUtf8(createClassInfo->fullName()) );

    userClass._constants.appendMethodRefStr(createClassInfo->fullName(), "<init>", "()V");

    this->_exprInfo[expr].ownerClassFullName = createClassInfo->fullName();

    if (expr->method_id_name == NULL && !createClassInfo->_creators.empty()) {
        std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" :: ";
        errorMessage += "creating entity of type \"" + this->_exprInfo[expr].resultType.toString() + "\"";

        EProgram::semanticErrors.push_back(SemanticError(EXPR__CALL_REMOVED_DEFAULT_CREATOR, errorMessage));
    }
    else if (expr->method_id_name != NULL) {
        const auto& creatorInfo = std::find_if(createClassInfo->_creators.begin(), createClassInfo->_creators.end(), [&](const auto& creatorInfo) { return (creatorInfo.first == expr->method_id_name); });

        if (creatorInfo == createClassInfo->_creators.end()) {
            std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" :: ";
            errorMessage += "creating entity of type \"" + this->_exprInfo[expr].resultType.toString() + "\" ";
            errorMessage += "with unknown creator with name \"" + std::string(expr->method_id_name) + "\"";

            EProgram::semanticErrors.push_back(SemanticError(EXPR__CALL_UNKNOWN_CREATOR_METHOD, errorMessage));
        }
        else {
            this->_resolveCallArguments(userClass, creatorInfo->second, expr->argument_seq, expr->is_field_access);
            this->_exprInfo[expr].methodRef_constLink = userClass._constants.appendMethodRefStr(createClassInfo->fullName(), expr->method_id_name, creatorInfo->second->descriptor());
        }
    }
}

void ERoutine::_resolveCallArguments(EUserClass& userClass, const EFeature* featureInfo, const argument_seq_strct* argumentSeq, bool isFieldAccess) {
    std::vector<std::pair<std::string, EType>> argumentsType;
    argument_seq_strct* argumentSeqElem = (argument_seq_strct*)argumentSeq;
    while (argumentSeqElem != NULL) {
        this->_resolveExpr(userClass, argumentSeqElem->value);
        argumentsType.push_back({ "", this->_exprInfo.at(argumentSeqElem->value).resultType });

        argumentSeqElem = argumentSeqElem->next;
    }

    if (dynamic_cast<const EAttribute*>(featureInfo)) {
        if (argumentsType.size() != 0) {
            std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" :: ";
            errorMessage += "call of attribute \"" + featureInfo->toString() + "\" ";
            errorMessage += "requires [0] arguments but got [" + std::to_string(argumentsType.size()) + "]";

            EProgram::semanticErrors.push_back(SemanticError(EXPR__CALL_INVALID_ARGUMENTS_COUNT, errorMessage));
        }
        else if (!isFieldAccess) {
            std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" :: ";
            errorMessage += "try to call attribute \"" + featureInfo->toString() + "\" like routine";

            EProgram::semanticErrors.push_back(SemanticError(EXPR__CALL_ATTRIBUTE_AS_ROUTINE, errorMessage));
        }

        return;
    }

    if (argumentsType.size() != ((ERoutine*)featureInfo)->_formalParameters.size()) {
        std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" :: ";
        errorMessage += "call of routine \"" + featureInfo->toString() + "\" ";
        errorMessage += "requires [" + std::to_string(((ERoutine*)featureInfo)->_formalParameters.size()) + "] arguments but got [" + std::to_string(argumentsType.size()) + "]";

        EProgram::semanticErrors.push_back(SemanticError(EXPR__CALL_INVALID_ARGUMENTS_COUNT, errorMessage));
    }
    else {
        EClass* ownerClass = EProgram::current->getClassBy(this->_ownerClassName);
        ERoutine creatorRoutineInfoWithArgsTypes(featureInfo->name(), ownerClass, featureInfo->returnType(), argumentsType, {});

        if (!creatorRoutineInfoWithArgsTypes.isConformingTo(*featureInfo, false)) {
            std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" :: ";
            errorMessage += "call of routine \"" + featureInfo->toString() + "\"\n";
            errorMessage += "declaration - " + featureInfo->toString() + "\n";
            errorMessage += "call        - " + creatorRoutineInfoWithArgsTypes.toString();

            EProgram::semanticErrors.push_back(SemanticError(EXPR__CALL_NONCONFORMING_ARGUMENTS_SEQUENCE, errorMessage));
        }
    }
}

void ERoutine::_resolveArrElemExpr(EUserClass& userClass, expr_strct* expr) {
}

bool ERoutine::isConformingTo(const EFeature& other, bool areDeclarationsCompared) const {
    bool result = false;

    ERoutine* otherRoutine = dynamic_cast<ERoutine*>((EFeature*)(&other));
    if (otherRoutine != nullptr) {
        if (this->_returnType.canCastTo(otherRoutine->_returnType) &&
            this->_returnType.isExpanded() == otherRoutine->_returnType.isExpanded())
        {
            bool areFormalParamsConforming = (this->_formalParameters.size() == otherRoutine->_formalParameters.size());

            for (int i=0; i<this->_formalParameters.size() && areFormalParamsConforming; i++) {
                areFormalParamsConforming &= this->getInnerVar(i+1)->type().canCastTo(otherRoutine->getInnerVar(i+1)->type());

                if (areDeclarationsCompared) {
                    areFormalParamsConforming &= this->getInnerVar(i+1)->type().isExpanded() == otherRoutine->getInnerVar(i+1)->type().isExpanded();
                }
            }

            result = areFormalParamsConforming;
        }
    }

    return result;
}

std::string ERoutine::descriptor() const {
    std::string result = "(";

    if ( dynamic_cast<EClassRTL*>(EProgram::current->getClassBy(this->_ownerClassName)) ) {
        for (const auto& formalParamInfo : this->_formalParameters) { result += formalParamInfo.second.type().descriptor(); }
        result += ")" + this->_returnType.descriptor();
    }
    else {
        for (const auto& formalParamInfo : this->_formalParameters) { result += "L" + EClass::javaObjectFullName() + ";"; }
        result += ")";

        if (this->_returnType == EType::noType())   { result += "V"; }
        else                                        { result += "L" + EClass::javaObjectFullName() + ";"; }
    }

    return result;
}

std::string ERoutine::toString() const {
    std::string result = EFeature::toString() + "(";

    for (int i=1; i<=this->_formalParameters.size(); i++) { result += this->getInnerVar(i)->type().toString() + ", "; }
    if (!this->_formalParameters.empty()) { result = result.substr(0, result.size()-2); }

    result += ")";

    return result;
}
