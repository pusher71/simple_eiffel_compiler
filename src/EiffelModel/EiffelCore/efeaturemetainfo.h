#ifndef EMETAMETHODINFO_H
#define EMETAMETHODINFO_H

#include "efeature.h"

class EFeatureMetaInfo {
    // ============== ATTRIBUTES ==============
private:
    std::string                         _finalName;
    std::pair<std::string, std::string> _featureMark;       // Name of the class + final name of the feature
    EFeature*                           _implementation;
    std::string                         _parentClassName;

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

    std::string finalName() const;
    std::pair<std::string, std::string> featureMark() const;
    EFeature* implementation() const;
    std::string parentClassName() const;

    // ----------------- contract -----------------
public:
    bool operator==(const EFeatureMetaInfo& other) const;
    bool operator<(const EFeatureMetaInfo& other) const;
};

#endif // EMETAMETHODINFO_H
