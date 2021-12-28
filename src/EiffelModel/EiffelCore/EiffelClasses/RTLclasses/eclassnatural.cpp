#include "eclassnatural.h"
#include "eclassany.h"

std::string EClassNATURAL::classRTLname() { return "NATURAL"; }
std::string EClassNATURAL::classRTLfullName() { return EClass::rtlClassPackageName() + "/" + EClassNATURAL::classRTLname(); }

EClassNATURAL::EClassNATURAL() {
    this->_initSelf();
}

void EClassNATURAL::_defineParents() { this->_parents.push_back({EClassANY::classRTLname(), {}}); }
void EClassNATURAL::_defineCreators() {}
void EClassNATURAL::_defineFeatures() {
}

std::string EClassNATURAL::name() const { return EClassNATURAL::classRTLname(); }
