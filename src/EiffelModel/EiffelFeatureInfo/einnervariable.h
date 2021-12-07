#ifndef ELOCALVARIABLE_H
#define ELOCALVARIABLE_H

#include <string>
#include "../EiffelCore/etype.h"
#include "../../bison/tree_nodes.h"

class EInnerVariable {
    // ================ ATTRIBUTES ================
private:
    short   _index;
    EType   _type;

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
public:
    EInnerVariable(short index, const EType& type);

    // ---------------- attributes ----------------
    short index() const;
    EType type() const;
};

#endif // ELOCALVARIABLE_H
