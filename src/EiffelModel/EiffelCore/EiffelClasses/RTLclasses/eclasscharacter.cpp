#include "eclasscharacter.h"

std::string EClassCHARACTER::classRTLname() { return "CHARACTER"; }
std::string EClassCHARACTER::classRTLfullName() { return EClass::rtlClassPackageName() + "/" + EClassCHARACTER::classRTLname(); }

EClassCHARACTER::EClassCHARACTER() {
    this->_initSelf();
}

void EClassCHARACTER::_defineParents() {}
void EClassCHARACTER::_defineCreators() {}
void EClassCHARACTER::_defineFeatures() {
}

std::string EClassCHARACTER::name() const { return EClassCHARACTER::classRTLname(); }
