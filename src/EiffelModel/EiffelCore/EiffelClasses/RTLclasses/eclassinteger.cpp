#include "eclassinteger.h"
#include "eclassany.h"

std::string EClassINTEGER::classRTLname() { return "INTEGER"; }
std::string EClassINTEGER::classRTLfullName() { return EClass::rtlClassPackageName() + "/" + EClassINTEGER::classRTLname(); }

EClassINTEGER::EClassINTEGER() {
    this->_initSelf();
}

void EClassINTEGER::_defineParents() { this->_parents.push_back({EClassANY::classRTLname(), {}}); }
void EClassINTEGER::_defineCreators() {}
void EClassINTEGER::_defineFeatures() {
}

std::string EClassINTEGER::name() const { return EClassINTEGER::classRTLname(); }
