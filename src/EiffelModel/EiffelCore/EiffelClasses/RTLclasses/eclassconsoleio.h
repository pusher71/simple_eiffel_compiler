#ifndef ECLASSCONSOLEIO_H
#define ECLASSCONSOLEIO_H

#include "../eclassrtl.h"

class EClassCONSOLEIO : public EClassRTL {
    // ================ STATIC ================
public:
    static std::string classRTLname();
    static std::string classRTLfullName();

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
public:
    EClassCONSOLEIO();

protected:
    void _defineParents() override;
    void _defineCreators() override;
    void _defineFeatures() override;

    // ---------------- attributes ----------------
public:
    std::string name() const override;
};

#endif // ECLASSCONSOLEIO_H
