#include "eclassinteger.h"

std::string EClassINTEGER::classRTLname() { return "INTEGER"; }

EClassINTEGER::EClassINTEGER() {
    this->_initSelf();
}

void EClassINTEGER::_defineParents() {}
void EClassINTEGER::_defineCreators() {}
void EClassINTEGER::_defineFeatures() {
}

std::string EClassINTEGER::name() const { return EClassINTEGER::classRTLname(); }
