#ifndef ELOCALVARIABLE_H
#define ELOCALVARIABLE_H

#include <string>
#include "../EiffelCore/etype.h"
#include "../../bison/tree_nodes.h"

class ELocalVariable {
private:
    std::string _name;
    EType*      _type;

public:
    static ELocalVariable* create(const std::string& name, EType* type);
};

#endif // ELOCALVARIABLE_H
