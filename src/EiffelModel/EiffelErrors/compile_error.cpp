#include "compile_error.h"

CompileError::CompileError(CompileErrorCode errorCode, const std::string& errorMessage) :
    _errorCode(errorCode),
    _errorMessage(errorMessage)
{}

CompileErrorCode CompileError::errorCode() { return this->_errorCode; }

std::string CompileError::errorReason() const {
    std::string result;

    switch (this->_errorCode) {
    }
    result += " :: " + this->_errorMessage;

    return result;
}
