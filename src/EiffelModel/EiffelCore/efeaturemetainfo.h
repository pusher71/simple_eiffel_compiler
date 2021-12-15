#ifndef EMETAMETHODINFO_H
#define EMETAMETHODINFO_H

#include "efeature.h"
#include <map>

class ByteCode;

class EFeatureMetaInfo {
    // ================ MY FRIENDS ================
    friend ByteCode;

    // ============== ATTRIBUTES ==============
private:
    std::string                         _finalName;
    std::pair<std::string, std::string> _featureMark;       // Name of the class + final name of the feature
    EFeature*                           _implementation;
    std::string                         _parentClassName;
    int                                 _parentClassIndex;

    short                               _featureMark_utf8Link;
    short                               _descriptor_utf8Link;

    std::map<short, std::pair<EFeature::EFeatureType, short>> _polymorphicImplementations; // Constant class -> field or method ref

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
public:
    EFeatureMetaInfo(const std::string& finalName, const std::pair<std::string, std::string>& featureMark, EFeature* implementation);

    // ----------------- contract -----------------
public:
    void setFinalName(const std::string& finalName);
    void setFeatureMark(const std::string& className, const std::string& finalName);
    void setImplementation(EFeature* implementation);
    void setParentClassName(const std::string& parentClassName);
    void setParentClassIndex(int parentClassIndex);

    void setFeatureMark_utf8Link(short featureMark_utf8Link);
    void setDescriptor_utf8Link(short descriptor_utf8Link);
    void addPolymorphicImplementation(short constClassLink, const std::pair<EFeature::EFeatureType, short>& fieldOrMethodRef);

    std::string finalName() const;
    std::pair<std::string, std::string> featureMark() const;
    EFeature* implementation() const;

    std::string parentClassName() const;
    int parentClassIndex() const;

    short featureMark_utf8Link() const;
    short descriptor_utf8Link() const;
    std::map<short, std::pair<EFeature::EFeatureType, short>> polymorphicImplementations() const;

    // ----------------- contract -----------------
public:
    bool operator==(const EFeatureMetaInfo& other) const;
    bool operator<(const EFeatureMetaInfo& other) const;
};

#endif // EMETAMETHODINFO_H
