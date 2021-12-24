#ifndef ECLASSCHARACTER_H
#define ECLASSCHARACTER_H

#include "../eclassrtl.h"

class EClassCHARACTER : public EClassRTL {
    // ================ STATIC ================
public:
    static std::string classRTLname();

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
public:
    EClassCHARACTER();

protected:
    void _defineParents() override;
    void _defineCreators() override;
    void _defineFeatures() override;

    // ---------------- attributes ----------------
public:
    std::string name() const override;
};

#endif // ECLASSCHARACTER_H
