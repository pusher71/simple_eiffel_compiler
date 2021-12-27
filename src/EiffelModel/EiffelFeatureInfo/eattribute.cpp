#include "eattribute.h"

#include "../EiffelCore/eprogram.h"
#include "eroutine.h"

#include "../EiffelCore/EiffelClasses/euserclass.h"
#include "../EiffelCore/EiffelClasses/eclassrtl.h"

EAttribute::EAttribute(const std::string& featureName, EUserClass* ownerClass, feature_decl_strct* featureDecl)
    : EFeature(featureName, ownerClass, featureDecl)
{
}

EAttribute::EAttribute(const std::string& featureName, const EClass* ownerClass, const EType& returnType)
    : EFeature(featureName, ownerClass, returnType)
{}

EAttribute::~EAttribute() {}

EFeature::EFeatureType EAttribute::featureType() const { return efeature_attribute; }

void EAttribute::validateDataTypes() { EFeature::validateDataTypes(); }

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

std::string EAttribute::descriptor() const {
    if ( dynamic_cast<EClassRTL*>(EProgram::current->getClassBy(this->_ownerClassName)) )   { return (this->_returnType.descriptor()); }
    else                                                                                    { return ("L" + EClass::javaObjectFullName() + ";"); }
}

std::string EAttribute::toString() const {
    std::string result = EFeature::toString();
    return result;
}
