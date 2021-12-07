#include "eclass.h"

#include <set>
#include "eprogram.h"

EClass::EClass()
    :  _featuresTableState(NOT_SETUP)
{}

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

void EClass::_initSelf() {
    this->_defineParents();
    this->_defineCreators();
    this->_defineFeatures();
    this->_defineFeaturesTable();
}

#include <iostream>

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

    for (const auto& parentInfo : this->_parents) {
        EClass* parentClass = EProgram::current->getClassBy(parentInfo.first);

        // Setup parent features table if parent hasn't setup it
        if (parentClass->_featuresTableState != DONE) {
            std::vector<std::string> newClassInheritPath(classInheritPath.begin(), classInheritPath.end());
            newClassInheritPath.push_back(this->name());

            parentClass->setupAcceptableFeaturesTable(newClassInheritPath);
        }

        this->_fillSelfFeaturesTableUsingParent(parentClass, parentInfo.second);
    }

    // Check that only exist features are selected
    if (this->_checkOnlyExistFeaturesAreSelected()) {
        // Remove duplicates
        std::set<EFeatureMetaInfo> featuresTableAsSet(this->_featuresTable.begin(), this->_featuresTable.end());
        this->_featuresTable.assign(featuresTableAsSet.begin(), featuresTableAsSet.end());

        this->_resolveSelects();
        this->_validateSelfFeaturesTable();
    }

    this->_featuresTableState = DONE;
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
                        result.setImplementation(selfFeatureInfo.second.get());
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
                errorMessage += ":: select of unknown feature \"" + selectInfo + "\"";

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

            for (auto& featureInfo : featureGroupInfo.second) {
                if (std::count(selectedFeaturesInfo.begin(), selectedFeaturesInfo.end(), featureInfo) == 0) {
                    featureInfo->setFeatureMark(this->name(), featureInfo->finalName());
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
}

const std::map<std::string, EClass::EParentInfo> EClass::parents() const { return this->_parents; }
const std::map<std::string, std::shared_ptr<EFeature>> EClass::features() const { return this->_features; }
