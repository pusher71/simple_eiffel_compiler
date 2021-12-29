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
        efeature_nofeature,
        efeature_attribute,
        efeature_routine
    };

    // ================ ATTRIBUTES ================
protected:
    feature_decl_strct* _node;

    std::string _name;
    EType       _returnType;
    std::string _ownerClassName;

    short _linkUtf8_name;
    short _linkUtf8_descriptor;

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
protected:
    EFeature(const std::string& featureName, EUserClass* ownerClass, feature_decl_strct* featureDecl);
    EFeature(const std::string& featureName, const EClass* ownerClass, const EType& returnType);

public:
    virtual ~EFeature() = 0;

    virtual void validateDataTypes() = 0;

    void checkOnNameClashingWithClasses() const;

    // ---------------- attributes ----------------
public:
    virtual EFeatureType featureType() const = 0;

    std::string name() const;
    EType returnType() const;

    std::string ownerClassName() const;

    short linkUtf8_name() const;
    short linkUtf8_descriptor() const;

    void setLinkUtf8_name(short linkUtf8_name);
    void setLinkUtf8_descriptor(short linkUtf8_descriptor);

    virtual std::string descriptor() const = 0;

    // ----------------- contract -----------------
public:
    virtual bool isConformingTo(const EFeature& other, bool areDeclarationsCompared = true) const = 0;

    void changeOwnerClass(const EClass* classInfo);

    // ---------------- additional ----------------
public:
    virtual std::string toString() const = 0;
};

#endif // EFEATURE_H
