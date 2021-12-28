#ifndef ECLASSRTL_H
#define ECLASSRTL_H

#include "../eclass.h"
#include "../../EiffelCompilation/bytecode.h"

class EClassRTL : public EClass {
    // ================ ATTRIBUTES ================
protected:
    std::vector<int8_t> _selfByteCodeData;

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
public:
    EClassRTL();

    // ---------------- attributes ----------------
public:
    std::string javaPackageName() const override;
};

#endif // ECLASSRTL_H
