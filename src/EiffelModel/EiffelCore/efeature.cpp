#include "efeature.h"
#include "../EiffelFieldInfo/efield.h"
#include "../EiffelMethodInfo/emethod.h"
#include "etype.h"

EFeature* EFeature::create(const std::string& featureName, const std::string& ownerClassName, feature_decl_strct* featureDecl) {
    EFeature* feature = nullptr;

    // Validate on errors ...
    // ... name clashing

    if (featureDecl->routine_body == NULL)  { feature = EField::create(featureDecl); }
    else                                    { feature = EMethod::create(ownerClassName, featureDecl); }

    if (feature != nullptr) {
        feature->_node = featureDecl;

        feature->_name = featureName;
        feature->_ownerClassName = ownerClassName;
        feature->_type = EType::create(featureDecl->type);
    }

    return feature;
}
