#include "semantic_error.h"

SemanticError::SemanticError(SemanticErrorCode errorCode, const std::string& errorMessage) :
    _errorCode(errorCode),
    _errorMessage(errorMessage)
{}

SemanticErrorCode SemanticError::errorCode() { return this->_errorCode; }

std::string SemanticError::errorReason() const {
    std::string result;

    switch (this->_errorCode) {
        // First semantic stage error codes
        case CLASSES__NAME_CLASHES_WITH_OTHER_CLASS_NAME:
            result += "CLASS NAME CLASHES WITH NAME OF OTHER CLASS";
            break;

        // Second semantic stage error codes ...
        // ... Names clashing
        case FEATURES__NAME_CLASHES_WITH_CLASS_NAME:
            result += "FEATURE NAME CLASHES WITH CLASS NAME";
            break;
        case FEATURES__NAME_CLASHES_WITH_NAME_OF_SAME_CLASS_FEATURE:
            result += "FEATURE NAME CLASHES WITH NAME OF SAME CLASS FEATURE";
            break;

        case FEATURES__FORMAL_PARAM_NAME_CLASHES_WITH_CLASS_NAME:
            result += "FORMAL PARAMETER NAME CLASHES WITH NAME OF CLASS";
            break;
        case FEATURES__FORMAL_PARAM_NAME_CLASHES_WITH_NAME_OF_SELF_FEATURE:
            result += "FORMAL PARAMETER NAME CLASHES WITH NAME OF SELF FEATURE";
            break;
        case FEATURES__FORMAL_PARAM_NAME_CLASHES_WITH_NAME_OF_SAME_CLASS_FEATURE:
            result += "FORMAL PARAMETER NAME CLASHES WITH NAME OF SAME CLASS FEATURE";
            break;
        case FEATURES__FORMAL_PARAM_NAME_CLASHES_WITH_NAME_OF_OTHER_FORMAL_PARAM:
            result += "FORMAL PARAMETER NAME CLASHES WITH NAME OF OTHER FORMAL PARAMETER";
            break;

        case FEATURES__LOCAL_VAR_NAME_CLASHES_WITH_CLASS_NAME:
            result += "LOCAL VARIABLE NAME CLASHES WITH NAME OF CLASS";
            break;
        case FEATURES__LOCAL_VAR_NAME_CLASHES_WITH_NAME_OF_SELF_FEATURE:
            result += "LOCAL VARIABLE NAME CLASHES WITH NAME OF SELF FEATURE";
            break;
        case FEATURES__LOCAL_VAR_NAME_CLASHES_WITH_NAME_OF_SAME_CLASS_FEATURE:
            result += "LOCAL VARIABLE NAME CLASHES WITH NAME OF SAME CLASS FEATURE";
            break;
        case FEATURES__LOCAL_VAR_NAME_CLASHES_WITH_NAME_OF_FORMAL_PARAM:
            result += "LOCAL VARIABLE NAME CLASHES WITH NAME OF FORMAL PARAMETER";
            break;
        case FEATURES__LOCAL_VAR_NAME_CLASHES_WITH_NAME_OF_OTHER_LOCAL_VAR:
            result += "LOCAL VARIABLE NAME CLASHES WITH NAME OF OTHER LOCAL VARIABLE";
            break;

        // ... Invalid types
        case FEATURES__FEATURE_INVALID_TYPE:
            result += "TYPE OF FEATURE IS INVALID";
            break;
        case FEATURES__FORMAL_PARAM_INVALID_TYPE:
            result += "TYPE OF FORMAL PARAMETER IS INVALID";
            break;
        case FEATURES__LOCAL_VAR_INVALID_TYPE:
            result += "TYPE OF LOCAL VARIABLE IS INVALID";
            break;

        // Third semantic stage error codes ...
        // ... Global error codes
        case INHERITANCE__UNKNOWN_PARENT:
            result += "NAME OF UNKNOWN PARENT";
            break;
        case INHERITANCE__INHERIT_CYCLE:
            result += "INHERITANCE CYCLE";
            break;
        case FEATURES__NAME_CLASHES_WITH_NAME_OF_INHERITED_FEATURE:
            result += "FEATURE NAME CLASHES WITH NAME OF INHERITED FEATURE";
            break;

        // ... Rename error codes
        case INHERITANCE__RENAME_UKNOWN_FEATURE:
            result += "RENAME UKNOWN FEATURE";
            break;
        case INHERITANCE__TWO_OR_MORE_RENAMES_OF_SAME_FEATURE:
            result += "SEVERAL RENAMES OF ONE FEATURE";
            break;

        // ... Redefine error codes
        case INHERITANCE__REDEFINE_CLAUSE_FEATURE_DUPLICATED:
            result += "REDEFINE CLAUSE IS DUPLICATED";
            break;
        case INHERITANCE__REDEFINE_UNKNOWN_FEATURE:
            result += "REDEFINE UKNOWN FEATURE";
            break;
        case INHERITANCE__REDEFINE_WITHOUT_REDEFINING_IN_CLASS:
            result += "DON\'T REDEFINE FEATURE WHICH IS MARKED TO BE REDEFINED";
            break;
        case INHERITANCE__NONCONFORMING_REDEFINE:
            result += "NON-CONFORMING REDEFINE";
            break;

        // ... Select error codes
        case INHERITANCE__SELECT_CLAUSE_FEATURE_DUPLICATED:
            result += "SELECT CLAUSE IS DUPLICATED";
            break;
        case INHERITANCE__SELECT_UNKNOWN_FEATURE:
            result += "SELECT UKNOWN FEATURE";
            break;
        case INHERITANCE__IMPROPER_SELECT:
            result += "IMPROPER SELECT";
            break;
        case INHERITANCE__REPEATEDLY_INHERITED_FEATURE_VERSIONS_CONFLICT:
            result += "CONFLICT BETWEEN VERSIONS OF A REPEATEDLY INHERITED FEATURE";
            break;

        // ... Creators error codes
        case CREATORS__UNKNOWN_CREATOR:
            result += "NAME OF UNKNOWN CREATOR";
            break;
        case CREATORS__SEVERAL_CREATORS_WITH_SAME_NAME:
            result += "SEVERAL CREATORS WITH SAME NAME";
            break;
        case CREATORS__CREATOR_HAS_RETURN_VALUE:
            result += "CREATOR HAS RETURN VALUE";
            break;
        case CREATORS__ATTRIBUTE_IS_CREATOR:
            result += "ATTRIBUTE IS CREATOR";
            break;
        case CREATORS__MAIN_CLASS_WITHOUT_MAIN_FUNCTION:
            result += "MAIN CLASS WITHOUT MAIN FUNCTION";
            break;

        case PROGRAM__MAIN_CLASS_ISNT_SET:
            result += "MAIN CLASS ISN\'T SET";
            break;

        // Fourth semantic stage error codes ...
        // ... Create instruction
        case INSTR_CREATE__FIELD_OR_LOCAL_WITH_UNKNOWN_ID:
            result += "CREATE FIELD OR LOCAL VARIABLE WITH UNKNOWN ID";
            break;
        case INSTR_CREATE__CALL_REMOVED_DEFAULT_CREATOR:
            result += "CALL REMOVED DEFAULT CREATOR";
            break;
        case INSTR_CREATE__UNKNOWN_CREATOR:
            result += "CALL UNKNOWN CREATOR";
            break;

        // ... Assign instruction
        case INSTR_ASSIGN__FIELD_OR_LOCAL_WITH_UNKNOWN_ID:
            result += "ASSIGN TO FIELD OR LOCAL VARIABLE WITH UNKNOWN ID";
            break;
        case INSTR_ASSIGN__ROUTINE_ASSIGNMENT:
            result += "ASSIGN TO ROUTINE";
            break;
        case INSTR_ASSIGN__CANT_CAST_EXPR_TO_TYPE_OF_ATTRIBUTE:
            result += "CAN\'T CAST EXPR TO TYPE OF ATTRIBUTE";
            break;
        case INSTR_ASSIGN__CANT_CAST_EXPR_TO_TYPE_OF_LOCAL:
            result += "CAN\'T CAST EXPR TO TYPE OF LOCAL VARIABLE";
            break;

        // ... Expression as instruction
        case INSTR_AS_EXPR__INSTRUCTION_RETURNS_SOME_VALUE:
            result += "INSTRUCTION RETURNS SOME VALUE";
            break;

        case EXPR__METHOD_OR_VAR_CALL_WITH_UNKNOWN_ID:
            result += "CALL METHOD, FIELD OR INNER METHOD VARIABLE WITH UNKNOWN ID";
            break;
        case EXPR__SUBCALL_WITH_PRIMITIVE_TYPE_OR_VOID_OPERAND:
            result += "SUBCALL WITH PRIMITIVE TYPE OR VOID OPERAND";
            break;
        case EXPR__SUBCALL_WITH_NONPARENTHESIZED_CREATE_EXPR_OPERAND:
            result += "SUBCALL WITH NON-PARENTHESIZED CREATE EXPR AS OPERAND";
            break;
        case EXPR__CALL_INVALID_ARGUMENTS_COUNT:
            result += "CALL HAS IMPROPER ARGUMENTS COUNT";
            break;
        case EXPR__CALL_ATTRIBUTE_AS_ROUTINE:
            result += "CALL ATTRIBUTE AS ROUTINE";
            break;
        case EXPR__CALL_NONCONFORMING_ARGUMENTS_SEQUENCE:
            result += "CALL HAS NON-CONFORMING ARGUMENTS SEQUENCE";
            break;

        case EXPR__CALL_NONEXISTENT_PRECURSOR:
            result += "CALL NON-EXISTENT PRECURSOR";
            break;
        case EXPR__AMBIGIOUS_CALL_PRECURSOR:
            result += "AMBIGIOUS CALL PRECURSOR";
            break;
        case EXPR__CALL_PRECURSOR_OF_UNKNOWN_PARENT:
            result += "CALL PRECURSOR OF UNKNOWN PARENT";
            break;

        case EXPR__CALL_REMOVED_DEFAULT_CREATOR:
            result += "CALL REMOVED DEFAULT CREATOR METHOD IN CREATE EXPRESSION";
            break;
        case EXPR__CALL_UNKNOWN_CREATOR_METHOD:
            result += "CALL UNKNOWN CREATOR METHOD IN CREATE EXPRESSION";
            break;
        case EXPR__INVALID_TYPE_IN_CREATE_EXPR:
            result += "UNKNOWN TYPE IN CREATE EXPR";
            break;
    }
    result += " :: " + this->_errorMessage;

    return result;
}
