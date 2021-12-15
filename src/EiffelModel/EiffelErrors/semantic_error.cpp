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
    }
    result += " :: " + this->_errorMessage;

    return result;
}
