#include "jvmconstant.h"

JvmConstant::JvmConstant()
    : _type(jvm_invalid),

      _utf8_value(""),
      _integer_value(0),
      _long_value(0),
      _string_value(0),
      _constClass_value(0),
      _nameAndType_value({0, 0}),
      _fieldRef_value({0, 0}),
      _methodRef_value({0, 0})
{}

JvmConstant::JvmConstant(JvmConstantType type)
    : _type(type),

      _utf8_value(""),
      _integer_value(0),
      _long_value(0),
      _string_value(0),
      _constClass_value(0),
      _nameAndType_value({0, 0}),
      _fieldRef_value({0, 0}),
      _methodRef_value({0, 0})
{}

JvmConstant::JvmConstantType JvmConstant::type() const { return this->_type; }

JvmConstant JvmConstant::UTF8(const std::string& utf8_value) {
    JvmConstant result(JvmConstantType::jvm_utf8);
    result._utf8_value = utf8_value;

    return result;
}

JvmConstant JvmConstant::Integer(int32_t integer_value) {
    JvmConstant result(JvmConstantType::jvm_integer);
    result._integer_value = integer_value;

    return result;
}

JvmConstant JvmConstant::Long(int64_t long_value) {
    JvmConstant result(JvmConstantType::jvm_long);
    result._long_value = long_value;

    return result;
}

JvmConstant JvmConstant::String(int16_t string_value) {
    JvmConstant result(JvmConstantType::jvm_string);
    result._string_value = string_value;

    return result;
}

JvmConstant JvmConstant::ConstClass(int16_t constClass_value) {
    JvmConstant result(JvmConstantType::jvm_class);
    result._constClass_value = constClass_value;

    return result;
}

JvmConstant JvmConstant::NameAndType(const std::pair<int16_t, int16_t>& nameAndType_value) {
    JvmConstant result(JvmConstantType::jvm_nameAndType);
    result._nameAndType_value = nameAndType_value;

    return result;
}

JvmConstant JvmConstant::FieldRef(const std::pair<int16_t, int16_t>& fieldRef_value) {
    JvmConstant result(JvmConstantType::jvm_fieldRef);
    result._fieldRef_value = fieldRef_value;

    return result;
}

JvmConstant JvmConstant::MethodRef(const std::pair<int16_t, int16_t>& methodRef_value) {
    JvmConstant result(JvmConstantType::jvm_methodRef);
    result._methodRef_value = methodRef_value;

    return result;
}

std::string JvmConstant::utf8_value() const {
    if (this->_type != JvmConstant::JvmConstantType::jvm_utf8) {
        throw std::runtime_error("Failed to get UTF8 value of constant with non-UTF8 type (type code: " + std::to_string(this->_type) + ")");
    }

    return this->_utf8_value;
}

int32_t JvmConstant::integer_value() const {
    if (this->_type != JvmConstant::JvmConstantType::jvm_integer) {
        throw std::runtime_error("Failed to get Integer value of constant with non-Integer type (type code: " + std::to_string(this->_type) + ")");
    }

    return this->_integer_value;
}

int64_t JvmConstant::long_value() const {
    if (this->_type != JvmConstant::JvmConstantType::jvm_long) {
        throw std::runtime_error("Failed to get Long value of constant with non-Long type (type code: " + std::to_string(this->_type) + ")");
    }

    return this->_long_value;
}

int16_t JvmConstant::string_value() const {
    if (this->_type != JvmConstant::JvmConstantType::jvm_string) {
        throw std::runtime_error("Failed to get String value of constant with non-String type (type code: " + std::to_string(this->_type) + ")");
    }

    return this->_string_value;
}

int16_t JvmConstant::class_value() const {
    if (this->_type != JvmConstant::JvmConstantType::jvm_class) {
        throw std::runtime_error("Failed to get ConstClass value of constant with non-ConstClass type (type code: " + std::to_string(this->_type) + ")");
    }

    return this->_constClass_value;
}

std::pair<int16_t, int16_t> JvmConstant::nameAndType_value() const {
    if (this->_type != JvmConstant::JvmConstantType::jvm_nameAndType) {
        throw std::runtime_error("Failed to get NameAndType value of constant with non-NameAndType type (type code: " + std::to_string(this->_type) + ")");
    }

    return this->_nameAndType_value;
}

std::pair<int16_t, int16_t> JvmConstant::fieldRef_value() const {
    if (this->_type != JvmConstant::JvmConstantType::jvm_fieldRef) {
        throw std::runtime_error("Failed to get FieldRef value of constant with non-FieldRef type (type code: " + std::to_string(this->_type) + ")");
    }

    return this->_fieldRef_value;
}

std::pair<int16_t, int16_t> JvmConstant::methodRef_value() const {
    if (this->_type != JvmConstant::JvmConstantType::jvm_methodRef) {
        throw std::runtime_error("Failed to get MethodRef value of constant with non-MethodRef type (type code: " + std::to_string(this->_type) + ")");
    }

    return this->_methodRef_value;
}

bool JvmConstant::operator==(const JvmConstant& other) const {
    bool result = true;

    switch (this->_type) {
        case jvm_invalid:
            result = false;
            break;
        case jvm_utf8:
            result = (this->_utf8_value == other._utf8_value);
            break;
        case jvm_integer:
            result = (this->_integer_value == other._integer_value);
            break;
        case jvm_long:
            result = (this->_long_value == other._long_value);
            break;
        case jvm_string:
            result = (this->_string_value == other._string_value);
            break;
        case jvm_class:
            result = (this->_constClass_value == other._constClass_value);
            break;
        case jvm_nameAndType:
            result = (this->_nameAndType_value == other._nameAndType_value);
            break;
        case jvm_fieldRef:
            result = (this->_fieldRef_value == other._fieldRef_value);
            break;
        case jvm_methodRef:
            result = (this->_methodRef_value == other._methodRef_value);
            break;
    }

    return result;
}
