#ifndef EFEATURE_H
#define EFEATURE_H

#include <string>
#include "../../bison/tree_nodes.h"
#include "etype.h"

class EClass;

class EFeature {
    // ================= SUBTYPES =================
public:
    enum EFeatureType {
        efeature_attribute,
        efeature_routine
    };

    // ================ ATTRIBUTES ================
protected:
    feature_decl_strct* _node;

    std::string _name;
    EType       _type;

    std::string _ownerClassName;

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
protected:
    EFeature(const std::string& featureName, const EClass* ownerClass, feature_decl_strct* featureDecl);

public:
    virtual ~EFeature() = 0;

    // ---------------- attributes ----------------
public:
    virtual EFeatureType featureType() const = 0;

    std::string name() const;
    EType type() const;

    std::string ownerClassName() const;

    // ----------------- contract -----------------
public:
    virtual void validate() const = 0;
};

#endif // EFEATURE_H
