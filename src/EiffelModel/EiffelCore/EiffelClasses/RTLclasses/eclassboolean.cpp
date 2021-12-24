#include "eclassboolean.h"

std::string EClassBOOLEAN::classRTLname() { return "BOOLEAN"; }

EClassBOOLEAN::EClassBOOLEAN() {
    this->_initSelf();
}

void EClassBOOLEAN::_defineParents() {}
void EClassBOOLEAN::_defineCreators() {}
void EClassBOOLEAN::_defineFeatures() {
}

std::string EClassBOOLEAN::name() const { return EClassBOOLEAN::classRTLname(); }
