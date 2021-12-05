#include "etype.h"
#include "eprogram.h"

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

EType EType::voidType() {
    return EType(nullptr);
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

std::string EType::descriptor() const {
    std::string result;

    if (this->_type == nullptr) { return "<NULL TYPE>"; }

    type_strct* typeLevel = this->_type;
    while (typeLevel->type == dtype_array) {
        result += "[";
        typeLevel = typeLevel->arrayelem_type;
    }

    switch (typeLevel->type) {
        case dtype_boolean:         result += "Z"; break;
        case dtype_character:       result += "C"; break;
        case dtype_integer:         result += "S"; break;
        case dtype_natural:         result += "S"; break;
        case dtype_string:          result += "Ljava/lang/String;"; break;
        case dtype_user_defined:    result += std::string("L") + typeLevel->id_name + ";"; break;

        default: break;
    }

    return result;
}

bool EType::operator==(const EType& other) const { return (this->descriptor() == other.descriptor()); }
bool EType::operator!=(const EType& other) const { return (this->descriptor() != other.descriptor()); }
