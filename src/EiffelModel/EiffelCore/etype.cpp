#include "etype.h"
#include "eprogram.h"
#include "EiffelClasses/RTLclasses/eclassany.h"
#include "EiffelClasses/RTLclasses/eclassboolean.h"
#include "EiffelClasses/RTLclasses/eclassinteger.h"
#include "EiffelClasses/RTLclasses/eclassnatural.h"
#include "EiffelClasses/RTLclasses/eclasscharacter.h"
#include "EiffelClasses/RTLclasses/eclassstring.h"
#include "EiffelClasses/RTLclasses/eclassarray.h"

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

EType EType::noType()           { return EType(nullptr); }
EType EType::voidLiterType()    { return EType(create_type(-1, dtype_void, NULL, NULL)); }

EType EType::boolType(bool isClass) {
    char* classNameStr = NULL;

    if (isClass) {
        std::string className = EClassBOOLEAN::classRTLname();

        classNameStr = new char[className.size() + 1];
        strcpy(classNameStr, className.c_str());
    }

    return EType(create_type(-1, dtype_boolean, classNameStr, NULL));
}

EType EType::intType(bool isClass) {
    char* classNameStr = NULL;

    if (isClass) {
        std::string className = EClassINTEGER::classRTLname();

        classNameStr = new char[className.size() + 1];
        strcpy(classNameStr, className.c_str());
    }

    return EType(create_type(-1, dtype_integer, classNameStr, NULL));
}

EType EType::naturalType(bool isClass) {
    char* classNameStr = NULL;

    if (isClass) {
        std::string className = EClassNATURAL::classRTLname();

        classNameStr = new char[className.size() + 1];
        strcpy(classNameStr, className.c_str());
    }

    return EType(create_type(-1, dtype_natural, classNameStr, NULL));
}

EType EType::charType(bool isClass) {
    char* classNameStr = NULL;

    if (isClass) {
        std::string className = EClassCHARACTER::classRTLname();

        classNameStr = new char[className.size() + 1];
        strcpy(classNameStr, className.c_str());
    }

    return EType(create_type(-1, dtype_character, classNameStr, NULL));
}

EType EType::stringType(bool isClass) {
    char* classNameStr = NULL;

    if (isClass) {
        std::string className = EClassSTRING::classRTLname();

        classNameStr = new char[className.size() + 1];
        strcpy(classNameStr, className.c_str());
    }

    return EType(create_type(-1, dtype_string, classNameStr, NULL));
}

EType EType::classType(const std::string& classTypeName) {
    char* classNameStr = NULL;
    classNameStr = new char[classTypeName.size() + 1];
    strcpy(classNameStr, classTypeName.c_str());

    return EType(create_type(-1, dtype_user_defined, classNameStr, NULL));
}

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

bool EType::isClass() const { return (this->_type->id_name != NULL); }

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

    if (typeLevel->id_name == NULL) {
        switch (typeLevel->type) {
            case dtype_boolean:         result += "Z"; break;
            case dtype_character:       result += "C"; break;
            case dtype_integer:         result += "J"; break;
            case dtype_natural:         result += "J"; break;
            case dtype_string:          result += "L" + EClass::javaStringFullName() + ";"; break;

            default: break;
        }
    }
    else {
        switch (typeLevel->type) {
            case dtype_boolean:         result += "L" + EClassBOOLEAN::classRTLfullName() + ";"; break;
            case dtype_character:       result += "L" + EClassCHARACTER::classRTLfullName() + ";"; break;
            case dtype_integer:         result += "L" + EClassINTEGER::classRTLfullName() + ";"; break;
            case dtype_string:          result += "L" + EClassSTRING::classRTLfullName() + ";"; break;
            case dtype_array:           result += "L" + EClassARRAY::classRTLfullName() + ";"; break;
            case dtype_user_defined:    result += "L" + classInfo->fullName() + ";"; break;

            default: break;
        }
    }

    return result;
}

bool EType::isExpanded() const {
    bool result = *this == EType::noType() ||
                  (this->_type->type == dtype_boolean) ||
                  (this->_type->type == dtype_integer) ||
                  (this->_type->type == dtype_character);

    return result;
}

type_strct* EType::getRawTypeCopy() const {
    if (this->_type == nullptr) {
        return nullptr;
    }

    type_strct* result = new type_strct;
    result->type = this->_type->type;
    result->id_name = this->_type->id_name;
    result->arrayelem_type = (this->_type->type == dtype_array ? EType(this->_type->arrayelem_type).getRawTypeCopy() : nullptr);

    return result;
}

bool EType::operator==(const EType& other) const {
    bool result = false;

    if (other._type == nullptr)         { return (this->_type == nullptr); }
    else if (this->_type == nullptr)    { return (other._type == nullptr); }

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
        else if (firstTypeArrElemType->type != dtype_user_defined) {
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
    else if (*this == EType::noType() || other == EType::noType()) {
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
    else if (secondTypeArrElemType->type == dtype_user_defined &&
        firstTypeArrElemType->type == dtype_user_defined &&
        firstTypeArrLevel == secondTypeArrLevel &&
        EProgram::current->getClassBy(firstTypeArrElemType->id_name)->isDescendantTo(EProgram::current->getClassBy(secondTypeArrElemType->id_name)))
    {
        return true;
    }
    else if (firstTypeArrElemType->type == dtype_integer &&
             secondTypeArrElemType->type == dtype_natural
             ||
             firstTypeArrElemType->type == dtype_natural &&
             secondTypeArrElemType->type == dtype_integer)
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
        case dtype_void:            result = "void liter"; break;
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

std::string EType::firstElemClassName() const {
    std::string result;
    switch (this->_type->type) {
        case dtype_boolean:         result = EClassBOOLEAN::classRTLname(); break;
        case dtype_character:       result = EClassCHARACTER::classRTLname(); break;
        case dtype_integer:         result = EClassINTEGER::classRTLname(); break;
        case dtype_natural:         result = EClassNATURAL::classRTLname(); break;
        case dtype_string:          result = EClassSTRING::classRTLname(); break;
        case dtype_array:           result = EClassARRAY::classRTLname(); break;
        case dtype_user_defined:    result = std::string(this->_type->id_name); break;

        default: break;
    }

    return result;
}
