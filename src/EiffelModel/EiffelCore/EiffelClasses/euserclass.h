#ifndef EUSERCLASS_H
#define EUSERCLASS_H

#include <string>

#include "../eclass.h"
#include "../../../bison/tree_nodes.h"

class ByteCode;

class EUserClass : public EClass {
    // ================ MY FRIENDS ================
    friend ByteCode;
    friend ERoutine;

    // ================ ATTRIBUTES ================
private:
    class_decl_strct* _classNode;

    std::string     _name;
    EConstantTable  _constants;

    bool _isMainClass;

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
public:
    EUserClass(const class_decl_strct* classNode);

private:
    void _fillConstantTableWithSelf();

public:
    void fillConstantTableWithSelfFeatures();

protected:
    void _defineParents() override;
    void _defineCreators() override;
    void _defineFeatures() override;

    // ---------------- attributes ----------------
public:
    std::string name() const override;
    std::string javaPackageName() const override;

    EConstantTable& constants();

    bool isMainClass() const;
    void becomeMainClass();

    // ----------------- contract -----------------
public:
    void addFeaturesTableInfoToConstantTable();
    void _addFeatureInfoFromMetaToConstantTable(EFeatureMetaInfo& featureMetaInfo);
    void _addPolyMethodInfoFromMetaToConstantTable(EFeatureMetaInfo& featureMetaInfo);

    void resolveRoutines();

    void compile(const std::string& outputDirectoryPath);
};

#endif // EUSERCLASS_H
