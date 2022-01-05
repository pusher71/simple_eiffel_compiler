#include "efeaturemetainfo.h"

EFeatureMetaInfo::EFeatureMetaInfo(const std::string& finalName,
                                   const std::pair<std::string, std::string>& featureMark,
                                   EFeature* implementation,
                                   EFeature::EFeatureType featureType)
    : _finalName(finalName),
      _featureMark(featureMark),
      _implementation(implementation),
      _parentClassName(""),
      _parentClassIndex(-1),
      _featureType(featureType)
{}

std::string EFeatureMetaInfo::finalName() const { return this->_finalName; }
std::pair<std::string, std::string> EFeatureMetaInfo::featureMark() const { return this->_featureMark; }
EFeature* EFeatureMetaInfo::implementation() const { return this->_implementation; }
EFeature::EFeatureType EFeatureMetaInfo::featureType() const { return this->_featureType; }
EFeatureMetaInfo::EReturnType EFeatureMetaInfo::returnType() const { return this->_returnType; }

void EFeatureMetaInfo::setFinalName(const std::string& finalName) { this->_finalName = finalName; }
void EFeatureMetaInfo::setFeatureMark(const std::string& className, const std::string& finalName) { this->_featureMark = {className, finalName}; }
void EFeatureMetaInfo::setImplementation(EFeature* implementation) { this->_implementation = implementation; }
void EFeatureMetaInfo::setReturnType(EFeatureMetaInfo::EReturnType returnType) { this->_returnType = returnType; }

std::string EFeatureMetaInfo::currentOwnerClassName() const { return this->_currentOwnerClassName; }
std::string EFeatureMetaInfo::parentClassName() const { return this->_parentClassName; }
int EFeatureMetaInfo::parentClassIndex() const { return this->_parentClassIndex; }

void EFeatureMetaInfo::setCurrentOwnerClassName(const std::string& currentOwnerClassName) { this->_currentOwnerClassName = currentOwnerClassName; }
void EFeatureMetaInfo::setParentClassName(const std::string& parentClassName) { this->_parentClassName = parentClassName; }
void EFeatureMetaInfo::setParentClassIndex(int parentClassIndex) { this->_parentClassIndex = parentClassIndex; }

short EFeatureMetaInfo::featureName_utf8Link() const { return this->_featureName_utf8Link; }
short EFeatureMetaInfo::featureDescriptor_utf8Link() const { return this->_featureDescriptor_utf8Link; }
short EFeatureMetaInfo::polyMethodName_utf8Link() const { return this->_polyMethodName_utf8Link; }
short EFeatureMetaInfo::polyMethodDescriptor_utf8Link() const { return this->_polyMethodDescriptor_utf8Link; }

void EFeatureMetaInfo::setFeatureName_utf8Link(short featureName_utf8Link) { this->_featureName_utf8Link = featureName_utf8Link; }
void EFeatureMetaInfo::setFeatureDescriptor_utf8Link(short featureDescriptor_utf8Link) { this->_featureDescriptor_utf8Link = featureDescriptor_utf8Link; }
void EFeatureMetaInfo::setPolyMethodName_utf8Link(short polyMethodName_utf8Link) { this->_polyMethodName_utf8Link = polyMethodName_utf8Link; }
void EFeatureMetaInfo::setPolyMethodDescriptor_utf8Link(short polyMethodDescriptor_utf8Link) { this->_polyMethodDescriptor_utf8Link = polyMethodDescriptor_utf8Link; }

const std::map<std::string, std::string> EFeatureMetaInfo::redefinedFeatures() const { return this->_redefinedFeatures; }
const std::map<short, EPolymorphicImplementationInfo>& EFeatureMetaInfo::polyMethodImplementations() const { return this->_polyMethodImplementations; }

void EFeatureMetaInfo::setRedefinedFeature(const std::string& parentName, const std::string& redefinedFeatureMetaFinalName) { this->_redefinedFeatures[parentName] = redefinedFeatureMetaFinalName; }
void EFeatureMetaInfo::clearRedefinedFeatures() { this->_redefinedFeatures.clear(); }
void EFeatureMetaInfo::addPolyMethodImplementation(short constClassLink, const EPolymorphicImplementationInfo& polyImplementation) { this->_polyMethodImplementations[constClassLink] = polyImplementation; }

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
