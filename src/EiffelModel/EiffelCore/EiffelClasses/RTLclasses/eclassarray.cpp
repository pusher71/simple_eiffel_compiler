#include "eclassarray.h"

std::string EClassARRAY::classRTLname() { return "ARRAY"; }

EClassARRAY::EClassARRAY() {
    this->_initSelf();
}

void EClassARRAY::_defineParents() {}
void EClassARRAY::_defineCreators() {}
void EClassARRAY::_defineFeatures() {
}

std::string EClassARRAY::name() const { return EClassARRAY::classRTLname(); }
