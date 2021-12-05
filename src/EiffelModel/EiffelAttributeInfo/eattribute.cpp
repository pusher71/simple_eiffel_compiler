#include "eattribute.h"
#include "../EiffelCore/eprogram.h"

EAttribute::EAttribute(const std::string& featureName, const EClass* ownerClass, feature_decl_strct* featureDecl)
    : EFeature(featureName, ownerClass, featureDecl)
{}

EAttribute::~EAttribute() {}

EFeature::EFeatureType EAttribute::featureType() const { return efeature_attribute; }

void EAttribute::validate() const { EFeature::validate(); }
