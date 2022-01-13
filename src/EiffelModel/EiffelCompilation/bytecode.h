#ifndef BYTECODE_H
#define BYTECODE_H

#include <vector>
#include <fstream>
#include <cstring>
#include <string.h>

#include "../EiffelCore/EiffelClasses/euserclass.h"
#include "../EiffelFeatureInfo/eattribute.h"

class EClassRTL;

class ByteCode {
    // ================ MY FRIENDS ================
    friend EClassRTL;

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

    ByteCode(const EConstantTable&                                                  userClassConstants,
             const ERoutine*                                                        routineInfo,
             const std::map<const instruction_strct*, ERoutine::InstructionInfo>&   instructionInfo,
             const std::map<const expr_strct*, ERoutine::ExpressionInfo>&           expressionInfo);

    ByteCode(const EConstantTable&                                                  userClassConstants,
             const instruction_strct*                                               instruction,
             const std::map<const instruction_strct*, ERoutine::InstructionInfo>&   instructionInfo,
             const std::map<const expr_strct*, ERoutine::ExpressionInfo>&           expressionInfo);

    static ByteCode createInstructionByteCode(const EConstantTable&                                                 userClassConstants,
                                              const instruction_strct*                                              createInstruction,
                                              const std::map<const instruction_strct*, ERoutine::InstructionInfo>&  instructionInfo,
                                              const std::map<const expr_strct*, ERoutine::ExpressionInfo>&          expressionInfo);

    static ByteCode assignInstructionByteCode(const EConstantTable&                                                 userClassConstants,
                                              const instruction_strct*                                              assignInstruction,
                                              const std::map<const instruction_strct*, ERoutine::InstructionInfo>&  instructionInfo,
                                              const std::map<const expr_strct*, ERoutine::ExpressionInfo>&          expressionInfo);

    static ByteCode ifInstructionByteCode(const EConstantTable&                                                     userClassConstants,
                                          const instruction_strct*                                                  ifInstruction,
                                          const std::map<const instruction_strct*, ERoutine::InstructionInfo>&      instructionInfo,
                                          const std::map<const expr_strct*, ERoutine::ExpressionInfo>&              expressionInfo);

    static ByteCode loopInstructionByteCode(const EConstantTable&                                                   userClassConstants,
                                            const instruction_strct*                                                ifInstruction,
                                            const std::map<const instruction_strct*, ERoutine::InstructionInfo>&    instructionInfo,
                                            const std::map<const expr_strct*, ERoutine::ExpressionInfo>&            expressionInfo);

    ByteCode(const EConstantTable& userClassConstants, const expr_strct* expression, const std::map<const expr_strct*, ERoutine::ExpressionInfo>& expressionInfo);
    static ByteCode literExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression, const std::map<const expr_strct*, ERoutine::ExpressionInfo>& expressionInfo);
    static ByteCode currentExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression, const std::map<const expr_strct*, ERoutine::ExpressionInfo>& expressionInfo);

    static ByteCode exprCallSelffeatureByteCode(const EConstantTable& userClassConstants, const expr_strct* expression, const std::map<const expr_strct*, ERoutine::ExpressionInfo>& expressionInfo);
    static ByteCode exprCallSubcallByteCode(const EConstantTable& userClassConstants, const expr_strct* expression, const std::map<const expr_strct*, ERoutine::ExpressionInfo>& expressionInfo);
    static ByteCode createExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression, const std::map<const expr_strct*, ERoutine::ExpressionInfo>& expressionInfo);
    static ByteCode argumentsByteCode(const EConstantTable& userClassConstants, const argument_seq_strct* argumentsSeq, const std::map<const expr_strct*, ERoutine::ExpressionInfo>& expressionInfo, int16_t& argumentsCount);

    static ByteCode arrElemExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression, const std::map<const expr_strct*, ERoutine::ExpressionInfo>& expressionInfo);
    static ByteCode binArithmExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression, const std::map<const expr_strct*, ERoutine::ExpressionInfo>& expressionInfo);
    static ByteCode unArithmExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression, const std::map<const expr_strct*, ERoutine::ExpressionInfo>& expressionInfo);

    static ByteCode compareExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression, const std::map<const expr_strct*, ERoutine::ExpressionInfo>& expressionInfo);
    static ByteCode equalityCompareExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression, const std::map<const expr_strct*, ERoutine::ExpressionInfo>& expressionInfo);

    static ByteCode binLogicExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression, const std::map<const expr_strct*, ERoutine::ExpressionInfo>& expressionInfo);
    static ByteCode unLogicExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression, const std::map<const expr_strct*, ERoutine::ExpressionInfo>& expressionInfo);

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
    static ByteCode i2l();

    static ByteCode ldc(char u1);
    static ByteCode ldc_w(short int u2);
    static ByteCode ldc2_w(short int u2);
    static ByteCode iload(char u1);
    static ByteCode aload(char u1);

    static ByteCode istore(char u1);
    static ByteCode astore(char u1);

    static ByteCode pop();
    static ByteCode dup();
    static ByteCode dup2();

    static ByteCode ladd();
    static ByteCode lmul();
    static ByteCode lsub();
    static ByteCode lneg();
    static ByteCode ldiv();
    static ByteCode iinc(char u1, signed char i);
    static ByteCode lcmp();

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
    static ByteCode athrow();

    static ByteCode invokevirtual(short int u2, short int argCount);
    static ByteCode invokespecial(short int u2, short int argCount);
    static ByteCode invokestatic(short int u2, short int argCount);
    static ByteCode _return();
    static ByteCode ireturn();
    static ByteCode lreturn();
    static ByteCode areturn();
};

#endif // BYTECODE_H
