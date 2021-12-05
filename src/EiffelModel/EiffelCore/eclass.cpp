#include "eclass.h"
#include <iostream>

#include "../EiffelAttributeInfo/eattribute.h"
#include "../EiffelRoutineInfo/eroutine.h"

EClass::EClass(class_decl_strct* classNode)
    : _name(classNode->id_name),
      _type(EType(classNode->id_name))
{
    this->_constants.appendUtf8(this->_name);
    this->_constants.appendConstClass(1);

    this->_defineParents(classNode->parent_seq);    // Read parents information
    this->_defineCreators(classNode->creators_seq); // Read creators information
    this->_defineFeatures(classNode->features_seq); // Read features information
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

std::string EClass::name() const { return this->_name; }
EType EClass::getType() const { return this->_type; }

const std::map<std::string, EClass::EParentInfo> EClass::parents() const { return this->_parents; }
const std::map<std::string, std::shared_ptr<EFeature>> EClass::features() const { return this->_features; }

void EClass::compile() {
}
