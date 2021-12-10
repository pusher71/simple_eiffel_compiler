#ifndef EMETHOD_H
#define EMETHOD_H

#include <string>
#include <map>

#include "../EiffelCore/efeature.h"
#include "einnervariable.h"
#include "../../bison/tree_nodes.h"

class ERoutine : public EFeature {
    // ================ ATTRIBUTES ================
private:
    instruction_seq_strct*      _routineBody;

    EInnerVariable              _current;
    std::map<std::string, EInnerVariable> _formalParameters;
    std::map<std::string, EInnerVariable> _localVariables;

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
public:
    ERoutine(const std::string& featureName, const EClass* ownerClass, feature_decl_strct* featureDecl);
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
    unsigned short formalParamsCount() const;

    // ----------------- contract -----------------
public:
    void validateDataTypes() const override;
    void checkOnNameClashingAfterInherit() const override;

private:
    void _validateFormalParamDataTypes() const;
    void _validateLocalVarDataTypes() const;

    void _checkOnFormalParamNameClashing() const;
    void _checkOnLocalVarNameClashing() const;

    bool isConformingTo(const EFeature& other) const override;

    // ---------------- additional ----------------
public:
    std::string toString() const override;
};

#endif // EMETHOD_H
