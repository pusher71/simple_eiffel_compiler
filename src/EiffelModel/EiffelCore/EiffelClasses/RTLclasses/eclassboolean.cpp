#include "eclassboolean.h"

std::string EClassBOOLEAN::classRTLname() { return "BOOLEAN"; }
std::string EClassBOOLEAN::classRTLfullName() { return EClass::rtlClassPackageName() + "/" + EClassBOOLEAN::classRTLname(); }

EClassBOOLEAN::EClassBOOLEAN() {
    this->_initSelf();
}

void EClassBOOLEAN::_defineParents() {}
void EClassBOOLEAN::_defineCreators() {}
void EClassBOOLEAN::_defineFeatures() {
}

std::string EClassBOOLEAN::name() const { return EClassBOOLEAN::classRTLname(); }
