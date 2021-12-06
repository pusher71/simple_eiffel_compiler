#include "econstanttable.h"

EConstantTable::JvmConstant::JvmConstant() {
	this->jvm_utf8          = nullptr;
    this->jvm_string        = -1;
    this->jvm_class         = -1;
    this->jvm_nameAndType   = { -1, -1 };
	this->jvm_fieldRef      = { -1, -1 };
	this->jvm_methodRef     = { -1, -1 };
}

std::pair<EConstantTable::JvmConstantType, EConstantTable::JvmConstant> EConstantTable::getConstant(int constantIndex) {
    if (constantIndex < 1 || constantIndex > this->_constants.size()) {
        return { jvm_invalid, EConstantTable::JvmConstant() };
    }

    return this->_constants[constantIndex-1];
}

void EConstantTable::appendUtf8(const std::string& stringUtf8) {
    EConstantTable::JvmConstant result;
    result.jvm_utf8 = new std::string(stringUtf8);

    this->_constants.push_back({jvm_utf8, result});
}

void EConstantTable::appendString(short utf8Link_string) {
    EConstantTable::JvmConstant result;
    result.jvm_string = utf8Link_string;

    this->_constants.push_back({jvm_string, result});
}

void EConstantTable::appendConstClass(short utf8Link_class) {
    EConstantTable::JvmConstant result;
    result.jvm_class = utf8Link_class;

    this->_constants.push_back({jvm_class, result});
}

void EConstantTable::appendNameAndType(const std::pair<short, short>& utf8Links_nameAndType) {
    EConstantTable::JvmConstant result;
    result.jvm_nameAndType = utf8Links_nameAndType;

    this->_constants.push_back({jvm_nameAndType, result});
}

void EConstantTable::appendFieldRef(const std::pair<short, short>& utf8Links_fieldRef) {
    EConstantTable::JvmConstant result;
    result.jvm_fieldRef = utf8Links_fieldRef;

    this->_constants.push_back({jvm_fieldRef, result});
}

void EConstantTable::appendMethodRef(const std::pair<short, short>& utf8Links_methodRef) {
    EConstantTable::JvmConstant result;
    result.jvm_methodRef = utf8Links_methodRef;

    this->_constants.push_back({jvm_methodRef, result});
}
