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
    this->_addFeature( std::make_shared<ERoutine>(ERoutine("GET", this, EType::intType(), {}, {})) );
    this->_addFeature( std::make_shared<ERoutine>(ERoutine("SET", this, EType::noType(), {{"value", EType::intType()}}, {})) );
}

std::string EClassINTEGER::name() const { return EClassINTEGER::classRTLname(); }
