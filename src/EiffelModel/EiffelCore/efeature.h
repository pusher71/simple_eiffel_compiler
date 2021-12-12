#ifndef EFEATURE_H
#define EFEATURE_H

#include <string>
#include "../../bison/tree_nodes.h"
#include "etype.h"

class EClass;
class EUserClass;

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

    short _name_utf8Link;
    short _descriptor_utf8Link;

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
protected:
    EFeature(const std::string& featureName, EUserClass* ownerClass, feature_decl_strct* featureDecl);
    EFeature(const std::string& featureName, const EClass* ownerClass, const EType& returnType);

public:
    virtual ~EFeature() = 0;

    virtual void validateDataTypes() = 0;

    void checkOnNameClashingWithClass() const;
    virtual void checkOnNameClashingAfterInherit() const = 0;

    // ---------------- attributes ----------------
public:
    virtual EFeatureType featureType() const = 0;

    std::string name() const;
    EType returnType() const;

    std::string ownerClassName() const;

    short name_utf8Link() const;
    short descriptor_utf8Link() const;

    // ----------------- contract -----------------
public:
    virtual bool isConformingTo(const EFeature& other) const = 0;

    // ---------------- additional ----------------
public:
    virtual std::string toString() const = 0;
};

#endif // EFEATURE_H
