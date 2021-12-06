#include "efeaturemetainfo.h"

EFeatureMetaInfo::EFeatureMetaInfo(const std::string& finalName, const std::pair<std::string, std::string>& featureMark, EFeature* implementation)
    : _finalName(finalName),
      _featureMark(featureMark),
      _implementation(implementation),
      _parentClassName("")
{}

void EFeatureMetaInfo::setFinalName(const std::string& finalName) { this->_finalName = finalName; }
void EFeatureMetaInfo::setFeatureMark(const std::string& className, const std::string& finalName) { this->_featureMark = {className, finalName}; }
void EFeatureMetaInfo::setImplementation(EFeature* implementation) { this->_implementation = implementation; }
void EFeatureMetaInfo::setParentClassName(const std::string& parentClassName) { this->_parentClassName = parentClassName; }

std::string EFeatureMetaInfo::finalName() const { return this->_finalName; }
std::pair<std::string, std::string> EFeatureMetaInfo::featureMark() const { return this->_featureMark; }
EFeature* EFeatureMetaInfo::implementation() const { return this->_implementation; }
std::string EFeatureMetaInfo::parentClassName() const { return this->_parentClassName; }

bool EFeatureMetaInfo::operator==(const EFeatureMetaInfo& other) const {
    bool result = true;
    result &= this->_finalName == other._finalName;
    result &= this->_featureMark == other._featureMark;
    result &= this->_implementation == other._implementation;

    return result;
}

bool EFeatureMetaInfo::operator<(const EFeatureMetaInfo& other) const {
    bool result;

    // Compare final names
    if (this->_finalName < other._finalName)        { result = true; }
    else if (this->_finalName > other._finalName)   { result = false; }
    else {
        // Compare feature marks
        if (this->_featureMark < other._featureMark)        { result = true; }
        else if (this->_featureMark > other._featureMark)   { result = false; }
        else {
            // Compare implementations
            if (this->_implementation < other._implementation)      { result = true; }
            else if (this->_implementation > other._implementation) { result = false; }
            else                                                    { result = false; }
        }
    }

    return result;
}
