#include "eclasscharacter.h"
#include "eclassany.h"

std::string EClassCHARACTER::classRTLname() { return "CHARACTER"; }
std::string EClassCHARACTER::classRTLfullName() { return EClass::rtlClassPackageName() + "/" + EClassCHARACTER::classRTLname(); }

EClassCHARACTER::EClassCHARACTER() {
    this->_initSelf();
}

void EClassCHARACTER::_defineParents() { this->_parents.push_back({EClassANY::classRTLname(), {}}); }
void EClassCHARACTER::_defineCreators() {}
void EClassCHARACTER::_defineFeatures() {
    this->_addFeature( std::make_shared<ERoutine>(ERoutine("GET", this, EType::charType(), {}, {})) );
    this->_addFeature( std::make_shared<ERoutine>(ERoutine("SET", this, EType::noType(), {{"value", EType::charType()}}, {})) );
}

std::string EClassCHARACTER::name() const { return EClassCHARACTER::classRTLname(); }
