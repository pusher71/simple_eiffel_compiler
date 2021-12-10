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
    EType       _returnType;

    std::string _ownerClassName;

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
protected:
    EFeature(const std::string& featureName, const EClass* ownerClass, feature_decl_strct* featureDecl);
    EFeature(const std::string& featureName, const EClass* ownerClass, const EType& returnType);

public:
    virtual ~EFeature() = 0;

    virtual void validateDataTypes() const = 0;

    void checkOnNameClashingWithClass() const;
    virtual void checkOnNameClashingAfterInherit() const = 0;

    // ---------------- attributes ----------------
public:
    virtual EFeatureType featureType() const = 0;

    std::string name() const;
    EType returnType() const;

    std::string ownerClassName() const;

    // ----------------- contract -----------------
public:
    virtual bool isConformingTo(const EFeature& other) const = 0;

    // ---------------- additional ----------------
public:
    virtual std::string toString() const = 0;
};

#endif // EFEATURE_H
