#include "eattribute.h"

#include "../EiffelCore/eprogram.h"
#include "eroutine.h"

EAttribute::EAttribute(const std::string& featureName, const EClass* ownerClass, feature_decl_strct* featureDecl)
    : EFeature(featureName, ownerClass, featureDecl)
{}

EAttribute::EAttribute(const std::string& featureName, const EClass* ownerClass, const EType& returnType)
    : EFeature(featureName, ownerClass, returnType)
{}

EAttribute::~EAttribute() {}

EFeature::EFeatureType EAttribute::featureType() const { return efeature_attribute; }

void EAttribute::validateDataTypes() const { EFeature::validateDataTypes(); }
void EAttribute::checkOnNameClashingAfterInherit() const { EFeature::checkOnNameClashingAfterInherit(); }

bool EAttribute::isConformingTo(const EFeature& other) const {
    bool result = false;

    EAttribute* otherAttribute  = dynamic_cast<EAttribute*>((EFeature*)(&other));
    ERoutine*   otherRoutine    = dynamic_cast<ERoutine*>((EFeature*)(&other));

    if (otherAttribute != nullptr) {
        if (this->_returnType.canCastTo(otherAttribute->_returnType) &&
            this->_returnType.isExpanded() == otherAttribute->_returnType.isExpanded())
        {
            result = true;
        }
    }
    else if (otherRoutine != nullptr) {
        if (otherRoutine->formalParamsCount() == 0 &&
            this->_returnType.canCastTo(otherRoutine->returnType()) &&
            this->_returnType.isExpanded() == otherRoutine->returnType().isExpanded())
        {
            result = true;
        }
    }

    return result;
}

std::string EAttribute::toString() const {
    std::string result = EFeature::toString();
    return result;
}
