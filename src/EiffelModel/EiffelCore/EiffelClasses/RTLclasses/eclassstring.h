#ifndef ECLASSSTRING_H
#define ECLASSSTRING_H

#include "../eclassrtl.h"

class EClassSTRING : public EClassRTL {
    // ================ STATIC ================
public:
    static std::string classRTLname();

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
public:
    EClassSTRING();

protected:
    void _defineParents() override;
    void _defineCreators() override;
    void _defineFeatures() override;

    // ---------------- attributes ----------------
public:
    std::string name() const override;
};

#endif // ECLASSSTRING_H
