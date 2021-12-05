#include "emetafeatureinfo.h"

EMetaFeatureInfo::EMetaFeatureInfo(const std::string& finalName, const std::pair<std::string, std::string>& featureMark, EFeature* implementation)
    : _finalName(finalName), _featureMark(featureMark), _implementation(implementation)
{}

void EMetaFeatureInfo::setFinalName(const std::string& finalName) {
    this->_finalName = finalName;
}

void EMetaFeatureInfo::setClassNameAndFinalName(const std::string& className, const std::string& finalName) {
    this->_featureMark = {className, finalName};
}

void EMetaFeatureInfo::setImplementation(EFeature* implementation) {
    this->_implementation = implementation;
}

std::string EMetaFeatureInfo::finalName() const { return this->_finalName; }
std::pair<std::string, std::string> EMetaFeatureInfo::featureMark() const { return this->_featureMark; }
std::string EMetaFeatureInfo::featureMarkStr() const {
    return this->_featureMark.first + ":" + this->_featureMark.second;
}
EFeature* EMetaFeatureInfo::implementation() const { return this->_implementation; }
