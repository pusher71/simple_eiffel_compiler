#ifndef COMPILERERROR_H
#define COMPILERERROR_H

#include <string>

#include "compile_error_codes.h"
#include "compile_error_codes.h"

class CompileError {
public:
    // ============== ATTRIBUTES ==============
private:
    CompileErrorCode    _errorCode;
    std::string         _errorMessage;

    // ============== OPERATIONS ==============
    // -------- creating --------
public:
    CompileError(CompileErrorCode errorCode, const std::string& errorMessage);

    // ------- attributes -------
public:
     CompileErrorCode errorCode();

    // -------- contract --------
public:
    std::string errorReason() const;
};

#endif // COMPILERERROR_H
