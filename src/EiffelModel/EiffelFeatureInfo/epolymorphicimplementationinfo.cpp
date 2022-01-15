#include "epolymorphicimplementationinfo.h"

EPolymorphicImplementationInfo::EPolymorphicImplementationInfo()
    : _featureType(EFeature::efeature_nofeature),
      _fieldOrMethodRef_constLink(0),

      _exceptionClass_constLink(0),
      _exceptionMethodRef_constLink(0),
      _exceptionString_constLink(0)
{}

EPolymorphicImplementationInfo::EPolymorphicImplementationInfo(EFeature::EFeatureType featureType, short fieldOrMethodRef_constLink)
    : _featureType(featureType),
      _fieldOrMethodRef_constLink(fieldOrMethodRef_constLink),

      _exceptionClass_constLink(0),
      _exceptionMethodRef_constLink(0),
      _exceptionString_constLink(0)
{}

EPolymorphicImplementationInfo::EPolymorphicImplementationInfo(short exceptionClass_constLink, short exceptionMethodRef_constLink, short exceptionString_constLink)
    : _featureType(EFeature::efeature_nofeature),
      _fieldOrMethodRef_constLink(0),

      _exceptionClass_constLink(exceptionClass_constLink),
      _exceptionMethodRef_constLink(exceptionMethodRef_constLink),
      _exceptionString_constLink(exceptionString_constLink)
{}

bool EPolymorphicImplementationInfo::isExceptionThrow() const { return (this->_featureType == EFeature::efeature_nofeature); }

EFeature::EFeatureType EPolymorphicImplementationInfo::featureType() const { return this->_featureType; }
short EPolymorphicImplementationInfo::fieldOrMethodRef_constLink() const { return this->_fieldOrMethodRef_constLink; }

short EPolymorphicImplementationInfo::exceptionString_constLink() const { return this->_exceptionString_constLink; }
