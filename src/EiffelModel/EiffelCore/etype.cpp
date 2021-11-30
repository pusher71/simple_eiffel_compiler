#include "etype.h"

extern "C" {
    struct type_strct* create_type(unsigned int         node_index,
                                   enum type_enum       type,
                                   char*                id_name,
                                   struct type_strct*   arrayelem_type);
}

EType* EType::create(type_strct* type) {
    EType* result = new EType();
    result->_type = type;

    return result;
}

EType* EType::create(const std::string& className) {
    EType* result = new EType();
    char className_cstr[512];
    strcpy(className_cstr, className.c_str());

    result->_type = create_type(-1, dtype_user_defined, className_cstr, NULL);

    return result;
}
