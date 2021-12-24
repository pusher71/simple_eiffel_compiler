#ifndef ECLASSARRAY_H
#define ECLASSARRAY_H

#include "../eclassrtl.h"

class EClassARRAY : public EClassRTL {
    // ================ STATIC ================
public:
    static std::string classRTLname();

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
public:
    EClassARRAY();

protected:
    void _defineParents() override;
    void _defineCreators() override;
    void _defineFeatures() override;

    // ---------------- attributes ----------------
public:
    std::string name() const override;
};

#endif // ECLASSARRAY_H
