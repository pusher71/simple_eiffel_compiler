#ifndef EMETHOD_H
#define EMETHOD_H

#include <string>
#include <map>

#include "../EiffelCore/efeature.h"
#include "../EiffelCore/efeaturemetainfo.h"
#include "einnervariable.h"
#include "../../bison/tree_nodes.h"

#include <vector>

class ByteCode;

class ERoutine : public EFeature {
    // ================ MY FRIENDS ================
    friend ByteCode;

    // ================= SUBTYPES =================
public:
    struct InstructionInfo {
        short       localVarNumber              = 0;
        short       fieldRef_constLink          = 0;
        short       creatorMethodRef_constLink  = 0;
        short       methodRef_constLink         = 0;

        short       constClass_constLink        = 0;
        std::string ownerClassFullName          = "";
    };

    struct ExpressionInfo {
        bool        isValid                     = true;
        EType       resultType                  = EType::noType();

        short       innerVarNumber              = 0;
        short       liter_constLink             = 0;
        short       fieldRef_constLink          = 0;
        short       methodRef_constLink         = 0;
        short       getterConstClass_constLink  = 0;
        short       getterMethodRef_constLink   = 0;
        short       setterConstClass_constLink  = 0;
        short       setterMethodRef_constLink   = 0;

        short       constClass_constLink        = 0;
        std::string ownerClassFullName          = "";

        bool        isRTLcall                   = false;
    };

    // ================ ATTRIBUTES ================
private:
    instruction_seq_strct* _routineBody;

    EInnerVariable                          _current;
    std::map<std::string, EInnerVariable>   _formalParameters;
    std::map<std::string, EInnerVariable>   _localVariables;

    std::map<const instruction_strct*, InstructionInfo> _instrInfo;
    std::map<const expr_strct*, ExpressionInfo>         _exprInfo;

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
    void resolveBody(const EFeatureMetaInfo& selfMetaInfo);


private:
    void _resolveInstruction(const EFeatureMetaInfo& selfMetaInfo, EUserClass& userClass, instruction_strct* instruction);
    void _resolveCreateInstruction(const EFeatureMetaInfo& selfMetaInfo, EUserClass& userClass, instruction_strct* createInstruction);
    void _resolveAssignInstruction(const EFeatureMetaInfo& selfMetaInfo, EUserClass& userClass, instruction_strct* assignInstruction);
    void _resolveIfInstruction(const EFeatureMetaInfo& selfMetaInfo, EUserClass& userClass, instruction_strct* ifInstruction);
    void _resolveLoopInstruction(const EFeatureMetaInfo& selfMetaInfo, EUserClass& userClass, instruction_strct* loopInstruction);
    void _resolveExprAsInstruction(const EFeatureMetaInfo& selfMetaInfo, EUserClass& userClass, instruction_strct* exprAsInstruction);

    void _resolveExpr(const EFeatureMetaInfo& selfMetaInfo, EUserClass& userClass, expr_strct* expr);
    void _resolveCallSelffeatureExpr(const EFeatureMetaInfo& selfMetaInfo, EUserClass& userClass, expr_strct* expr);
    void _resolveCallPrecursorExpr(const EFeatureMetaInfo& selfMetaInfo, EUserClass& userClass, expr_strct* expr);
    void _resolveCallSubcallExpr(const EFeatureMetaInfo& selfMetaInfo, EUserClass& userClass, expr_strct* expr);
    void _resolveCreateExpr(const EFeatureMetaInfo& selfMetaInfo, EUserClass& userClass, expr_strct* expr);
    bool _resolveCallArguments(const EFeatureMetaInfo&      selfMetaInfo,
                               EUserClass&                  userClass,
                               const EFeature*              featureInfo,
                               const argument_seq_strct*    argumentSeq,
                               bool                         isFieldAccess,
                               EType                        arrayType = EType::noType());

    void _resolveArrElemExpr(const EFeatureMetaInfo& selfMetaInfo, EUserClass& userClass, expr_strct* expr);

    void _resolveBinaryArithmExpr(const EFeatureMetaInfo& selfMetaInfo, EUserClass& userClass, expr_strct* expr);
    void _resolveUnaryArithmExpr(const EFeatureMetaInfo& selfMetaInfo, EUserClass& userClass, expr_strct* expr);

    void _resolveCompareExpr(const EFeatureMetaInfo& selfMetaInfo, EUserClass& userClass, expr_strct* expr);
    void _resolveEqualityCompareExpr(const EFeatureMetaInfo& selfMetaInfo, EUserClass& userClass, expr_strct* expr);

    void _resolveBinaryLogicExpr(const EFeatureMetaInfo& selfMetaInfo, EUserClass& userClass, expr_strct* expr);
    void _resolveUnaryLogicExpr(const EFeatureMetaInfo& selfMetaInfo, EUserClass& userClass, expr_strct* expr);

public:
    bool isConformingTo(const EFeature& other, bool areDeclarationsCompared = true) const override;

    // ---------------- additional ----------------
public:
    std::string toString() const override;
};

#endif // EMETHOD_H
