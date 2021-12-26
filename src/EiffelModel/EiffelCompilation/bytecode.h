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

    static ByteCode defaultConstructorByteCode(const EConstantTable& userClassConstants, const EUserClass& userClass);
    static ByteCode polyMethodByteCode(const EConstantTable& userClassConstants, const EFeatureMetaInfo& featureMetaInfo);
    static ByteCode mainFunctionByteCode(const EConstantTable& userClassConstants, const EUserClass& mainClass);

    ByteCode(const EConstantTable& userClassConstants, const instruction_seq_strct* routineBody);
    ByteCode(const EConstantTable& userClassConstants, const instruction_strct* instruction);
    static ByteCode createInstructionByteCode(const EConstantTable& userClassConstants, const instruction_strct* createInstruction);
    static ByteCode assignInstructionByteCode(const EConstantTable& userClassConstants, const instruction_strct* assignInstruction);
    static ByteCode ifInstructionByteCode(const EConstantTable& userClassConstants, const instruction_strct* ifInstruction);
    static ByteCode loopInstructionByteCode(const EConstantTable& userClassConstants, const instruction_strct* loopInstruction);
    ByteCode(const EConstantTable& userClassConstants, const expr_strct* expression);
    static ByteCode literExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression);
    static ByteCode currentExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression);

    static ByteCode exprCallSelffeatureByteCode(const EConstantTable& userClassConstants, const expr_strct* expression);
    static ByteCode exprCallPrecursorByteCode(const EConstantTable& userClassConstants, const expr_strct* expression);
    static ByteCode exprCallSubcallByteCode(const EConstantTable& userClassConstants, const expr_strct* expression);
    static ByteCode createExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression);

    static ByteCode arrElemExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression);
    static ByteCode plusExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression);
    static ByteCode binminusExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression);
    static ByteCode mulExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression);
    static ByteCode idivExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression);
    static ByteCode unminusExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression);

    static ByteCode lessExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression);
    static ByteCode greatExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression);
    static ByteCode lessequalExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression);
    static ByteCode greatequalExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression);
    static ByteCode equalExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression);
    static ByteCode notequalExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression);

    static ByteCode andExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression);
    static ByteCode orExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression);
    static ByteCode notExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression);
    static ByteCode xorExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression);

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
    static ByteCode const_null();

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
    static ByteCode checkcast(short int u2);

    static ByteCode invokevirtual(short int u2, short int argCount);
    static ByteCode invokespecial(short int u2, short int argCount);
    static ByteCode invokestatic(short int u2, short int argCount);
    static ByteCode ireturn();
    static ByteCode areturn();
    static ByteCode _return();
};

#endif // BYTECODE_H
