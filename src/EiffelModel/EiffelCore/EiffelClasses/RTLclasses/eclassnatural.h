#ifndef ECLASSNATURAL_H
#define ECLASSNATURAL_H

#include "../eclassrtl.h"

class EClassNATURAL : public EClassRTL {
    // ================ STATIC ================
public:
    static std::string classRTLname();

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
public:
    EClassNATURAL();

protected:
    void _defineParents() override;
    void _defineCreators() override;
    void _defineFeatures() override;

    // ---------------- attributes ----------------
public:
    std::string name() const override;
};

#endif // ECLASSNATURAL_H
