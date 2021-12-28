#include "eclassboolean.h"
#include "eclassany.h"

std::string EClassBOOLEAN::classRTLname() { return "BOOLEAN"; }
std::string EClassBOOLEAN::classRTLfullName() { return EClass::rtlClassPackageName() + "/" + EClassBOOLEAN::classRTLname(); }

EClassBOOLEAN::EClassBOOLEAN() {
    this->_initSelf();
}

void EClassBOOLEAN::_defineParents() { this->_parents.push_back({EClassANY::classRTLname(), {}}); }
void EClassBOOLEAN::_defineCreators() {}
void EClassBOOLEAN::_defineFeatures() {
}

std::string EClassBOOLEAN::name() const { return EClassBOOLEAN::classRTLname(); }
