#include "econstanttable.h"

std::pair<EConstantTable::JvmConstantType, EConstantTable::JvmConstant> EConstantTable::getConstant(int constantIndex) {
    union EConstantTable::JvmConstant result = { .jvm_utf8=nullptr };

    if (constantIndex < 1 || constantIndex > this->_constants.size()) {
        return { jvm_invalid, { .jvm_utf8 = nullptr } };
    }

    return this->_constants[constantIndex-1];
}

void EConstantTable::appendUtf8(const std::string& stringUtf8) {
    this->_constants.push_back({ jvm_utf8, { .jvm_utf8 = new std::string(stringUtf8) } });
}

void EConstantTable::appendString(short utf8Link_string) {
    this->_constants.push_back({ jvm_string, { .jvm_string = utf8Link_string } });
}

void EConstantTable::appendConstClass(short utf8Link_string) {
    this->_constants.push_back({ jvm_class, { .jvm_string = utf8Link_string } });
}

void EConstantTable::appendNameAndType(const std::pair<short, short>& utf8Links_nameAndType) {
    this->_constants.push_back({ jvm_nameAndType, { .jvm_nameAndType = utf8Links_nameAndType } });
}

void EConstantTable::appendFieldRef(const std::pair<short, short>& utf8Links_fieldRef) {
    this->_constants.push_back({ jvm_fieldRef, { .jvm_fieldRef = utf8Links_fieldRef } });
}

void EConstantTable::appendMethodRef(const std::pair<short, short>& utf8Links_methodRef) {
    this->_constants.push_back({ jvm_methodRef, { .jvm_methodRef = utf8Links_methodRef } });
}
