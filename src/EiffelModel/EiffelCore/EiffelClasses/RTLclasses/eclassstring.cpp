#include "eclassstring.h"
#include "eclassany.h"

std::string EClassSTRING::classRTLname() { return "STRING"; }
std::string EClassSTRING::classRTLfullName() { return EClass::rtlClassPackageName() + "/" + EClassSTRING::classRTLname(); }

EClassSTRING::EClassSTRING() {
    this->_initSelf();
}

void EClassSTRING::_defineParents() { this->_parents.push_back({EClassANY::classRTLname(), {}}); }
void EClassSTRING::_defineCreators() {}
void EClassSTRING::_defineFeatures() {
    this->_addFeature( std::make_shared<ERoutine>(ERoutine("GET", this, EType::stringType(), {}, {})) );
    this->_addFeature( std::make_shared<ERoutine>(ERoutine("SET", this, EType::noType(), {{"value", EType::stringType()}}, {})) );
}

std::string EClassSTRING::name() const { return EClassSTRING::classRTLname(); }
