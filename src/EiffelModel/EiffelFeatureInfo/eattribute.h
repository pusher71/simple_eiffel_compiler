#ifndef EFIELD_H
#define EFIELD_H

#include <string>
#include "../EiffelCore/efeature.h"

class EAttribute : public EFeature {
    // ================ OPERATIONS ================
    // ----------------- creating -----------------
public:
    EAttribute(const std::string& featureName, const EClass* ownerClass, feature_decl_strct* featureDecl);
    EAttribute(const std::string& featureName, const EClass* ownerClass, const EType& returnType);
    ~EAttribute() override;

    // ---------------- attributes ----------------
public:
    EFeatureType featureType() const override;

    // ----------------- contract -----------------
public:
    void validate() const override;
};

#endif // EFIELD_H
