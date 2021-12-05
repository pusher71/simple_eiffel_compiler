#ifndef EMETAMETHODINFO_H
#define EMETAMETHODINFO_H

#include "efeature.h"

class EMetaFeatureInfo {
    // ============== ATTRIBUTES ==============
private:
    std::string                         _finalName;
    std::pair<std::string, std::string> _featureMark;       // Name of the class + final name of the feature
    EFeature*                           _implementation;

public:
    EMetaFeatureInfo(const std::string& finalName, const std::pair<std::string, std::string>& featureMark, EFeature* implementation);

    void setFinalName(const std::string& finalName);
    void setClassNameAndFinalName(const std::string& className, const std::string& finalName);
    void setImplementation(EFeature* implementation);

    std::string finalName() const;
    std::pair<std::string, std::string> featureMark() const;
    std::string featureMarkStr() const;
    EFeature* implementation() const;
};

#endif // EMETAMETHODINFO_H
