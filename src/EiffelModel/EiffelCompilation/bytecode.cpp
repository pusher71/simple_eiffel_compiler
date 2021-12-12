#include "bytecode.h"
#include "../EiffelCore/eclass.h"

ByteCode::ByteCode() {}

#include <iostream>

ByteCode::ByteCode(const EUserClass* userClass) {
    // Main bytecode values
    this->_appendFourBytes(0xCAFEBABE);     // "Magic" java constant
    this->_appendTwoBytes(0x0000);          // Minor version of java
    this->_appendTwoBytes(0x003C);          // Major version of java

    // Bytecode of constant table
    ByteCode constantTableByteCode(userClass->_constants);
    this->_append(constantTableByteCode);

    // Self class info
    this->_appendTwoBytes(0x0001);          // Access flags (0x0001 - PUBLIC class)
    this->_appendTwoBytes(userClass->_constants.searchClassConstBy(userClass->fullName())); // Link to self constant class in constant table
    this->_appendTwoBytes(userClass->_constants.searchClassConstBy(EClass::javaObjectFullName())); // Link to parent constantn class in constant table (java.lang.Object is parent)
    this->_appendTwoBytes(0x0000);          // Count of interfaces which class implements

    // Fields info
    const auto& userClassAttributesInfo = userClass->attributes();
    this->_appendTwoBytes(userClassAttributesInfo.size());

    for (const auto& attributeInfo : userClassAttributesInfo) {
        ByteCode attributeByteCode(userClass->_constants, (EAttribute*)attributeInfo.second.get());
        this->_append(attributeByteCode);
    }

    // Methods info
    const auto& userClassRoutinesInfo = userClass->routines();
    this->_appendTwoBytes(userClassRoutinesInfo.size());

    for (const auto& routineInfo : userClassRoutinesInfo) {
        ByteCode routineByteCode(userClass->_constants, (ERoutine*)routineInfo.second.get());
        this->_append(routineByteCode);
    }

    // Class attributes info
    this->_appendTwoBytes(0x0000); // Class attributes count
}

ByteCode::ByteCode(const EConstantTable& classConstantTable) {
    this->_appendTwoBytes(classConstantTable.size()+1);

    for (int i=1; i<=classConstantTable.size(); i++) {
        const auto& jvmConstantInfo = classConstantTable.getConstant(i);

        this->_appendByte(jvmConstantInfo.first);

        std::vector<char> stringBytes;
        switch (jvmConstantInfo.first) {
            case EConstantTable::jvm_utf8:
                this->_appendTwoBytes(jvmConstantInfo.second.jvm_utf8->length());

                stringBytes = std::vector<char>(jvmConstantInfo.second.jvm_utf8->begin(), jvmConstantInfo.second.jvm_utf8->end());
                for (char stringByte : stringBytes) {
                    this->_appendByte(stringByte);
                }
                break;

            case EConstantTable::jvm_string:
                this->_appendTwoBytes(jvmConstantInfo.second.jvm_string);
                break;

            case EConstantTable::jvm_class:
                this->_appendTwoBytes(jvmConstantInfo.second.jvm_class);
                break;

            case EConstantTable::jvm_nameAndType:
                this->_appendTwoBytes(jvmConstantInfo.second.jvm_nameAndType.first);
                this->_appendTwoBytes(jvmConstantInfo.second.jvm_nameAndType.second);
                break;

            case EConstantTable::jvm_fieldRef:
                this->_appendTwoBytes(jvmConstantInfo.second.jvm_fieldRef.first);
                this->_appendTwoBytes(jvmConstantInfo.second.jvm_fieldRef.second);
                break;

            case EConstantTable::jvm_methodRef:
                this->_appendTwoBytes(jvmConstantInfo.second.jvm_methodRef.first);
                this->_appendTwoBytes(jvmConstantInfo.second.jvm_methodRef.second);
                break;

            default:
                break;
        }
    }
}

ByteCode::ByteCode(const EConstantTable& userClassConstants, const EAttribute* classAttribute) {
    this->_appendTwoBytes(0x0001);
    this->_appendTwoBytes(classAttribute->name_utf8Link());
    this->_appendTwoBytes(classAttribute->descriptor_utf8Link());
    this->_appendTwoBytes(0x0000);
}

ByteCode::ByteCode(const EConstantTable& userClassConstants, const ERoutine* classRoutine) {
    this->_appendTwoBytes(0x0001);
    this->_appendTwoBytes(classRoutine->name_utf8Link());
    this->_appendTwoBytes(classRoutine->descriptor_utf8Link());
    this->_appendTwoBytes(0x0001);

    // "Code" attribute of method
    ByteCode codeAttribute;
    codeAttribute._appendTwoBytes(0x1000);
    codeAttribute._appendTwoBytes((short)classRoutine->_formalParameters.size() + (short)classRoutine->_localVariables.size() + 1);

    ByteCode routineBodyCode(userClassConstants, classRoutine->_routineBody);

    codeAttribute._appendFourBytes((unsigned long)routineBodyCode._bytes.size());
    codeAttribute._append(routineBodyCode);
    codeAttribute._appendTwoBytes(0x0000);

    this->_appendTwoBytes(0x0001);
    this->_appendFourBytes((unsigned long)codeAttribute._bytes.size());
    this->_append(codeAttribute);
}

ByteCode::ByteCode(const EConstantTable& userClassConstants, const instruction_seq_strct* routineBody) {
    this->_appendByte(0xB1);
}

ByteCode& ByteCode::_appendByte(unsigned char value) {
    this->_bytes.push_back(value);
    return *this;
}

ByteCode& ByteCode::_appendTwoBytes(unsigned short int value) {
    for (int i=1; i>=0; i--) {
        unsigned char eachByte = *(((char*)(&value)) + i);
        this->_bytes.push_back(eachByte);
    }

    return *this;
}

ByteCode& ByteCode::_appendFourBytes(unsigned long int value) {
    for (int i=3; i>=0; i--) {
        unsigned char eachByte = *(((char*)(&value)) + i);
        this->_bytes.push_back(eachByte);
    }

    return *this;
}

ByteCode& ByteCode::_append(const ByteCode& other) {
    for (char byteValue : other._bytes) {
        this->_bytes.push_back(byteValue);
    }

    return *this;
}

bool ByteCode::writeToFile(std::ofstream& outputClassFile) const {
    if (outputClassFile.is_open()) {
        outputClassFile.clear();

        for (char byteValue : this->_bytes) {
            outputClassFile.write(reinterpret_cast<char*>(&byteValue), sizeof(byteValue));
        }

        return true;
    }
    else {
        return false;
    }
}

/*
=== EXAMPLE OF BYTE CODE STRUCTURE =======

    this->_appendFourBytes(0xCAFEBABE);     // "Magic" java constant
    this->_appendTwoBytes(0x0000);          // Minor version of java
    this->_appendTwoBytes(0x003C);          // Major version of java

    // Bytecode of constant table
    ((EUserClass*)userClass)->_constants.appendUtf8("<init>");
    ((EUserClass*)userClass)->_constants.appendUtf8("()V");
    ((EUserClass*)userClass)->_constants.appendNameAndType({19, 20});
    ((EUserClass*)userClass)->_constants.appendUtf8("java/lang/Object");
    ((EUserClass*)userClass)->_constants.appendConstClass(22);
    ((EUserClass*)userClass)->_constants.appendMethodRef({23, 21});
    ((EUserClass*)userClass)->_constants.appendUtf8("<init>");
    ((EUserClass*)userClass)->_constants.appendUtf8("()V");
    ((EUserClass*)userClass)->_constants.appendNameAndType({6, 7});
    ((EUserClass*)userClass)->_constants.appendMethodRef({5, 8});

    ((EUserClass*)userClass)->_constants.appendUtf8("main");
    ((EUserClass*)userClass)->_constants.appendUtf8("([Ljava/lang/String;)V");
    ((EUserClass*)userClass)->_constants.appendUtf8("java/lang/System");
    ((EUserClass*)userClass)->_constants.appendConstClass(12);
    ((EUserClass*)userClass)->_constants.appendUtf8("out");
    ((EUserClass*)userClass)->_constants.appendUtf8("Ljava/io/PrintStream;");
    ((EUserClass*)userClass)->_constants.appendNameAndType({14, 15});
    ((EUserClass*)userClass)->_constants.appendFieldRef({13, 16});
    ((EUserClass*)userClass)->_constants.appendUtf8("java/io/PrintStream");
    ((EUserClass*)userClass)->_constants.appendConstClass(18);
    ((EUserClass*)userClass)->_constants.appendUtf8("println");
    ((EUserClass*)userClass)->_constants.appendUtf8("(Ljava/lang/String;)V");
    ((EUserClass*)userClass)->_constants.appendNameAndType({20, 21});
    ((EUserClass*)userClass)->_constants.appendMethodRef({19, 22});
    ((EUserClass*)userClass)->_constants.appendUtf8("Hello! It\'s me, " + userClass->fullName() + "!\n");
    ((EUserClass*)userClass)->_constants.appendString(24);

    ByteCode constantTableByteCode(&userClass->_constants);
    this->_append(constantTableByteCode);

    // Self class info
    this->_appendTwoBytes(0x0001);          // Access flags (0x0001 - PUBLIC class)
    this->_appendTwoBytes(userClass->_constants.searchClassConstBy(userClass->fullName())); // Link to self constant class in constant table
    this->_appendTwoBytes(userClass->_constants.searchClassConstBy(EClass::javaObjectFullName())); // Link to parent constantn class in constant table (java.lang.Object is parent)
    this->_appendTwoBytes(0x0000);          // Count of interfaces which class implements
    // Fields info
    this->_appendTwoBytes(0x0000);

    // Methods info
    this->_appendTwoBytes(0x0002); // Methods count

    // Default constructor ...
    // ... Main settings
    this->_appendTwoBytes(0x0001);  // Access flags (PUBLIC)
    this->_appendTwoBytes(0x0006);  // Link to utf8 string with name of method
    this->_appendTwoBytes(0x0007);  // Link to utf8 string with descriptor of method
    this->_appendTwoBytes(0x0001);  // Attributes count
    this->_appendTwoBytes(0x0001);  // Attribute index ("Code" attribute)
    this->_appendFourBytes(0x0011); // Attribute length (in bytes)
    this->_appendTwoBytes(0x0080); // max stack size (in bytes)
    this->_appendTwoBytes(0x0080); // max local size (in bytes)
    this->_appendFourBytes(0x5); // "Code" length (in bytes)

    // ... Code
    // Aload "this"
    this->_appendByte(0x2A);

    // Invokespecial
    this->_appendByte(0xB7);
    this->_appendTwoBytes(0x0009);

    // Return
    this->_appendByte(0xB1);

    // ... End of method
    this->_appendTwoBytes(0x0000); // Length of exception (in bytes)
    this->_appendTwoBytes(0x0000); // Attributes count

    // "main" function
    // ... Main settings
    this->_appendTwoBytes(0x0009);  // Access flags (PUBLIC + STATIC)
    this->_appendTwoBytes(0x000A);  // Link to utf8 string with name of method
    this->_appendTwoBytes(0x000B);  // Link to utf8 string with descriptor of method
    this->_appendTwoBytes(0x0001);  // Attributes count
    this->_appendTwoBytes(0x0001);  // Attribute index ("Code" attribute)
    this->_appendFourBytes(0x15);   // Attribute length (in bytes)
    this->_appendTwoBytes(0x0010);  // max stack size (in bytes)
    this->_appendTwoBytes(0x0010);  // max local size (in bytes)
    this->_appendFourBytes(0x09);   // "Code" length (in bytes)

    // ... Code
    // Getstatic "out"
    this->_appendByte(0xB2);
    this->_appendTwoBytes(0x0011);

    // Ldc "string"
    this->_appendByte(0x12);
    this->_appendByte(0x19);

    // Invokevirtual
    this->_appendByte(0xB6);
    this->_appendTwoBytes(0x0017);

    // Return
    this->_appendByte(0xB1);

    // ... End of method
    this->_appendTwoBytes(0x0000); // Length of exception (in bytes)
    this->_appendTwoBytes(0x0000); // Attributes count

    this->_appendTwoBytes(0x0000); // Class attributes count

*/
