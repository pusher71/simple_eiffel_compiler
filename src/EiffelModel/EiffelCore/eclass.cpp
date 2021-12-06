#include "eclass.h"
#include <set>

#include "eprogram.h"
#include "../EiffelAttributeInfo/eattribute.h"
#include "../EiffelRoutineInfo/eroutine.h"

EClass::EClass(class_decl_strct* classNode)
    : _name(classNode->id_name),
      _type(EType(classNode->id_name)),
      _featuresTableState(NOT_SETUP)
{
    this->_constants.appendUtf8(this->_name);
    this->_constants.appendConstClass(1);

    this->_defineParents(classNode->parent_seq);    // Read parents information
    this->_defineCreators(classNode->creators_seq); // Read creators information
    this->_defineFeatures(classNode->features_seq); // Read features information
    this->_defineFeaturesTable();                   // Define features table
}

void EClass::_defineParents(const parent_seq_strct* parentSeq) {
    parent_seq_strct* parentSeqElem = (parent_seq_strct*)parentSeq;
    while(parentSeqElem != NULL) {
        EParentInfo parentInfo;

        // Set rename sequence of each parent
        rename_seq_strct* renameSeqElem = parentSeqElem->value->rename_seq;
        while (renameSeqElem != NULL) {
            parentInfo.renameSeq.push_back({renameSeqElem->old_id_name, renameSeqElem->new_id_name});
            renameSeqElem = renameSeqElem->next;
        }

        // Set redefine sequence of each parent
        identifiers_comma_seq_strct* redefineSeqElem = parentSeqElem->value->redefine_seq;
        while (redefineSeqElem != NULL) {
            parentInfo.redefineSeq.push_back(redefineSeqElem->value);
            redefineSeqElem = redefineSeqElem->next;
        }

        // Set select sequence of each parent
        identifiers_comma_seq_strct* selectSeqElem = parentSeqElem->value->select_seq;
        while (selectSeqElem != NULL) {
            parentInfo.selectSeq.push_back(selectSeqElem->value);
            selectSeqElem = selectSeqElem->next;
        }

        this->_parents[parentSeqElem->value->id_name] = parentInfo;
        parentSeqElem = parentSeqElem->next;
    }
}

void EClass::_defineCreators(const creators_seq_strct* creatorSeq) {
    creators_seq_strct* creatorsSeqElem = (creators_seq_strct*)creatorSeq;
    while (creatorsSeqElem != NULL) {
        identifiers_comma_seq_strct* identifiersCommaSeqElem = creatorsSeqElem->value;

        while (identifiersCommaSeqElem != NULL) {
            this->_creators.push_back(identifiersCommaSeqElem->value);
            identifiersCommaSeqElem = identifiersCommaSeqElem->next;
        }

        creatorsSeqElem = creatorsSeqElem->next;
    }
}

void EClass::_defineFeatures(const features_seq_strct* featuresSeq) {
    features_seq_strct* featuresSeqElem = (features_seq_strct*)featuresSeq;
    while (featuresSeqElem != NULL) {
        feature_decl_seq_strct* featureDeclSeqElem = featuresSeqElem->value;
        while (featureDeclSeqElem != NULL) {
            identifiers_comma_seq_strct* featureNameSeqElem = featureDeclSeqElem->value->identifiers_comma_seq;
            while (featureNameSeqElem != NULL) {
                if (featureDeclSeqElem->value->routine_body != nullptr) {
                    this->_features[featureNameSeqElem->value] = std::make_unique<ERoutine>(ERoutine(featureNameSeqElem->value, this, featureDeclSeqElem->value));
                }
                else {
                    this->_features[featureNameSeqElem->value] = std::make_unique<EAttribute>(EAttribute(featureNameSeqElem->value, this, featureDeclSeqElem->value));
                }

                featureNameSeqElem = featureNameSeqElem->next;
            }

            featureDeclSeqElem = featureDeclSeqElem->next;
        }

        featuresSeqElem = featuresSeqElem->next;
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
            this->_featuresTable.push_back(EFeatureMetaInfo(featureInfo.first, {this->_name, featureInfo.first}, featureInfo.second.get()));
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
        classPathStr += this->_name;

        std::string errorMessage = "class \""+ this->_name + "\" has inherited self by path: <PATH>";
        EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::INHERITANCE__INHERIT_CYCLE, errorMessage));
    }

    this->_featuresTableState = IN_PROCESS;

    for (const auto& parentInfo : this->_parents) {
        EClass* parentClass = EProgram::current->getClassBy(parentInfo.first);

        // Setup parent features table if parent hasn't setup it
        if (parentClass->_featuresTableState == NOT_SETUP) {
            std::vector<std::string> newClassInheritPath(classInheritPath.begin(), classInheritPath.end());
            newClassInheritPath.push_back(this->_name);

            parentClass->setupAcceptableFeaturesTable(newClassInheritPath);
        }

        this->_fillSelfFeaturesTableUsingParent(parentClass, parentInfo.second);
    }

    // Remove duplicates
    std::set<EFeatureMetaInfo> featuresTableAsSet(this->_featuresTable.begin(), this->_featuresTable.end());
    this->_featuresTable.assign(featuresTableAsSet.begin(), featuresTableAsSet.end());

    this->_resolveSelects();
    this->_validateSelfFeaturesTable();

    this->_featuresTableState = DONE;
}

void EClass::_fillSelfFeaturesTableUsingParent(const EClass* parent, const EParentInfo& parentInfo) {
    for (const auto& parentFeatureInfo : parent->_featuresTable) {
        EFeatureMetaInfo result(parentFeatureInfo);
        result.setParentClassName(parent->_name);

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

            for (const auto& featureInfo : featureGroupInfo.second) {
                std::vector<std::string> parentOfFeatureSelects = this->_parents[featureInfo->parentClassName()].selectSeq;

                if (std::count(parentOfFeatureSelects.begin(), parentOfFeatureSelects.end(), featureInfo->finalName())) {
                    selectedFeaturesInfo.push_back(featureInfo);
                    break;
                }
            }

            for (auto& featureInfo : featureGroupInfo.second) {
                if (std::count(selectedFeaturesInfo.begin(), selectedFeaturesInfo.end(), featureInfo) == 0) {
                    featureInfo->setFeatureMark(this->_name, featureInfo->finalName());
                }
            }
        }
    }
}

void EClass::_validateSelfFeaturesTable() const {
}

std::string EClass::name() const { return this->_name; }
EType EClass::getType() const { return this->_type; }

const std::map<std::string, EClass::EParentInfo> EClass::parents() const { return this->_parents; }
const std::map<std::string, std::shared_ptr<EFeature>> EClass::features() const { return this->_features; }

void EClass::compile() {
}
