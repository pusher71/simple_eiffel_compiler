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
        case CLASSES__NAME_CLASHES_WITH_USER_CLASS_NAME:
            result += "CLASS NAME CLASHES WITH NAME OF OTHER USER CLASS";
            break;
        case CLASSES__NAME_CLASHES_WITH_RTL_CLASS_NAME:
            result += "CLASS NAME CLASHES WITH NAME OF RTL CLASS";
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
    }
    result += " :: " + this->_errorMessage;

    return result;
}
