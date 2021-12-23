#ifndef EMETHOD_H
#define EMETHOD_H

#include <string>
#include <map>

#include "../EiffelCore/efeature.h"
#include "einnervariable.h"
#include "../../bison/tree_nodes.h"

class ByteCode;

class ERoutine : public EFeature {
    // ================ MY FRIENDS ================
    friend ByteCode;

    // ================ ATTRIBUTES ================
private:
    instruction_seq_strct*      _routineBody;

    EInnerVariable              _current;
    std::map<std::string, EInnerVariable> _formalParameters;
    std::map<std::string, EInnerVariable> _localVariables;

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
public:
    ERoutine(const std::string& featureName, EUserClass* ownerClass, feature_decl_strct* featureDecl);
    ERoutine(const std::string&                                 featureName,
             const EClass*                                      ownerClass,
             const EType&                                       returnType,
             const std::vector<std::pair<std::string, EType>>&  formalParameters,
             const std::vector<std::pair<std::string, EType>>&  localVariables);

    ~ERoutine() override;

private:
    void _defineFormalParameters(const ids_with_type_seq_strct* formalParameters);
    void _defineLocalVariables(const ids_with_type_seq_strct* localVariables);

    // ---------------- attributes ----------------
public:
    EFeatureType featureType() const override;

    const EInnerVariable* getInnerVar(short index) const;
    std::map<std::string, EInnerVariable> formalParameters() const;

    unsigned short formalParamsCount() const;

    std::string descriptor() const override;

    // ----------------- contract -----------------
public:
    void validateDataTypes() override;
    void checkOnInnerVarsNameClashing() const;

private:
    void _validateFormalParamDataTypes() const;
    void _validateLocalVarDataTypes() const;

    void _checkOnFormalParamNameClashing() const;
    void _checkOnLocalVarNameClashing() const;

public:
    void resolveBody();

private:
    void _resolveInstruction(EUserClass& userClass, instruction_strct* instruction);
    void _resolveCreateInstruction(EUserClass& userClass, instruction_strct* createInstruction);
    void _resolveAssignInstruction(EUserClass& userClass, instruction_strct* assignInstruction);
    void _resolveIfInstruction(EUserClass& userClass, instruction_strct* ifInstruction);
    void _resolveLoopInstruction(EUserClass& userClass, instruction_strct* loopInstruction);
    void _resolveInstructionAsExpr(EUserClass& userClass, instruction_strct* instructionAsExpr);

    void _resolveExpr(EUserClass& userClass, expr_strct* expr);

public:
    bool isConformingTo(const EFeature& other) const override;

    // ---------------- additional ----------------
public:
    std::string toString() const override;
};

#endif // EMETHOD_H
