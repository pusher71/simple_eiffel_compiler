#ifndef BYTECODE_H
#define BYTECODE_H

#include <vector>
#include <fstream>

#include "../EiffelCore/EiffelClasses/euserclass.h"
#include "../EiffelFeatureInfo/eattribute.h"

class ByteCode {
    // ================ ATTRIBUTES ================
private:
    std::vector<unsigned char> _bytes;

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
public:
    ByteCode();
    ByteCode(const EUserClass& userClass);
    ByteCode(const EConstantTable& classConstantTable);
    static ByteCode attributesMetaByteCode(const EConstantTable& userClassConstants, const EFeatureMetaInfo& featureMetaInfo);
    static ByteCode routinesMetaByteCode(const EConstantTable& userClassConstants, const EFeatureMetaInfo& featureMetaInfo);
    ByteCode(const EConstantTable& userClassConstants, const instruction_seq_strct* routineBody);

    static ByteCode defaultConstructorByteCode(const EConstantTable& userClassConstants, const EUserClass& userClass);
    static ByteCode polyMethodByteCode(const EConstantTable& userClassConstants, const EFeatureMetaInfo& featureMetaInfo);
    static ByteCode mainFunctionByteCode(const EConstantTable& userClassConstants, const EUserClass& mainClass);

private:
    ByteCode& _appendByte(unsigned char value);
    ByteCode& _appendTwoBytes(unsigned short int value);
    ByteCode& _appendFourBytes(unsigned long int value);
    ByteCode& _append(const ByteCode& other);

    // ----------------- contract -----------------
public:
    bool writeToFile(std::ofstream& outputClassFile) const;

private:
    static ByteCode iconst(signed char i); // [-1 .. 5] (7 possible values)
    static ByteCode iconst_null();

    static ByteCode bipush(char s1);
    static ByteCode sipush(short int s2);

    static ByteCode ldc(char u1);
    static ByteCode ldc_w(short int u2);
    static ByteCode iload(char u1);
    static ByteCode aload(char u1);

    static ByteCode istore(char u1);
    static ByteCode astore(char u1);

    static ByteCode pop();
    static ByteCode dup();
    static ByteCode dup2();

    static ByteCode iadd();
    static ByteCode imul();
    static ByteCode isub();
    static ByteCode ineg();
    static ByteCode idiv();
    static ByteCode iinc(char u1, signed char i);

    // Control transfer commands ...
    static ByteCode if_icmpeq(short int s2);
    static ByteCode if_icmpne(short int s2);
    static ByteCode if_icmplt(short int s2);
    static ByteCode if_icmpge(short int s2);
    static ByteCode if_icmpgt(short int s2);
    static ByteCode if_icmple(short int s2);

    static ByteCode ifeq(short int s2);
    static ByteCode ifne(short int s2);
    static ByteCode iflt(short int s2);
    static ByteCode ifle(short int s2);
    static ByteCode ifgt(short int s2);
    static ByteCode ifge(short int s2);

    static ByteCode if_acmpeq(short int s2);
    static ByteCode if_acmpne(short int s2);

    static ByteCode goto_(short int s2);

    static ByteCode newarray(char u1);
    static ByteCode anewarray(short int u2);
    static ByteCode arraylength();
    static ByteCode iaload();
    static ByteCode aaload();
    static ByteCode iastore();
    static ByteCode aastore();

    static ByteCode new_(short int u2);
    static ByteCode getfield(short int u2);
    static ByteCode putfield(short int u2);
    static ByteCode instanceof(short int u2);

    static ByteCode invokevirtual(short int u2, short int argCount, bool isVoid);
    static ByteCode invokespecial(short int u2, short int argCount, bool isVoid);
    static ByteCode invokestatic(short int u2, short int argCount, bool isVoid);
    static ByteCode ireturn();
    static ByteCode areturn();
    static ByteCode _return();
};

#endif // BYTECODE_H
