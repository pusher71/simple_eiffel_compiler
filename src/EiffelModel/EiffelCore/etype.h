#ifndef EDATATYPE_H
#define EDATATYPE_H

#include <string>
#include "../../bison/tree_nodes.h"

class EType {
private:
    type_strct* _type;

public:
    static EType* create(type_strct* type);
    static EType* create(const std::string& className);
};

#endif // EDATATYPE_H
