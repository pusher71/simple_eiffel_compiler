#ifndef EFEATURE_H
#define EFEATURE_H

#include <string>
#include "../../bison/tree_nodes.h"
#include "etype.h"

class EFeature {
    // ============== INNER TYPES =============
public:
    enum EFeatureType {
        efeature_field,
        efeature_method
    };

    // ============== ATTRIBUTES ==============
protected:
    feature_decl_strct* _node;

    std::string _name;
    std::string _ownerClassName;
    EType*      _type;

    // ============== OPERATIONS ==============
    // -------- creating --------
public:
    static EFeature* create(const std::string& featureName, const std::string& ownerClassName, feature_decl_strct* featureDecl);

    virtual bool initSelf() = 0;

    // ------- attributes -------
    EFeatureType type();
};

#endif // EFEATURE_H
