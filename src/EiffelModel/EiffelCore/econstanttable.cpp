#include "econstanttable.h"

EConstantTable::EConstantTable()
    : _nextAvailableIndex(1)
{}

std::map<int16_t, JvmConstant> EConstantTable::constants() const { return this->_constants; }

int16_t EConstantTable::size() const { return this->_nextAvailableIndex-1; }

int16_t EConstantTable::append(const JvmConstant& jvmConstant) {
    if (jvmConstant.type() == JvmConstant::jvm_invalid) { throw std::runtime_error("Try to assign an invalid constant to the constant table"); }

    // Try to find constant in the constant table
    for (const auto& constInfo : this->_constants) {
        if (constInfo.second == jvmConstant) { return constInfo.first; }
    }

    // Append constant to the constant table if it wasn't found
    int constantPos = this->_nextAvailableIndex++;
    if (jvmConstant.type() == JvmConstant::jvm_long) { this->_nextAvailableIndex++; }

    this->_constants[constantPos] = jvmConstant;

    return constantPos;
}

short EConstantTable::appendConstClass(const std::string& classFullName) {
    int16_t className_constLink = this->append(JvmConstant::UTF8(classFullName));
    return this->append(JvmConstant::ConstClass(className_constLink));
}

int16_t EConstantTable::appendString(const std::string& stringValue) {
    int16_t stringValue_constLink = this->append(JvmConstant::UTF8(stringValue));
    return this->append(JvmConstant::String(stringValue_constLink));
}

short EConstantTable::appendFieldRef(const std::string& classFullName, const std::string& fieldName, const std::string& fieldDescriptor) {
    int16_t className_constLink         = this->append(JvmConstant::UTF8(classFullName));
    int16_t constClass_constLink        = this->append(JvmConstant::ConstClass(className_constLink));

    int16_t fieldName_constLink         = this->append(JvmConstant::UTF8(fieldName));
    int16_t fieldDescriptor_constLink   = this->append(JvmConstant::UTF8(fieldDescriptor));
    int16_t fieldNameAndType_constLink  = this->append(JvmConstant::NameAndType({fieldName_constLink, fieldDescriptor_constLink}));

    return this->append(JvmConstant::FieldRef({constClass_constLink, fieldNameAndType_constLink}));
}

short EConstantTable::appendMethodRef(const std::string& classFullName, const std::string& methodName, const std::string& methodDescriptor) {
    int16_t className_constLink         = this->append(JvmConstant::UTF8(classFullName));
    int16_t constClass_constLink        = this->append(JvmConstant::ConstClass(className_constLink));

    int16_t methodName_constLink        = this->append(JvmConstant::UTF8(methodName));
    int16_t methodDescriptor_constLink  = this->append(JvmConstant::UTF8(methodDescriptor));
    int16_t methodNameAndType_constLink = this->append(JvmConstant::NameAndType({methodName_constLink, methodDescriptor_constLink}));

    int16_t result = this->append(JvmConstant::MethodRef({constClass_constLink, methodNameAndType_constLink}));
    return result;
}

JvmConstant EConstantTable::getConstant(int constantIndex) const { return this->_constants.at(constantIndex); }

int16_t EConstantTable::searchUTF8By(const std::string& stringUTF8) const {
    for (const auto& constInfo : this->_constants) {
        if (constInfo.second.type() == JvmConstant::jvm_utf8 &&
            constInfo.second.utf8_value() == stringUTF8)
        {
            return constInfo.first;
        }
    }

    return 0;
}

int16_t EConstantTable::searchClassConstBy(const std::string& classFullName) const {
    for (const auto& constInfo : this->_constants) {
        if (constInfo.second.type() == JvmConstant::jvm_class &&
            this->_constants.at( constInfo.second.class_value() ).utf8_value() == classFullName) {
            return constInfo.first;
        }
    }

    return 0;
}

int16_t EConstantTable::searchFieldRefBy(const std::string& classFullName, const std::string& fieldName, const std::string& fieldDescriptor) const {
    for (const auto& constInfo : this->_constants) {
        if (constInfo.second.type() == JvmConstant::jvm_fieldRef) {
            const auto& fieldRefInfo = constInfo.second.fieldRef_value();
            int16_t constClass_constLink = this->_constants.at(fieldRefInfo.first).class_value();
            std::string classFullNameInConstTable = this->_constants.at(constClass_constLink).utf8_value();

            const auto& nameAndTypeInfo = this->_constants.at(fieldRefInfo.second).nameAndType_value();
            std::string fieldNameInConstTable = this->_constants.at(nameAndTypeInfo.first).utf8_value();
            std::string fieldDescriptorInConstTable = this->_constants.at(nameAndTypeInfo.second).utf8_value();

            if (classFullNameInConstTable == classFullName && fieldNameInConstTable == fieldName && fieldDescriptorInConstTable == fieldDescriptor) {
                return constInfo.first;
            }
        }
    }

    return 0;
}

int16_t EConstantTable::searchMethodRefBy(const std::string& classFullName, const std::string& methodName, const std::string& methodDescriptor) const {
    for (const auto& constInfo : this->_constants) {
        if (constInfo.second.type() == JvmConstant::jvm_methodRef) {
            const auto& methodRefInfo = constInfo.second.methodRef_value();
            int16_t constClass_constLink = this->_constants.at(methodRefInfo.first).class_value();
            std::string classFullNameInConstTable = this->_constants.at(constClass_constLink).utf8_value();

            const auto& nameAndTypeInfo = this->_constants.at(methodRefInfo.second).nameAndType_value();
            std::string methodNameInConstTable = this->_constants.at(nameAndTypeInfo.first).utf8_value();
            std::string methodDescriptorInConstTable = this->_constants.at(nameAndTypeInfo.second).utf8_value();

            if (classFullNameInConstTable == classFullName && methodNameInConstTable == methodName && methodDescriptorInConstTable == methodDescriptor) {
                return constInfo.first;
            }
        }
    }

    return 0;
}
