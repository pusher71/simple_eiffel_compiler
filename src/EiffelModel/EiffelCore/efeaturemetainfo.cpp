#include "efeaturemetainfo.h"

EFeatureMetaInfo::EFeatureMetaInfo(const std::string& finalName, const std::pair<std::string, std::string>& featureMark, EFeature* implementation)
    : _finalName(finalName),
      _featureMark(featureMark),
      _implementation(implementation),
      _parentClassName(""),
      _parentClassIndex(-1)
{}

void EFeatureMetaInfo::setFinalName(const std::string& finalName) { this->_finalName = finalName; }
void EFeatureMetaInfo::setFeatureMark(const std::string& className, const std::string& finalName) { this->_featureMark = {className, finalName}; }
void EFeatureMetaInfo::setImplementation(EFeature* implementation) { this->_implementation = implementation; }
void EFeatureMetaInfo::setParentClassName(const std::string& parentClassName) { this->_parentClassName = parentClassName; }
void EFeatureMetaInfo::setParentClassIndex(int parentClassIndex) { this->_parentClassIndex = parentClassIndex; }

void EFeatureMetaInfo::setFeatureMark_utf8Link(short featureMark_utf8Link) { this->_featureMark_utf8Link = featureMark_utf8Link; }
void EFeatureMetaInfo::setDescriptor_utf8Link(short descriptor_utf8Link) { this->_descriptor_utf8Link = descriptor_utf8Link; }
void EFeatureMetaInfo::addPolymorphicImplementation(short constClassLink, const std::pair<EFeature::EFeatureType, short>& fieldOrMethodRef) { this->_polymorphicImplementations[constClassLink] = fieldOrMethodRef; }

std::string EFeatureMetaInfo::finalName() const { return this->_finalName; }
std::pair<std::string, std::string> EFeatureMetaInfo::featureMark() const { return this->_featureMark; }
EFeature* EFeatureMetaInfo::implementation() const { return this->_implementation; }
std::string EFeatureMetaInfo::parentClassName() const { return this->_parentClassName; }
int EFeatureMetaInfo::parentClassIndex() const { return this->_parentClassIndex; }

short EFeatureMetaInfo::featureMark_utf8Link() const { return this->_featureMark_utf8Link; }
short EFeatureMetaInfo::descriptor_utf8Link() const { return this->_descriptor_utf8Link; }
std::map<short, std::pair<EFeature::EFeatureType, short>> EFeatureMetaInfo::polymorphicImplementations() const { return this->_polymorphicImplementations; }

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
