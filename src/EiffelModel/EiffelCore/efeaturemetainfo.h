#ifndef EMETAMETHODINFO_H
#define EMETAMETHODINFO_H

#include "efeature.h"
#include <map>
#include <vector>

#include "../EiffelFeatureInfo/epolymorphicimplementationinfo.h"

class ByteCode;

class EFeatureMetaInfo {
    // =============== SUBTYPES ===============
public:
    enum EReturnType {
        ereturntype_void,
        ereturntype_integer,
        ereturntype_object
    };

    // ============== ATTRIBUTES ==============
private:
    std::string                         _finalName;
    std::pair<std::string, std::string> _featureMark;       // Name of the class + final name of the feature
    EFeature*                           _implementation;

    std::string                         _currentOwnerClassName;
    std::string                         _parentClassName;
    int                                 _parentClassIndex;

    EFeature::EFeatureType              _featureType;
    EReturnType                         _returnType;

    short                               _featureName_utf8Link;
    short                               _featureDescriptor_utf8Link;
    short                               _polyMethodName_utf8Link;
    short                               _polyMethodDescriptor_utf8Link;

    std::map<std::string, std::string>  _redefinedFeatures;
    std::map<short, EPolymorphicImplementationInfo> _polyMethodImplementations;

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
public:
    EFeatureMetaInfo(const std::string& finalName,
                     const std::pair<std::string, std::string>& featureMark,
                     EFeature* implementation,
                     EFeature::EFeatureType featureType);

    // ---------------- attributes ----------------
public:
    // Main parameters
    std::string finalName() const;
    std::pair<std::string, std::string> featureMark() const;
    EFeature* implementation() const;
    EFeature::EFeatureType featureType() const;
    EReturnType returnType() const;

    void setFinalName(const std::string& finalName);
    void setFeatureMark(const std::string& className, const std::string& finalName);
    void setImplementation(EFeature* implementation);
    void setFeatureType(EFeature::EFeatureType featureType);
    void setReturnType(EReturnType returnType);

    // Owner and parent info
    std::string currentOwnerClassName() const;
    std::string parentClassName() const;
    int parentClassIndex() const;

    void setCurrentOwnerClassName(const std::string& currentOwnerClassName);
    void setParentClassName(const std::string& parentClassName);
    void setParentClassIndex(int parentClassIndex);

    // Constant table info
    short featureName_utf8Link() const;
    short featureDescriptor_utf8Link() const;
    short polyMethodName_utf8Link() const;
    short polyMethodDescriptor_utf8Link() const;

    void setFeatureName_utf8Link(short featureName_utf8Link);
    void setFeatureDescriptor_utf8Link(short featureDescriptor_utf8Link);
    void setPolyMethodName_utf8Link(short polyMethodName_utf8Link);
    void setPolyMethodDescriptor_utf8Link(short polyMethodDescriptor_utf8Link);

    const std::map<std::string, std::string> redefinedFeatures() const;
    const std::map<short, EPolymorphicImplementationInfo>& polyMethodImplementations() const;

    void setRedefinedFeature(const std::string& parentName, const std::string& redefinedFeatureMetaFinalName);
    void clearRedefinedFeatures();
    void addPolyMethodImplementation(short constClassLink, const EPolymorphicImplementationInfo& polyImplementation);

    // ----------------- contract -----------------
public:
    bool operator==(const EFeatureMetaInfo& other) const;
    bool operator<(const EFeatureMetaInfo& other) const;
};

#endif // EMETAMETHODINFO_H
