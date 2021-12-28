#ifndef EPOLYMORPHICFEATUREINFO_H
#define EPOLYMORPHICFEATUREINFO_H

#include "../EiffelCore/efeature.h"

class EPolymorphicImplementationInfo {
    // ================ ATTRIBUTES ================
private:
    // ... Polymorphic implementation info
    EFeature::EFeatureType  _featureType;
    short                   _fieldOrMethodRef_constLink;

    // ... Exception call info
    short                   _exceptionClass_constLink;
    short                   _exceptionMethodRef_constLink;
    short                   _exceptionString_constLink;

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
public:
    EPolymorphicImplementationInfo();
    EPolymorphicImplementationInfo(EFeature::EFeatureType featureType, short fieldOrMethodRef_constLink);
    EPolymorphicImplementationInfo(short exceptionClass_constLink, short exceptionMethodRef_constLink, short exceptionString_constLink);

    // ----------------- contract -----------------
public:
    bool isExceptionThrow() const;

    EFeature::EFeatureType featureType() const;
    short fieldOrMethodRef_constLink() const;

    short exceptionClass_constLink() const;
    short exceptionMethodRef_constLink() const;
    short exceptionString_constLink() const;
};

#endif // EPOLYMORPHICFEATUREINFO_H
