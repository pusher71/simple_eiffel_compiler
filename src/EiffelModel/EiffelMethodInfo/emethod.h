#ifndef EMETHOD_H
#define EMETHOD_H

#include <string>
#include <vector>

#include "../EiffelCore/efeature.h"
#include "elocalvariable.h"
#include "../../bison/tree_nodes.h"

class EMethod : public EFeature {
private:
    std::string _name;
    std::vector<ELocalVariable*> _locals;
    instruction_seq_strct* _routineBody;

    // ============== OPERATIONS ==============
    // -------- creating --------
public:
    static EMethod* create(const std::string& ownerClassName, feature_decl_strct* featureDecl);

    bool initSelf();

    // ------- attributes -------
public:
    std::string name();
};

#endif // EMETHOD_H
