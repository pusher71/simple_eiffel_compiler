#ifndef ECLASSINFO_H
#define ECLASSINFO_H

#include <vector>
#include <map>
#include <string>
#include <memory>

#include "econstanttable.h"
#include "efeature.h"
#include "../EiffelFeatureInfo/eroutine.h"
#include "efeaturemetainfo.h"
#include "../../bison/tree_nodes.h"

class EClass {
    // ================ MY FRIENDS ================
    friend EUserClass;
    friend ERoutine;

    // ================== STATIC ==================
public:
    static std::string javaObjectFullName();
    static std::string javaStringFullName();

    static std::string userClassPackageName();
    static std::string rtlClassPackageName();

    // ================= SUBTYPES =================
protected:
    struct EParentInfo {
        std::vector<std::pair<std::string, std::string>>    renameSeq;
        std::vector<std::string>                            redefineSeq;
        std::vector<std::string>                            selectSeq;
    };

private:
    enum EFeatureTableState {
        NOT_SETUP,
        IN_PROCESS,
        DONE
    };

    // ================ ATTRIBUTES ================
protected:
    std::vector<std::pair<std::string, EParentInfo>>    _parents;
    std::vector<std::pair<std::string, EFeature*>>      _creators;
    std::map<std::string, std::shared_ptr<EFeature>>    _features;

    std::vector<EFeatureMetaInfo>       _featuresTable;
    EFeatureTableState                  _featuresTableState;

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
    // -- Stage 0 functionality -------
protected:
    void _initSelf();
    virtual void _defineParents() = 0;
    virtual void _defineCreators() = 0;
    virtual void _defineFeatures() = 0;

private:
    void _checkInheritClausesDuplicates() const;
    void _checkCreatorClausesDuplicates() const;
    void _fillFeaturesTableWithSelfFeatures();

    // -- Stage 1 functionality -------
public:
    void validateSelfFeatures() const;
    void checkThatAllParentsAreExist() const;

    // -- Stage 2 functionality -------
public:
    void setupFeaturesTable(const std::vector<std::string>& classInheritPath = {});
    void setupCreators();

private:
    void _fillFeaturesTableUsingParent(const EClass* parent, const EParentInfo& parentInfo, int parentIndex);
    void _checkOnlyExistFeaturesAreRenamed(const EClass* parent, const EParentInfo& parentInfo) const;
    void _checkOnlyExistFeaturesAreTrulyRedefined(const EClass* parent, const EParentInfo& parentInfo) const;
    void _checkOnlyExistFeaturesAreSelected(const EClass* parent, const EParentInfo& parentInfo) const;

    void _resolveSelects();
    void _checkOnFeaturesNameClashing() const;
    void _checkOnFeaturesRepeatInheritConflict() const;

    // ---------------- attributes ----------------
public:
    virtual std::string name() const = 0;
    virtual std::string javaPackageName() const = 0;
    std::string fullName() const;

    const std::vector<std::pair<std::string, EParentInfo>> parents() const;
    const std::map<std::string, std::shared_ptr<EFeature>> features() const;

    const std::vector<const EFeatureMetaInfo*> attributesMetaInfo() const;
    const std::vector<const EFeatureMetaInfo*> routinesMetaInfo() const;

protected:
    void _addFeature(std::shared_ptr<EFeature> feature);
    const EFeature* _getSelfFeature(const std::string& featureName) const;

    // ----------------- contract -----------------
public:
    bool isDescendantTo(const EClass* other) const;
};

#endif // ECLASSINFO_H
