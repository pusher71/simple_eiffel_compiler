#include "semantic_error.h"

SemanticError::SemanticError(SemanticErrorCode errorCode, const std::string& errorMessage) :
    _errorCode(errorCode),
    _errorMessage(errorMessage)
{}

SemanticErrorCode SemanticError::errorCode() { return this->_errorCode; }

std::string SemanticError::errorReason() const {
    std::string result;

    switch (this->_errorCode) {
        case NO_ERROR:
            result += "NO ERROR";
            break;
        case CLASSES__DUPLICATE_CLASS_NAMES:
            result += "DUPLICATE CLASS NAMES";
            break;
        case CLASS__NAME_IS_RESERVED_WORD:
            result += "CLASS NAME IS RESERVED WORD";
            break;
    }

    if (this->_errorCode != NO_ERROR) {
        result += " :: " + this->_errorMessage;
    }

    return result;
}
