#include "eclassstring.h"

std::string EClassSTRING::classRTLname() { return "STRING"; }
std::string EClassSTRING::classRTLfullName() { return EClass::rtlClassPackageName() + "/" + EClassSTRING::classRTLname(); }

EClassSTRING::EClassSTRING() {
    this->_initSelf();
}

void EClassSTRING::_defineParents() {}
void EClassSTRING::_defineCreators() {}
void EClassSTRING::_defineFeatures() {
}

std::string EClassSTRING::name() const { return EClassSTRING::classRTLname(); }
