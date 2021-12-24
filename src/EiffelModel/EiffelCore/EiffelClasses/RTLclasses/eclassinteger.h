#ifndef ECLASSINTEGER_H
#define ECLASSINTEGER_H

#include "../eclassrtl.h"

class EClassINTEGER : public EClassRTL {
    // ================ STATIC ================
public:
    static std::string classRTLname();

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
public:
    EClassINTEGER();

protected:
    void _defineParents() override;
    void _defineCreators() override;
    void _defineFeatures() override;

    // ---------------- attributes ----------------
public:
    std::string name() const override;
};

#endif // ECLASSINTEGER_H
