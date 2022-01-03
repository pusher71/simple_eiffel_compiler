#ifndef ECLASSBOOLEAN_H
#define ECLASSBOOLEAN_H

#include "../eclassrtl.h"

class EClassBOOLEAN : public EClassRTL {
    // ================== STATIC ==================
public:
    static std::string classRTLname();
    static std::string classRTLfullName();

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
public:
    EClassBOOLEAN();

protected:
    void _defineParents() override;
    void _defineCreators() override;
    void _defineFeatures() override;

    // ---------------- attributes ----------------
public:
    std::string name() const override;
};

#endif // ECLASSBOOLEAN_H
