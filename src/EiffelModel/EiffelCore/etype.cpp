#include "etype.h"
#include "eprogram.h"
#include "EiffelClasses/eclassany.h"

extern "C" {
    struct type_strct* create_type(unsigned int         node_index,
                                   enum type_enum       type,
                                   char*                id_name,
                                   struct type_strct*   arrayelem_type);
}

EType::EType(type_strct* type)
    : _type(type)
{}

EType::EType(const std::string& className) {
    char* className_cstr = new char[className.size()+1];
    strcpy(className_cstr, className.c_str());

    this->_type = create_type(-1, dtype_user_defined, className_cstr, NULL);
}

EType EType::voidType()     { return nullptr; }
EType EType::boolType()     { return EType(create_type(-1, dtype_boolean, nullptr, NULL)); }
EType EType::intType()      { return EType(create_type(-1, dtype_integer, nullptr, NULL)); }
EType EType::charType()     { return EType(create_type(-1, dtype_character, nullptr, NULL)); }
EType EType::stringType()   { return EType(create_type(-1, dtype_string, nullptr, NULL)); }

bool EType::isUserDefinedSubtypeValid(std::string& outputInvalidUserTypeName) const {
    bool result = true;
    outputInvalidUserTypeName = "";

    // Move to the lowest type if initial type is a multidimensional array
    type_strct* typeLevel = this->_type;
    while (typeLevel->type == dtype_array) {
        typeLevel = typeLevel->arrayelem_type;
    }

    // Validate type if it is user defined
    if (typeLevel->type == dtype_user_defined) {
        if (EProgram::current->getClassBy(typeLevel->id_name) == nullptr) {
            result = false;
            outputInvalidUserTypeName = typeLevel->id_name;
        }
    }

    return result;
}

std::string EType::descriptor() const {
    std::string result;

    if (this->_type == nullptr) { return "V"; }

    type_strct* typeLevel = this->_type;
    while (typeLevel->type == dtype_array) {
        result += "[";
        typeLevel = typeLevel->arrayelem_type;
    }

    EClass* classInfo = nullptr;

    if (typeLevel->type == dtype_user_defined) {
        classInfo = EProgram::current->getClassBy(typeLevel->id_name);
    }

    switch (typeLevel->type) {
        case dtype_boolean:         result += "Z"; break;
        case dtype_character:       result += "C"; break;
        case dtype_integer:         result += "I"; break;
        case dtype_natural:         result += "I"; break;
        case dtype_string:          result += "L" + EClass::javaStringFullName() + ";"; break;
        case dtype_user_defined:    result += "L" + classInfo->fullName() + ";"; break;

        default: break;
    }

    return result;
}

bool EType::isExpanded() const {
    bool result = *this == EType::voidType() ||
                  (this->_type->type == dtype_boolean) ||
                  (this->_type->type == dtype_integer) ||
                  (this->_type->type == dtype_natural) ||
                  (this->_type->type == dtype_character);

    return result;
}

bool EType::operator==(const EType& other) const {
    bool result = false;

    if (other._type == nullptr) {
        return (this->_type == nullptr);
    }
    else if (this->_type == nullptr) {
        return (other._type == nullptr);
    }

    // Convert first type to its the lowest array element type If first type is a multidimensional array
    type_strct* firstTypeArrElemType = this->_type;
    short firstTypeArrLevel = 0;

    while (firstTypeArrElemType->type == dtype_array) {
        firstTypeArrElemType = firstTypeArrElemType->arrayelem_type;
        firstTypeArrLevel++;
    }

    // Convert second type to its the lowest array element type If second type is a multidimensional array
    type_strct* secondTypeArrElemType = other._type;
    short secondTypeArrLevel = 0;

    while (secondTypeArrElemType->type == dtype_array) {
        secondTypeArrElemType = secondTypeArrElemType->arrayelem_type;
        secondTypeArrLevel++;
    }

    // Compare got types
    if (firstTypeArrElemType->type == secondTypeArrElemType->type && firstTypeArrLevel == secondTypeArrLevel) {
        if (firstTypeArrElemType->type == dtype_user_defined && std::string(firstTypeArrElemType->id_name) == std::string(secondTypeArrElemType->id_name)) {
            result = true;
        }
    }

    return result;
}

bool EType::operator!=(const EType& other) const { return !(*this == other); }

bool EType::canCastTo(const EType& other) const {
    if (*this == other) {
        return true;
    }
    else if (*this == EType::voidType() || other == EType::voidType()) {
        return false;
    }

    // Convert first type to its the lowest array element type If first type is a multidimensional array
    type_strct* firstTypeArrElemType = this->_type;
    short firstTypeArrLevel = 0;

    while (firstTypeArrElemType->type == dtype_array) {
        firstTypeArrElemType = firstTypeArrElemType->arrayelem_type;
        firstTypeArrLevel++;
    }

    // Convert second type to its the lowest array element type If second type is a multidimensional array
    type_strct* secondTypeArrElemType = other._type;
    short secondTypeArrLevel = 0;

    while (secondTypeArrElemType->type == dtype_array) {
        secondTypeArrElemType = secondTypeArrElemType->arrayelem_type;
        secondTypeArrLevel++;
    }

    // Compare got types
    if (secondTypeArrElemType->type == dtype_user_defined && std::string(secondTypeArrElemType->id_name) == EClassANY::classRTLname() && firstTypeArrLevel >= secondTypeArrLevel) {
        return true;
    }

    if (secondTypeArrElemType->type == dtype_user_defined &&
        firstTypeArrElemType->type == dtype_user_defined &&
        firstTypeArrLevel == secondTypeArrLevel &&
        EProgram::current->getClassBy(firstTypeArrElemType->id_name)->isDescendantTo(EProgram::current->getClassBy(secondTypeArrElemType->id_name)))
    {
        return true;
    }

    return false;
}

std::string EType::toString() const {
    std::string result;

    if (this->_type == nullptr) { return "V"; }

    type_strct* typeLevel = this->_type;
    while (typeLevel->type == dtype_array) {
        result += "[]";
        typeLevel = typeLevel->arrayelem_type;
    }

    switch (typeLevel->type) {
        case dtype_boolean:         result = "bool" + result; break;
        case dtype_character:       result = "char" + result; break;
        case dtype_integer:         result = "int" + result; break;
        case dtype_natural:         result = "nat" + result; break;
        case dtype_string:          result = "str" + result; break;
        case dtype_user_defined:    result = std::string(typeLevel->id_name) + result; break;

        default: break;
    }

    return result;
}
