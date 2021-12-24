#include "eclassconsoleio.h"

#include "../../../EiffelFeatureInfo/eattribute.h"
#include "../../../EiffelFeatureInfo/eroutine.h"

std::string EClassCONSOLEIO::classRTLname() { return "CONSOLEIO"; }

EClassCONSOLEIO::EClassCONSOLEIO() {
    this->_initSelf();
}

void EClassCONSOLEIO::_defineParents() {}
void EClassCONSOLEIO::_defineCreators() {}
void EClassCONSOLEIO::_defineFeatures() {
    std::vector<EFeature> features;

    this->_addFeature( std::make_shared<ERoutine>(ERoutine("put_boolean", this, EType::voidType(), {{"input_value", EType::boolType()}}, {})) );
    this->_addFeature( std::make_shared<ERoutine>(ERoutine("put_integer", this, EType::voidType(), {{"input_value", EType::intType()}}, {})) );
    this->_addFeature( std::make_shared<ERoutine>(ERoutine("put_character", this, EType::voidType(), {{"input_value", EType::charType()}}, {})) );
    this->_addFeature( std::make_shared<ERoutine>(ERoutine("put_string", this, EType::voidType(), {{"input_value", EType::stringType()}}, {})) );
    this->_addFeature( std::make_shared<ERoutine>(ERoutine("new_line", this, EType::voidType(), {}, {})) );

    this->_addFeature( std::make_shared<ERoutine>(ERoutine("read_boolean", this, EType::voidType(), {}, {})) );
    this->_addFeature( std::make_shared<ERoutine>(ERoutine("read_integer", this, EType::voidType(), {}, {})) );
    this->_addFeature( std::make_shared<ERoutine>(ERoutine("read_character", this, EType::voidType(), {}, {})) );
    this->_addFeature( std::make_shared<ERoutine>(ERoutine("read_line", this, EType::voidType(), {}, {})) );

    this->_addFeature( std::make_shared<EAttribute>(EAttribute("last_boolean", this, EType::boolType())) );
    this->_addFeature( std::make_shared<EAttribute>(EAttribute("last_integer", this, EType::intType())) );
    this->_addFeature( std::make_shared<EAttribute>(EAttribute("last_character", this, EType::charType())) );
    this->_addFeature( std::make_shared<EAttribute>(EAttribute("last_string", this, EType::stringType())) );
}

std::string EClassCONSOLEIO::name() const { return EClassCONSOLEIO::classRTLname(); }
