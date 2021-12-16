#include "econstanttable.h"

EConstantTable::JvmConstant::JvmConstant() {
	this->jvm_utf8          = nullptr;
    this->jvm_string        = -1;
    this->jvm_class         = -1;
    this->jvm_nameAndType   = { -1, -1 };
	this->jvm_fieldRef      = { -1, -1 };
	this->jvm_methodRef     = { -1, -1 };
}

bool EConstantTable::JvmConstant::operator==(const JvmConstant& other) const {
    bool result = true;

    if ((this->jvm_utf8 != nullptr && other.jvm_utf8 == nullptr) ||
        (this->jvm_utf8 == nullptr && other.jvm_utf8 != nullptr))
    {
        return false;
    }
    else if (this->jvm_utf8 != nullptr) {
        result &= (*this->jvm_utf8 == *other.jvm_utf8);
    }

    result &= (this->jvm_string == other.jvm_string);
    result &= (this->jvm_class == other.jvm_class);
    result &= (this->jvm_nameAndType == other.jvm_nameAndType);
    result &= (this->jvm_fieldRef == other.jvm_fieldRef);
    result &= (this->jvm_methodRef == other.jvm_methodRef);

    return result;
}

int EConstantTable::size() const { return this->_constants.size(); }

std::pair<EConstantTable::JvmConstantType, EConstantTable::JvmConstant> EConstantTable::getConstant(int constantIndex) const {
    if (constantIndex < 1 || constantIndex > this->_constants.size()) {
        return { jvm_invalid, EConstantTable::JvmConstant() };
    }

    return this->_constants.at(constantIndex-1);
}

short EConstantTable::searchConstant(const std::pair<JvmConstantType, JvmConstant>& constant) const {
    short result = -1;

    for (int i=0; i<this->_constants.size(); i++) {
        if (this->_constants.at(i) == constant) {
            result = i+1;
            break;
        }
    }

    return result;
}

short EConstantTable::searchClassConstBy(const std::string& classFullName) const {
    short result = -1;

    for (int i=0; i<this->_constants.size(); i++) {
        if (this->_constants.at(i).first == jvm_class &&
            *this->getConstant( this->_constants.at(i).second.jvm_class ).second.jvm_utf8 == classFullName)
        {
            result = i+1;
            break;
        }
    }

    return result;
}

short EConstantTable::searchUtf8By(const std::string& stringUtf8) const {
    short result = -1;

    for (int i=0; i<this->_constants.size(); i++) {
        if (this->_constants.at(i).first == jvm_utf8 &&
            std::string(*this->_constants.at(i).second.jvm_utf8) == stringUtf8)
        {
            result = i+1;
            break;
        }
    }

    return result;
}

short EConstantTable::appendUtf8(const std::string& stringUtf8) {
    EConstantTable::JvmConstant result;
    result.jvm_utf8 = new std::string(stringUtf8);

    int constantPos = 0;
    for (int i=0; i<this->_constants.size(); i++) {
        if (this->_constants.at(i).first == jvm_utf8 && *this->_constants.at(i).second.jvm_utf8 == stringUtf8) {
            constantPos = i+1;
        }
    }

    if (constantPos == 0) {
        this->_constants.push_back({jvm_utf8, result});
        return this->_constants.size();
    }
    else {
        return constantPos;
    }
}

short EConstantTable::appendString(short utf8Link_string) {
    EConstantTable::JvmConstant result;
    result.jvm_string = utf8Link_string;

    int constantPos = 0;
    for (int i=0; i<this->_constants.size(); i++) {
        if (this->_constants.at(i).first == jvm_string && this->_constants.at(i).second.jvm_string == utf8Link_string) {
            constantPos = i+1;
        }
    }

    if (constantPos == 0) {
        this->_constants.push_back({jvm_string, result});
        return this->_constants.size();
    }
    else {
        return constantPos;
    }
}

short EConstantTable::appendConstClass(short utf8Link_class) {
    EConstantTable::JvmConstant result;
    result.jvm_class = utf8Link_class;

    int constantPos = 0;
    for (int i=0; i<this->_constants.size(); i++) {
        if (this->_constants.at(i).first == jvm_class && this->_constants.at(i).second.jvm_class == utf8Link_class) {
            constantPos = i+1;
        }
    }

    if (constantPos == 0) {
        this->_constants.push_back({jvm_class, result});
        return this->_constants.size();
    }
    else {
        return constantPos;
    }
}

short EConstantTable::appendNameAndType(const std::pair<short, short>& utf8Links_nameAndType) {
    EConstantTable::JvmConstant result;
    result.jvm_nameAndType = utf8Links_nameAndType;

    int constantPos = 0;
    for (int i=0; i<this->_constants.size(); i++) {
        if (this->_constants.at(i).first == jvm_nameAndType && this->_constants.at(i).second.jvm_nameAndType == utf8Links_nameAndType) {
            constantPos = i+1;
        }
    }

    if (constantPos == 0) {
        this->_constants.push_back({jvm_nameAndType, result});
        return this->_constants.size();
    }
    else {
        return constantPos;
    }
}

short EConstantTable::appendFieldRef(const std::pair<short, short>& utf8Links_fieldRef) {
    EConstantTable::JvmConstant result;
    result.jvm_fieldRef = utf8Links_fieldRef;

    int constantPos = 0;
    for (int i=0; i<this->_constants.size(); i++) {
        if (this->_constants.at(i).first == jvm_fieldRef && this->_constants.at(i).second.jvm_fieldRef == utf8Links_fieldRef) {
            constantPos = i+1;
        }
    }

    if (constantPos == 0) {
        this->_constants.push_back({jvm_fieldRef, result});
        return this->_constants.size();
    }
    else {
        return constantPos;
    }
}

short EConstantTable::appendMethodRef(const std::pair<short, short>& utf8Links_methodRef) {
    EConstantTable::JvmConstant result;
    result.jvm_methodRef = utf8Links_methodRef;

    int constantPos = 0;
    for (int i=0; i<this->_constants.size(); i++) {
        if (this->_constants.at(i).first == jvm_methodRef && this->_constants.at(i).second.jvm_methodRef == utf8Links_methodRef) {
            constantPos = i+1;
        }
    }

    if (constantPos == 0) {
        this->_constants.push_back({jvm_methodRef, result});
        return this->_constants.size();
    }
    else {
        return constantPos;
    }
}
