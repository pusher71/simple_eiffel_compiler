#ifndef EUSERCLASS_H
#define EUSERCLASS_H

#include <string>

#include "eclass.h"
#include "../../bison/tree_nodes.h"

class EUserClass : public EClass {
    // ================ ATTRIBUTES ================
private:
    class_decl_strct* _classNode;

    std::string     _name;
    EConstantTable  _constants;

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
public:
    EUserClass(const class_decl_strct* classNode);

protected:
    void _defineParents() override;
    void _defineCreators() override;
    void _defineFeatures() override;

    // ---------------- attributes ----------------
public:
    std::string name() const override;
    std::string javaPackageName() const override;

    // ----------------- contract -----------------
public:
    void compile();
};

#endif // EUSERCLASS_H
