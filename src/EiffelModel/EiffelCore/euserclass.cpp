#include "euserclass.h"
#include "../EiffelFeatureInfo/eattribute.h"
#include "../EiffelFeatureInfo/eroutine.h"

EUserClass::EUserClass(const class_decl_strct* classNode)
    : _name(classNode->id_name),
      _classNode((class_decl_strct*)classNode)
{
    this->_initSelf();

    this->_constants.appendUtf8(this->_name);
    this->_constants.appendConstClass(1);
}

void EUserClass::_defineParents() {
    const parent_seq_strct* parentSeq = this->_classNode->parent_seq;

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

    // Set ANY class as parent if user class hasn't got any parents
    if (this->_parents.empty()) {
        this->_parents["any"] = {};
    }
}

void EUserClass::_defineCreators() {
    const creators_seq_strct* creatorSeq = this->_classNode->creators_seq;

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

void EUserClass::_defineFeatures() {
    const features_seq_strct* featuresSeq = this->_classNode->features_seq;

    features_seq_strct* featuresSeqElem = (features_seq_strct*)featuresSeq;
    while (featuresSeqElem != NULL) {
        feature_decl_seq_strct* featureDeclSeqElem = featuresSeqElem->value;
        while (featureDeclSeqElem != NULL) {
            identifiers_comma_seq_strct* featureNameSeqElem = featureDeclSeqElem->value->identifiers_comma_seq;
            while (featureNameSeqElem != NULL) {
                if (featureDeclSeqElem->value->routine_body != nullptr) {
                    this->_features[featureNameSeqElem->value] = std::make_shared<ERoutine>(ERoutine(featureNameSeqElem->value, this, featureDeclSeqElem->value));
                }
                else {
                    this->_features[featureNameSeqElem->value] = std::make_shared<EAttribute>(EAttribute(featureNameSeqElem->value, this, featureDeclSeqElem->value));
                }

                featureNameSeqElem = featureNameSeqElem->next;
            }

            featureDeclSeqElem = featureDeclSeqElem->next;
        }

        featuresSeqElem = featuresSeqElem->next;
    }
}

std::string EUserClass::name() const { return this->_name; }
std::string EUserClass::javaPackageName() const { return "eiffel"; }

void EUserClass::compile() {
}
