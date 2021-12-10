#include "eclass.h"

#include <set>
#include "eprogram.h"

EClass::EClass()
    :  _featuresTableState(NOT_SETUP)
{}

void EClass::validateSelfFeatures() const {
    for (const auto& featureInfo : this->_features) {
        featureInfo.second.get()->validateDataTypes();
        featureInfo.second.get()->checkOnNameClashingWithClass();
    }
}

void EClass::_initSelf() {
    this->_defineParents();
    this->_checkRenameRedefineSelectDuplicates();

    this->_defineCreators();
    this->_defineFeatures();
    this->_defineFeaturesTable();
}

void EClass::_checkRenameRedefineSelectDuplicates() const {
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

void EClass::_defineFeaturesTable() {
    if (this->_parents.empty()) { this->_featuresTableState = DONE; }

    for (const auto& featureInfo : this->_features) {
        bool isRedefinedFeature = false;

        // Check if current feature isn't redefined feature of the class parent
        for (const auto& parentInfo : this->_parents) {
            std::vector<std::string> redefines = parentInfo.second.redefineSeq;

            // Set feature mark as unknown if current feature is redefined feature of the class parent
            if (std::find(redefines.begin(), redefines.end(), featureInfo.first) != redefines.end()) {
                isRedefinedFeature = true;
                break;
            }
        }

        if (!isRedefinedFeature) {
            this->_featuresTable.push_back(EFeatureMetaInfo(featureInfo.first, {this->name(), featureInfo.first}, featureInfo.second.get()));
        }
    }
}

void EClass::setupAcceptableFeaturesTable(const std::vector<std::string>& classInheritPath) {
    if (this->_featuresTableState == DONE) {
        return;
    }
    else if (this->_featuresTableState == IN_PROCESS) {
        std::string classPathStr = "";
        for (const std::string& classPathName : classInheritPath) {
            classPathStr += classPathName + "->";
        }
        classPathStr += this->name();

        std::string errorMessage = "class \""+ this->name() + "\" has inherited self by path: " + classPathStr;
        EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::INHERITANCE__INHERIT_CYCLE, errorMessage));

        return;
    }

    this->_featuresTableState = IN_PROCESS;

    bool isValid = true;

    for (const auto& parentInfo : this->_parents) {
        EClass* parentClass = EProgram::current->getClassBy(parentInfo.first);

        // Setup parent features table if parent hasn't setup it
        if (parentClass->_featuresTableState != DONE) {
            std::vector<std::string> newClassInheritPath(classInheritPath.begin(), classInheritPath.end());
            newClassInheritPath.push_back(this->name());

            parentClass->setupAcceptableFeaturesTable(newClassInheritPath);
        }

        isValid &= this->_validateRenamesForParent(parentClass, parentInfo.second);
        if (isValid) {
            this->_fillSelfFeaturesTableUsingParent(parentClass, parentInfo.second);

            isValid &= this->_validateRedefinesForParent(parentClass, parentInfo.second);
        }
    }

    isValid &= this->_checkOnlyExistFeaturesAreSelected();

    // Check that only exist features are selected
    if (isValid) {
        // Remove duplicates
        std::set<EFeatureMetaInfo> featuresTableAsSet(this->_featuresTable.begin(), this->_featuresTable.end());
        this->_featuresTable.assign(featuresTableAsSet.begin(), featuresTableAsSet.end());

        this->_resolveSelects();
        this->_validateSelfFeaturesTable();
    }

    this->_featuresTableState = DONE;
}

bool EClass::_validateRenamesForParent(const EClass* parent, const EParentInfo& parentInfo) const {
    bool result = true;

    for (const auto& renameInfo : parentInfo.renameSeq) {
        bool renamedFeatureFound = false;
        for (const auto& parentFeatureInfo : parent->_featuresTable) {
            if (parentFeatureInfo.finalName() == renameInfo.first) {
                renamedFeatureFound = true;
                break;
            }
        }

        if (!renamedFeatureFound) {
            std::string errorMessage = "class \"" + this->name() + "\" ";
            errorMessage += ":: rename of unknown feature \"" + renameInfo.first + "\" of parent class \"" + parent->name() + "\"";

            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::INHERITANCE__RENAME_UKNOWN_FEATURE, errorMessage));

            result = false;
            break;
        }
    }

    return result;
}

bool EClass::_validateRedefinesForParent(const EClass* parent, const EParentInfo& parentInfo) const {
    bool areOnlyExistFeaturesRedefined = true;
    bool areAllMarkedFeaturesRedefined = true;

    for (const auto& redefineInfo : parentInfo.redefineSeq) {
        // Check that only exist features are redefined
        bool redefinedFeatureFound = false;
        for (const auto& selfFeatureInfo : this->_featuresTable) {
            if (selfFeatureInfo.finalName() == redefineInfo && selfFeatureInfo.parentClassName() == parent->name()) {
                redefinedFeatureFound = true;
                break;
            }
        }

        if (!redefinedFeatureFound) {
            std::string errorMessage = "class \"" + this->name() + "\" ";
            errorMessage += ":: redefine of unknown feature \"" + redefineInfo + "\" of parent class \"" + parent->name() + "\"";

            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::INHERITANCE__REDEFINE_UNKNOWN_FEATURE, errorMessage));

            areOnlyExistFeaturesRedefined = false;
            break;
        }

        // Check that marked features are redefined in current class
        bool isRedefinedInCurrentClass = false;
        for (const auto& featureInfo : this->_features) {
            if (featureInfo.first == redefineInfo) {
                isRedefinedInCurrentClass = true;
                break;
            }
        }

        if (!isRedefinedInCurrentClass) {
            std::string errorMessage = "class \"" + this->name() + "\" ";
            errorMessage += ":: feature \"" + redefineInfo + "\" of parent class \"" + parent->name() + "\" wasn\'t redefined";

            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::INHERITANCE__REDEFINE_WITHOUT_REDEFINING_IN_CLASS, errorMessage));

            areAllMarkedFeaturesRedefined = false;
            break;
        }
    }

    return areOnlyExistFeaturesRedefined && areAllMarkedFeaturesRedefined;
}

void EClass::_fillSelfFeaturesTableUsingParent(const EClass* parent, const EParentInfo& parentInfo) {
    for (const auto& parentFeatureInfo : parent->_featuresTable) {
        EFeatureMetaInfo result(parentFeatureInfo);
        result.setParentClassName(parent->name());

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

bool EClass::_checkOnlyExistFeaturesAreSelected() {
    for (const auto& parentInfo : this->_parents) {
        for (const auto& selectInfo : parentInfo.second.selectSeq) {
            int count = std::count_if(this->_featuresTable.begin(), this->_featuresTable.end(), [&](const auto& featureMetaInfo){ return (selectInfo == featureMetaInfo.finalName() && parentInfo.first == featureMetaInfo.parentClassName()); });
            if (count == 0) {
                std::string errorMessage = "class \"" + this->name() + "\" ";
                errorMessage += ":: select of unknown feature \"" + selectInfo + "\" of parent class \"" + parentInfo.first + "\" is the only version to select from";

                EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::INHERITANCE__SELECT_UNKNOWN_FEATURE, errorMessage));

                return false;
            }
        }
    }

    return true;
}

void EClass::_resolveSelects() {
    // Divide acceptable features into groups by feature mark
    std::map<std::pair<std::string, std::string>, std::vector<EFeatureMetaInfo*>> featuresInfoDividedByMark;

    for (auto& featureInfo : this->_featuresTable) {
        featuresInfoDividedByMark[featureInfo.featureMark()].push_back(&featureInfo);
    }

    // Set feature marks of features
    for (const auto& featureGroupInfo : featuresInfoDividedByMark) {
        if (featureGroupInfo.second.size() > 1) {
            std::vector<EFeatureMetaInfo*> selectedFeaturesInfo;

            for (const auto& featureMetaInfo : featureGroupInfo.second) {
                std::vector<std::string> parentOfFeatureSelects = this->_parents[featureMetaInfo->parentClassName()].selectSeq;

                if (std::count(parentOfFeatureSelects.begin(), parentOfFeatureSelects.end(), featureMetaInfo->finalName())) {
                    selectedFeaturesInfo.push_back(featureMetaInfo);
                    break;
                }
            }

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

void EClass::_validateSelfFeaturesTable() const {
    bool isValid = true;

    // Check that class doesn't contains two or more different features with same name
    std::map<std::pair<std::string, std::string>, std::vector<EFeatureMetaInfo*>> featuresMetaInfoByMarks;

    for (const auto& featureMetaInfo : this->_featuresTable) {
        featuresMetaInfoByMarks[featureMetaInfo.featureMark()].push_back((EFeatureMetaInfo*)&featureMetaInfo);
    }

    for (const auto& featuresMetaInfo : featuresMetaInfoByMarks) {
        if (featuresMetaInfo.second.size() > 1) {
            std::string errorMessage = "class \"" + this->name() + "\" ";
            errorMessage += ":: class has two or more versions of a feature\n";

            for (const auto& featureMetaInfo : featuresMetaInfo.second) {
                if (featureMetaInfo->parentClassName() != "") {
                    errorMessage += " - feature \"" + featureMetaInfo->finalName() + "\" from parent \"" + featureMetaInfo->parentClassName() + "\"\n";
                }
                else {
                    errorMessage += " - self-defined feature \"" + featureMetaInfo->finalName() + "\"\n";
                }
            }

            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::INHERITANCE__REPEATEDLY_INHERITED_FEATURE_VERSIONS_CONFLICT, errorMessage));
            isValid = false;
        }
    }

    // Check that class doesn't contains two or more different features coming from the same class
    std::map<std::string, std::vector<EFeatureMetaInfo*>> featuresMetaInfoByName;

    for (const auto& featureMetaInfo : this->_featuresTable) {
        std::vector<EFeatureMetaInfo*> featuresMetaInfo = featuresMetaInfoByName[featureMetaInfo.finalName()];

        if (!std::count_if(featuresMetaInfo.begin(),
                           featuresMetaInfo.end(),
                           [&](const auto& f) { return (featureMetaInfo.featureMark() == f->featureMark()); } )) {
            featuresMetaInfoByName[featureMetaInfo.finalName()].push_back((EFeatureMetaInfo*)&featureMetaInfo);
        }
    }

    for (const auto& featuresMetaInfo : featuresMetaInfoByName) {
        if (featuresMetaInfo.second.size() > 1) {
            std::string errorMessage = "class \"" + this->name() + "\" ";
            errorMessage += ":: class has two or more features with same name\n";

            for (const auto& featureMetaInfo : featuresMetaInfo.second) {
                if (featureMetaInfo->parentClassName() != "") {
                    errorMessage += " - feature \"" + featureMetaInfo->finalName() + "\" from parent \"" + featureMetaInfo->parentClassName() + "\"\n";
                }
                else {
                    errorMessage += " - self-defined feature \"" + featureMetaInfo->finalName() + "\"\n";
                }
            }

            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::FEATURES__NAME_CLASHES_WITH_NAME_OF_INHERITED_FEATURE, errorMessage));
            isValid = false;
        }
    }

    if (isValid) {
        for (const auto& selfFeatureInfo : this->_features) {
            selfFeatureInfo.second->checkOnNameClashingAfterInherit();
        }
    }
}

const std::map<std::string, EClass::EParentInfo> EClass::parents() const { return this->_parents; }
const std::map<std::string, std::shared_ptr<EFeature>> EClass::features() const { return this->_features; }

#include <iostream>

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
