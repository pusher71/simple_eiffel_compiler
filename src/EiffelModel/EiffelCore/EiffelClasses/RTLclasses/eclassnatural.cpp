#include "eclassnatural.h"

std::string EClassNATURAL::classRTLname() { return "NATURAL"; }
std::string EClassNATURAL::classRTLfullName() { return EClass::rtlClassPackageName() + "/" + EClassNATURAL::classRTLname(); }

EClassNATURAL::EClassNATURAL() {
    this->_initSelf();
}

void EClassNATURAL::_defineParents() {}
void EClassNATURAL::_defineCreators() {}
void EClassNATURAL::_defineFeatures() {
}

std::string EClassNATURAL::name() const { return EClassNATURAL::classRTLname(); }
