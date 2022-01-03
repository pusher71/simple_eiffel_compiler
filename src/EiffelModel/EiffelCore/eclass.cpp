#include "eclass.h"

#include <set>
#include "eprogram.h"

std::string EClass::javaObjectFullName() { return "java/lang/Object"; }
std::string EClass::javaStringFullName() { return "java/lang/String"; }

std::string EClass::userClassPackageName() { return "eiffel"; }
std::string EClass::rtlClassPackageName() { return "rtl"; }

void EClass::_initSelf() {
    this->_defineParents();
    this->_checkInheritClausesDuplicates();

    this->_defineCreators();
    this->_checkCreatorClausesDuplicates();

    this->_defineFeatures();
    this->_fillFeaturesTableWithSelfFeatures();
}

void EClass::_checkInheritClausesDuplicates() const {
    // Setup lambda expression for extracting string duplicates from vector
    auto getStrDuplicates = [](std::vector<std::string> vec) {
        std::vector<std::string> duplicates;
        std::sort(vec.begin(), vec.end());
        std::set<std::string> vecUnique(vec.begin(), vec.end());
        std::set_difference(vec.begin(), vec.end(), vecUnique.begin(), vecUnique.end(), std::back_inserter(duplicates));

        return std::set<std::string>(duplicates.begin(), duplicates.end());
    };

    for (const auto& parentInfo : this->_parents) {
        // Check rename duplicates
        std::vector<std::string> renameFirstNames;
        std::for_each(parentInfo.second.renameSeq.begin(), parentInfo.second.renameSeq.end(), [&](const auto& renameInfo){ renameFirstNames.push_back(renameInfo.first); });

        std::set<std::string> renameDuplicates = getStrDuplicates(renameFirstNames);

        for (const std::string& renameFirstName : renameDuplicates) {
            std::string errorMessage = "class \"" + this->name() + "\" ";
            errorMessage += ":: feature \"" + renameFirstName + "\" of parent class \"" + parentInfo.first + "\" was renamed more than once";

            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::INHERITANCE__TWO_OR_MORE_RENAMES_OF_SAME_FEATURE, errorMessage));
        }

        // Check redefine duplicates
        std::set<std::string> redefineDuplicates = getStrDuplicates(parentInfo.second.redefineSeq);

        for (const std::string& redefineName : redefineDuplicates) {
            std::string errorMessage = "class \"" + this->name() + "\" ";
            errorMessage += ":: redefine clause for feature \"" + redefineName + "\" of parent class \"" + parentInfo.first + "\" was repeated";

            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::INHERITANCE__REDEFINE_CLAUSE_FEATURE_DUPLICATED, errorMessage));
        }

        // Check select duplicates
        std::set<std::string> selectDuplicates = getStrDuplicates(parentInfo.second.selectSeq);

        for (const std::string& selectName : selectDuplicates) {
            std::string errorMessage = "class \"" + this->name() + "\" ";
            errorMessage += ":: select clause for feature \"" + selectName + "\" of parent class \"" + parentInfo.first + "\" was repeated";

            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::INHERITANCE__SELECT_CLAUSE_FEATURE_DUPLICATED, errorMessage));
        }
    }
}

void EClass::_checkCreatorClausesDuplicates() const {
    // Setup lambda expression for extracting string duplicates from vector
    auto getStrDuplicates = [](std::vector<std::string> vec) {
        std::vector<std::string> duplicates;
        std::sort(vec.begin(), vec.end());
        std::set<std::string> vecUnique(vec.begin(), vec.end());
        std::set_difference(vec.begin(), vec.end(), vecUnique.begin(), vecUnique.end(), std::back_inserter(duplicates));

        return std::set<std::string>(duplicates.begin(), duplicates.end());
    };

    std::vector<std::string> creatorsNames;
    std::for_each(this->_creators.begin(), this->_creators.end(), [&](const auto& creatorInfo) { creatorsNames.push_back(creatorInfo.first); });

    std::set<std::string> creatorsNamesDuplicates = getStrDuplicates(creatorsNames);

    for (const std::string& creatorName : creatorsNamesDuplicates) {
        std::string errorMessage = "class \"" + this->name() + "\" ";
        errorMessage += ":: creator clause with name \"" + creatorName + "\" was repeated";

        EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::CREATORS__SEVERAL_CREATORS_WITH_SAME_NAME, errorMessage));
    }
}

void EClass::_fillFeaturesTableWithSelfFeatures() {
    this->_featuresTableState = (this->_parents.empty() ? DONE : NOT_SETUP);

    for (const auto& featureInfo : this->_features) {
        std::vector<std::string> allRedefines;
        std::for_each(this->_parents.begin(), this->_parents.end(), [&](const auto& parentInfo) { allRedefines.insert(allRedefines.end(), parentInfo.second.redefineSeq.begin(), parentInfo.second.redefineSeq.end()); });

        // Add feature to feature table if it was defined in the class
        if (std::find(allRedefines.begin(), allRedefines.end(), featureInfo.first) == allRedefines.end()) {
            EFeatureMetaInfo featureMetaInfo(featureInfo.first, {this->name(), featureInfo.first}, featureInfo.second.get(), featureInfo.second.get()->featureType());
            if (featureInfo.second.get()->returnType() == EType::noType()) {
                featureMetaInfo.setReturnType(EFeatureMetaInfo::ereturntype_void);
            }
            else if (featureInfo.second.get()->returnType() == EType::intType()) {
                featureMetaInfo.setReturnType(EFeatureMetaInfo::ereturntype_integer);
            }
            else {
                featureMetaInfo.setReturnType(EFeatureMetaInfo::ereturntype_object);
            }

            this->_featuresTable.push_back(featureMetaInfo);
        }
    }
}

void EClass::validateSelfFeatures() const {
    for (auto& featureInfo : this->_features) {
        featureInfo.second.get()->validateDataTypes();
        featureInfo.second.get()->checkOnNameClashingWithClasses();
    }
}

void EClass::checkThatAllParentsAreExist() const {
    for (const auto& parentInfo : this->_parents) {
        EClass* parentClass = EProgram::current->getClassBy(parentInfo.first);

        // Check if class with parent name exists
        if (parentClass == nullptr) {
            std::string errorMessage = "class \""+ this->name() + "\" has unknown parent with name \"" + parentInfo.first + "\"";
            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::INHERITANCE__UNKNOWN_PARENT, errorMessage));
        }
    }
}

void EClass::setupFeaturesTable(const std::vector<std::string>& classInheritPath) {
    // Check features table state
    if (this->_featuresTableState == DONE) {
        return;
    }
    else if (this->_featuresTableState == IN_PROCESS) {
        auto classInheritPathBegin = classInheritPath.begin();
        while (*classInheritPathBegin != this->name() && classInheritPathBegin != classInheritPath.end()) { classInheritPathBegin++; }

        std::string classPathStr = "";
        std::for_each(classInheritPathBegin, classInheritPath.end(), [&](const std::string& classNameInPath) { classPathStr += classNameInPath + "->"; });
        classPathStr += this->name();

        std::string errorMessage = "class \""+ this->name() + "\" has inherited self by path: " + classPathStr;
        EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::INHERITANCE__INHERIT_CYCLE, errorMessage));

        return;
    }

    // Start filling features table with features
    this->_featuresTableState = IN_PROCESS;

    for (int i=0; i<this->_parents.size(); i++) {
        EClass* parentClass = EProgram::current->getClassBy(this->_parents.at(i).first);

        // Setup parent features table if parent hasn't setup it
        if (parentClass->_featuresTableState != DONE) {
            std::vector<std::string> newClassInheritPath(classInheritPath.begin(), classInheritPath.end());
            newClassInheritPath.push_back(this->name());

            parentClass->setupFeaturesTable(newClassInheritPath);
        }

        // Fill features table using parent features table
        this->_fillFeaturesTableUsingParent(parentClass, this->_parents.at(i).second, i);

        this->_checkOnlyExistFeaturesAreRenamed(parentClass, this->_parents.at(i).second);
        this->_checkOnlyExistFeaturesAreTrulyRedefined(parentClass, this->_parents.at(i).second);
        this->_checkOnlyExistFeaturesAreSelected(parentClass, this->_parents.at(i).second);
    }

    // Remove duplicates and resolve select clauses
    if (EProgram::semanticErrors.empty()) {
        // Remove duplicates
        std::set<EFeatureMetaInfo> featuresTableAsSet(this->_featuresTable.begin(), this->_featuresTable.end());
        this->_featuresTable.assign(featuresTableAsSet.begin(), featuresTableAsSet.end());

        // Resolve select clauses
        this->_resolveSelects();
        this->_checkOnFeaturesNameClashing();
        this->_checkOnFeaturesRepeatInheritConflict();
    }

    // Stop filling features table with features
    this->_featuresTableState = DONE;
}

void EClass::_fillFeaturesTableUsingParent(const EClass* parent, const EParentInfo& parentInfo, int parentIndex) {
    for (const auto& parentFeatureMetaInfo : parent->_featuresTable) {
        EFeatureMetaInfo result(parentFeatureMetaInfo);
        result.setParentClassName(parent->name());
        result.setParentClassIndex(parentIndex);

        // Set feature final name
        for (const auto& renameInfo : parentInfo.renameSeq) {
            if (result.finalName() == renameInfo.first) {
                result.setFinalName(renameInfo.second);
                break;
            }
        }

        // Set feature implementation
        for (const auto& redefineInfo : parentInfo.redefineSeq) {
            if (result.finalName() == redefineInfo) {
                // Find feature implementation in self features
                for (auto& selfFeatureInfo : this->_features) {
                    if (selfFeatureInfo.first == result.finalName()) {
                        if (selfFeatureInfo.second.get()->isConformingTo(*result.implementation())) {
                            result.setImplementation(selfFeatureInfo.second.get());
                        }
                        else {
                            std::string errorMessage = "class \"" + this->name() + "\" ";
                            errorMessage += ":: non-conforming redefine feature \"" + redefineInfo + "\" of parent class \"" + parent->name() + "\"\n";
                            errorMessage += "- parent feature:    " + result.implementation()->toString() + "\n";
                            errorMessage += "- redefined feature: " + selfFeatureInfo.second.get()->toString() + "\n";

                            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::INHERITANCE__NONCONFORMING_REDEFINE, errorMessage));
                        }
                    }
                }

                break;
            }
        }

        this->_featuresTable.push_back(result);
    }
}

void EClass::_checkOnlyExistFeaturesAreRenamed(const EClass* parent, const EParentInfo& parentInfo) const {
    for (const auto& renameInfo : parentInfo.renameSeq) {
        bool isRenamedExistFeature = std::count_if(parent->_featuresTable.begin(), parent->_featuresTable.end(), [&](const auto& featureMetaInfo){ return (featureMetaInfo.finalName() == renameInfo.first); });

        if (!isRenamedExistFeature) {
            std::string errorMessage = "class \"" + this->name() + "\" ";
            errorMessage += ":: rename of unknown feature \"" + renameInfo.first + "\" of parent class \"" + parent->name() + "\"";

            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::INHERITANCE__RENAME_UKNOWN_FEATURE, errorMessage));
            break;
        }
    }
}

void EClass::_checkOnlyExistFeaturesAreTrulyRedefined(const EClass* parent, const EParentInfo& parentInfo) const {
    for (const auto& redefineInfo : parentInfo.redefineSeq) {
        // Check that only exist features are redefined
        bool isRedefinedExistFeature = std::count_if(this->_featuresTable.begin(), this->_featuresTable.end(), [&](const auto& featureMetaInfo){ return (featureMetaInfo.finalName() == redefineInfo && featureMetaInfo.parentClassName() == parent->name()); });

        if (!isRedefinedExistFeature) {
            std::string errorMessage = "class \"" + this->name() + "\" ";
            errorMessage += ":: redefine of unknown feature \"" + redefineInfo + "\" of parent class \"" + parent->name() + "\"";

            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::INHERITANCE__REDEFINE_UNKNOWN_FEATURE, errorMessage));
            break;
        }

        // Check that features that marked as redefined are truly redefined in current class
        bool isRedefinedInCurrentClass = std::count_if(this->_features.begin(), this->_features.end(), [&](const auto& featureInfo){ return (featureInfo.first == redefineInfo); });

        if (!isRedefinedInCurrentClass) {
            std::string errorMessage = "class \"" + this->name() + "\" ";
            errorMessage += ":: feature \"" + redefineInfo + "\" of parent class \"" + parent->name() + "\" wasn\'t redefined";

            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::INHERITANCE__REDEFINE_WITHOUT_REDEFINING_IN_CLASS, errorMessage));
            break;
        }
    }
}

void EClass::_checkOnlyExistFeaturesAreSelected(const EClass* parent, const EParentInfo& parentInfo) const {
    for (const auto& selectInfo : parentInfo.selectSeq) {
        bool isSelectedExistFeature = std::count_if(this->_featuresTable.begin(), this->_featuresTable.end(), [&](const auto& featureMetaInfo){ return (featureMetaInfo.finalName() == selectInfo && featureMetaInfo.parentClassName() == parent->name()); });

        if (!isSelectedExistFeature) {
            std::string errorMessage = "class \"" + this->name() + "\" ";
            errorMessage += ":: select of unknown feature \"" + selectInfo + "\" of parent class \"" + parent->name() + "\" is the only version to select from";

            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::INHERITANCE__SELECT_UNKNOWN_FEATURE, errorMessage));
            return;
        }
    }
}

void EClass::_resolveSelects() {
    // Divide features from features table into groups by feature mark
    std::map<std::pair<std::string, std::string>, std::vector<EFeatureMetaInfo*>> featuresInfoDividedByMark;

    for (auto& featureInfo : this->_featuresTable) {
        featuresInfoDividedByMark[featureInfo.featureMark()].push_back(&featureInfo);
    }

    // Set feature marks of features
    for (const auto& featureGroupInfo : featuresInfoDividedByMark) {
        if (featureGroupInfo.second.size() > 1) {
            std::vector<EFeatureMetaInfo*> selectedFeaturesInfo;

            // Collect features that are selected
            for (const auto& featureMetaInfo : featureGroupInfo.second) {
                std::vector<std::string> parentOfFeatureSelects = this->_parents.at(featureMetaInfo->parentClassIndex()).second.selectSeq;

                if (std::count(parentOfFeatureSelects.begin(), parentOfFeatureSelects.end(), featureMetaInfo->finalName())) {
                    selectedFeaturesInfo.push_back(featureMetaInfo);
                }
            }

            // Change marks of features that aren't selected
            if (!selectedFeaturesInfo.empty()) {
                for (auto& featureInfo : featureGroupInfo.second) {
                    if (std::count(selectedFeaturesInfo.begin(), selectedFeaturesInfo.end(), featureInfo) == 0) {
                        featureInfo->setFeatureMark(this->name(), featureInfo->finalName());
                    }
                }
            }
        }
        else {
            EFeatureMetaInfo* featureMetaInfo = featureGroupInfo.second.at(0);

            for (const auto& parentInfo : this->_parents) {
                if (std::count(parentInfo.second.selectSeq.begin(), parentInfo.second.selectSeq.end(), featureMetaInfo->finalName())) {
                    std::string errorMessage = "class \"" + this->name() + "\" ";
                    errorMessage += ":: feature \"" + featureMetaInfo->finalName() + "\" of parent class \"" + parentInfo.first + "\" is the only version to select from";

                    EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::INHERITANCE__IMPROPER_SELECT, errorMessage));
                    break;
                }
            }
        }
    }
}

void EClass::_checkOnFeaturesNameClashing() const {
    std::map<std::string, std::vector<EFeatureMetaInfo*>> featuresMetaInfoByName;
    std::for_each(this->_featuresTable.begin(), this->_featuresTable.end(), [&](const auto& featureMetaInfo) { featuresMetaInfoByName[featureMetaInfo.finalName()].push_back((EFeatureMetaInfo*)&featureMetaInfo); });

    for (const auto& featuresMetaInfo : featuresMetaInfoByName) {
        if (featuresMetaInfo.second.size() > 1) {
            std::string errorMessage = "class \"" + this->name() + "\" ";
            errorMessage += ":: class has two or more features with same name\n";

            for (const auto& featureMetaInfo : featuresMetaInfo.second) {
                if (featureMetaInfo->parentClassName() != "")   { errorMessage += " - feature \"" + featureMetaInfo->finalName() + "\" from parent \"" + featureMetaInfo->parentClassName() + "\"\n"; }
                else                                            { errorMessage += " - self-defined feature \"" + featureMetaInfo->finalName() + "\"\n"; }
            }

            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::FEATURES__NAME_CLASHES_WITH_NAME_OF_INHERITED_FEATURE, errorMessage));
        }
    }

    for (const auto& selfFeatureInfo : this->_features) {
        if (selfFeatureInfo.second->featureType() == EFeature::efeature_routine) {
            ((ERoutine*)selfFeatureInfo.second.get())->checkOnInnerVarsNameClashing();
        }
    }
}

void EClass::_checkOnFeaturesRepeatInheritConflict() const {
    // Check that class doesn't contains two or more different features with same name
    std::map<std::pair<std::string, std::string>, std::vector<EFeatureMetaInfo*>> featuresMetaInfoByMarks;

    for (const auto& featureMetaInfo : this->_featuresTable) {
        std::vector<EFeatureMetaInfo*> featuresMetaInfoWithMark = featuresMetaInfoByMarks[featureMetaInfo.featureMark()];

        if (!std::count_if(featuresMetaInfoWithMark.begin(),
                          featuresMetaInfoWithMark.end(),
                          [&](const auto& otherFeatureMetaInfo) { return (featureMetaInfo.finalName() == otherFeatureMetaInfo->finalName()); }))
        {
            featuresMetaInfoByMarks[featureMetaInfo.featureMark()].push_back((EFeatureMetaInfo*)&featureMetaInfo);
        }
    }

    for (const auto& featuresMetaInfo : featuresMetaInfoByMarks) {
        if (featuresMetaInfo.second.size() > 1) {
            std::string errorMessage = "class \"" + this->name() + "\" ";
            errorMessage += ":: class has two or more versions of a feature\n";

            for (const auto& featureMetaInfo : featuresMetaInfo.second) {
                if (featureMetaInfo->parentClassName() != "")   { errorMessage += " - feature \"" + featureMetaInfo->finalName() + "\" from parent \"" + featureMetaInfo->parentClassName() + "\"\n"; }
                else                                            { errorMessage += " - self-defined feature \"" + featureMetaInfo->finalName() + "\"\n"; }
            }

            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::INHERITANCE__REPEATEDLY_INHERITED_FEATURE_VERSIONS_CONFLICT, errorMessage));
        }
    }
}

void EClass::setupCreators() {
    for (auto& creatorInfo : this->_creators) {
        const auto& featureMetaInfo = std::find_if(this->_featuresTable.begin(), this->_featuresTable.end(), [&](const auto& featureMetaInfo){ return (featureMetaInfo.finalName() == creatorInfo.first); });

        if (featureMetaInfo == this->_featuresTable.end()) {
            std::string errorMessage = "class \"" + this->name() + "\" ";
            errorMessage += ":: unknown creator with name \"" + creatorInfo.first + "\"";

            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::CREATORS__UNKNOWN_CREATOR, errorMessage));
        }
        else if ((*featureMetaInfo).implementation()->featureType() == EFeature::efeature_attribute) {
            std::string errorMessage = "class \"" + this->name() + "\" ";
            errorMessage += ":: attribute with name \"" + creatorInfo.first + "\"";

            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::CREATORS__ATTRIBUTE_IS_CREATOR, errorMessage));
        }
        else if ((*featureMetaInfo).implementation()->returnType() != EType::noType()) {
            std::string errorMessage = "class \"" + this->name() + "\" ";
            errorMessage += ":: type of creator\'s return value - \"" + (*featureMetaInfo).implementation()->returnType().toString() + "\"";

            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::CREATORS__CREATOR_HAS_RETURN_VALUE, errorMessage));
        }
        else {
            creatorInfo.second = (*featureMetaInfo).implementation();
        }
    }
}

std::string EClass::fullName() const { return this->javaPackageName() + "/" + this->name(); }

const std::vector<std::pair<std::string, EClass::EParentInfo>> EClass::parents() const { return this->_parents; }
const std::map<std::string, std::shared_ptr<EFeature>> EClass::features() const { return this->_features; }

const std::vector<const EFeatureMetaInfo*> EClass::attributesMetaInfo() const {
    std::vector<const EFeatureMetaInfo*> result;

    for (const auto& featureMetaInfo : this->_featuresTable) {
        if (featureMetaInfo.featureType() == EFeature::efeature_attribute) {
            result.push_back(&featureMetaInfo);
        }
    }

    return result;
}

const std::vector<const EFeatureMetaInfo*> EClass::routinesMetaInfo() const {
    std::vector<const EFeatureMetaInfo*> result;

    for (const auto& featureMetaInfo : this->_featuresTable) {
        if (featureMetaInfo.featureType() == EFeature::efeature_routine) {
            result.push_back(&featureMetaInfo);
        }
    }

    return result;
}

const EFeatureMetaInfo* EClass::getFeatureMetaInfoBy(const std::string& finalName) const {
    const EFeatureMetaInfo* result = nullptr;
    for (auto& featureMetaInfo : this->_featuresTable) {
        if (featureMetaInfo.finalName() == finalName) {
            result = &featureMetaInfo;
            break;
        }
    }

    return result;
}

void EClass::_addFeature(std::shared_ptr<EFeature> feature) {
    if (!this->_features.count(feature->name())) {
        this->_features[feature->name()] = feature;
    }
    else {
        if (this->features().count(feature->name())) {
            std::string errorMessage = "feature \"" + feature->ownerClassName() + "::" + feature->name() + "\"";
            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::FEATURES__NAME_CLASHES_WITH_NAME_OF_SAME_CLASS_FEATURE, errorMessage));
        }
    }
}

const EFeature* EClass::_getSelfFeature(const std::string& featureName) const {
    return (this->_features.count(featureName) ? this->_features.at(featureName).get() : nullptr);
}

bool EClass::isDescendantTo(const EClass* other) const {
    bool result = false;

    std::vector<EClass*> currClassesWave;
    std::for_each(this->_parents.begin(), this->_parents.end(), [&](const auto& parentInfo) { currClassesWave.push_back(EProgram::current->getClassBy(parentInfo.first)); });

    while (!currClassesWave.empty() && !result) {
        // Find parent with given name in current classes wave
        for (const EClass* parentClass : currClassesWave) {
            if (other->name() == parentClass->name()) {
                result = true;
                break;
            }
        }

        // Push parents wave
        std::vector<EClass*> newClassesWave;

        for (const EClass* parentClass : currClassesWave) {
            std::for_each(parentClass->_parents.begin(), parentClass->_parents.end(), [&](const auto& parentInfo) { newClassesWave.push_back(EProgram::current->getClassBy(parentInfo.first)); });
        }

        currClassesWave.assign(newClassesWave.begin(), newClassesWave.end());
    }

    return result;
}
