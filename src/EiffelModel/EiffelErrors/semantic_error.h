#ifndef SEMANTICERROR_H
#define SEMANTICERROR_H

#include <string>

#include "semantic_error_codes.h"

class SemanticError
{
public:
    // ============== ATTRIBUTES ==============
private:
    SemanticErrorCode   _errorCode;
    std::string         _errorMessage;

    // ============== OPERATIONS ==============
    // -------- creating --------
public:
    SemanticError(SemanticErrorCode errorCode, const std::string& errorMessage);

    // ------- attributes -------
public:
     SemanticErrorCode errorCode();

    // -------- contract --------
public:
    std::string errorReason() const;
};

#endif // SEMANTICERROR_H
