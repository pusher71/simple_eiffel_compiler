#include "eclassconsoleio.h"

#include "../../EiffelFeatureInfo/eattribute.h"
#include "../../EiffelFeatureInfo/eroutine.h"

EClassCONSOLEIO::EClassCONSOLEIO() {
    this->_initSelf();
}

void EClassCONSOLEIO::_defineParents() {}
void EClassCONSOLEIO::_defineCreators() {}
void EClassCONSOLEIO::_defineFeatures() {
    std::vector<EFeature> features;

    this->_features["put_boolean"]      = std::make_shared<ERoutine>( ERoutine("put_boolean", this, EType::voidType(), {{"input_value", EType::boolType()}}, {}) );
    this->_features["put_integer"]      = std::make_shared<ERoutine>( ERoutine("put_integer", this, EType::voidType(), {{"input_value", EType::intType()}}, {}) );
    this->_features["put_character"]    = std::make_shared<ERoutine>( ERoutine("put_character", this, EType::voidType(), {{"input_value", EType::charType()}}, {}) );
    this->_features["put_string"]       = std::make_shared<ERoutine>( ERoutine("put_string", this, EType::voidType(), {{"input_value", EType::stringType()}}, {}) );
    this->_features["new_line"]         = std::make_shared<ERoutine>( ERoutine("new_line", this, EType::voidType(), {}, {}) );

    this->_features["read_boolean"]     = std::make_shared<ERoutine>( ERoutine("read_boolean", this, EType::voidType(), {}, {}) );
    this->_features["read_integer"]     = std::make_shared<ERoutine>( ERoutine("read_integer", this, EType::voidType(), {}, {}) );
    this->_features["read_character"]   = std::make_shared<ERoutine>( ERoutine("read_character", this, EType::voidType(), {}, {}) );
    this->_features["read_line"]        = std::make_shared<ERoutine>( ERoutine("read_line", this, EType::voidType(), {}, {}) );

    this->_features["last_boolean"]     = std::make_shared<EAttribute>( EAttribute("last_boolean", this, EType::boolType()) );
    this->_features["last_integer"]     = std::make_shared<EAttribute>( EAttribute("last_integer", this, EType::intType()) );
    this->_features["last_character"]   = std::make_shared<EAttribute>( EAttribute("last_character", this, EType::charType()) );
    this->_features["last_string"]      = std::make_shared<EAttribute>( EAttribute("last_string", this, EType::stringType()) );
}

std::string EClassCONSOLEIO::name() const { return "CONSOLEIO"; }
