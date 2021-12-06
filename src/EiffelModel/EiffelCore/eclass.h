#ifndef ECLASSINFO_H
#define ECLASSINFO_H

#include <vector>
#include <map>
#include <string>
#include <memory>

#include "econstanttable.h"
#include "efeature.h"
#include "efeaturemetainfo.h"
#include "../../bison/tree_nodes.h"

class EClass {
    // ================= SUBTYPES =================
private:
    struct EParentInfo {
        std::vector<std::pair<std::string, std::string>>    renameSeq;
        std::vector<std::string>                            redefineSeq;
        std::vector<std::string>                            selectSeq;
    };

    enum EFeatureTableState {
        NOT_SETUP,
        IN_PROCESS,
        DONE
    };

    // ================ ATTRIBUTES ================
private:
    std::string                         _name;
    EType                               _type;
    EConstantTable                      _constants;

    std::map<std::string, EParentInfo>                  _parents;
    std::vector<std::string>                            _creators;
    std::map<std::string, std::shared_ptr<EFeature>>    _features;

    std::vector<EFeatureMetaInfo>       _featuresTable;
    EFeatureTableState                  _featuresTableState;

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
public:
    EClass(class_decl_strct* classNode);

private:
    void _defineParents(const parent_seq_strct* parentSeq);
    void _defineCreators(const creators_seq_strct* creatorSeq);
    void _defineFeatures(const features_seq_strct* featuresSeq);
    void _defineFeaturesTable();

public:
    void setupAcceptableFeaturesTable(const std::vector<std::string>& classInheritPath = {});

private:
    void _fillSelfFeaturesTableUsingParent(const EClass* parent, const EParentInfo& parentInfo);
    void _resolveSelects();
    void _validateSelfFeaturesTable() const;

    // ---------------- attributes ----------------
public:
    std::string name() const;
    EType getType() const;

    const std::map<std::string, EParentInfo> parents() const;
    const std::map<std::string, std::shared_ptr<EFeature>> features() const;

    // ----------------- contract -----------------
public:
    void compile();
};

#endif // ECLASSINFO_H
