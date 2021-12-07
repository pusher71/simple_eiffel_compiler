#ifndef ECLASSRTL_H
#define ECLASSRTL_H

#include "../eclass.h"

class EClassRTL : public EClass {
    // ================ OPERATIONS ================
    // ----------------- creating -----------------
public:
    EClassRTL();

    // ---------------- attributes ----------------
public:
    std::string javaPackageName() const override;
};

#endif // ECLASSRTL_H
