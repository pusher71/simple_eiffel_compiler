#include "elocalvariable.h"

ELocalVariable* ELocalVariable::create(const std::string& name, EType* type) {
    ELocalVariable* result = new ELocalVariable();
    result->_name = name;
    result->_type = type;

    return result;
}
