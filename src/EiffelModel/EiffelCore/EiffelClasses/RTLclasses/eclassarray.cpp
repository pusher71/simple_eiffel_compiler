#include "eclassarray.h"
#include "eclassany.h"

std::string EClassARRAY::classRTLname() { return "ARRAY"; }
std::string EClassARRAY::classRTLfullName() { return EClass::rtlClassPackageName() + "/" + EClassARRAY::classRTLname(); }

EClassARRAY::EClassARRAY() {
    this->_initSelf();
}

void EClassARRAY::_defineParents() { this->_parents.push_back({EClassANY::classRTLname(), {}}); }
void EClassARRAY::_defineCreators() {
    this->_creators.push_back({"MAKE_EMPTY", nullptr});
    this->_creators.push_back({"MAKE_FILLED", nullptr});
}

void EClassARRAY::_defineFeatures() {
    this->_addFeature( std::make_shared<ERoutine>(ERoutine("MAKE_EMPTY", this, EType::noType(), {}, {})) );
    this->_addFeature( std::make_shared<ERoutine>(ERoutine("MAKE_FILLED", this, EType::noType(), {{"value", EType::classType(EClassANY::classRTLname())}, {"lower", EType::intType()}, {"upper", EType::intType()}}, {})) );

    this->_addFeature( std::make_shared<ERoutine>(ERoutine("LOWER", this, EType::intType(), {}, {})) );
    this->_addFeature( std::make_shared<ERoutine>(ERoutine("UPPER", this, EType::intType(), {}, {})) );
    this->_addFeature( std::make_shared<ERoutine>(ERoutine("CAPACITY", this, EType::intType(), {}, {})) );

    this->_addFeature( std::make_shared<ERoutine>(ERoutine("GET", this, EType::classType(EClassANY::classRTLname()), {{"index", EType::intType()}}, {})) );
    this->_addFeature( std::make_shared<ERoutine>(ERoutine("SET", this, EType::noType(), {{"value", EType::classType(EClassANY::classRTLname())}, {"index", EType::intType()}}, {})) );

    this->_addFeature( std::make_shared<ERoutine>(ERoutine("ADD_FIRST", this, EType::noType(), {{"value", EType::classType(EClassANY::classRTLname())}}, {})) );
    this->_addFeature( std::make_shared<ERoutine>(ERoutine("ADD_LAST", this, EType::noType(), {{"value", EType::classType(EClassANY::classRTLname())}}, {})) );
    this->_addFeature( std::make_shared<ERoutine>(ERoutine("ADD", this, EType::noType(), {{"value", EType::classType(EClassANY::classRTLname())}, {"index", EType::intType()}}, {})) );

    this->_addFeature( std::make_shared<ERoutine>(ERoutine("REMOVE_FIRST", this, EType::noType(), {}, {})) );
    this->_addFeature( std::make_shared<ERoutine>(ERoutine("REMOVE_LAST", this, EType::noType(), {}, {})) );
    this->_addFeature( std::make_shared<ERoutine>(ERoutine("REMOVE", this, EType::noType(), {{"index", EType::intType()}}, {})) );
}

std::string EClassARRAY::name() const { return EClassARRAY::classRTLname(); }
