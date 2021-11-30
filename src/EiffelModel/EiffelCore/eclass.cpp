#include "eclass.h"
#include <iostream>

EClass* EClass::create(class_decl_strct* classNode) {
    EClass* result = new EClass();
    result->_name = classNode->id_name;
    result->_type = EType::create(result->_name);

    // Read inheritance information ...
    parent_seq_strct* parentSeqElem = classNode->parent_seq;
    while(parentSeqElem != NULL) {
        EParentInfo parentInfo;
        // ... Set name of each parent
        parentInfo.parentName = parentSeqElem->value->id_name;

        // ... Set rename sequence of each parent
        rename_seq_strct* renameSeqElem = parentSeqElem->value->rename_seq;
        while (renameSeqElem != NULL) {
            parentInfo.renameSeq.push_back({renameSeqElem->old_id_name, renameSeqElem->new_id_name});
            renameSeqElem = renameSeqElem->next;
        }

        // ... Set redefine sequence of each parent
        identifiers_comma_seq_strct* redefineSeqElem = parentSeqElem->value->redefine_seq;
        while (redefineSeqElem != NULL) {
            parentInfo.redefineSeq.push_back(redefineSeqElem->value);
            redefineSeqElem = redefineSeqElem->next;
        }

        // ... Set select sequence of each parent
        identifiers_comma_seq_strct* selectSeqElem = parentSeqElem->value->select_seq;
        while (selectSeqElem != NULL) {
            parentInfo.selectSeq.push_back(selectSeqElem->value);
            selectSeqElem = selectSeqElem->next;
        }

        result->_parents.push_back(parentInfo);
        parentSeqElem = parentSeqElem->next;
    }

    // Read creators information
    creators_seq_strct* creatorsSeqElem = classNode->creators_seq;
    while (creatorsSeqElem != NULL) {
        identifiers_comma_seq_strct* identifiersCommaSeqElem = creatorsSeqElem->value;

        while (identifiersCommaSeqElem != NULL) {
            result->_creators.push_back(identifiersCommaSeqElem->value);
            identifiersCommaSeqElem = identifiersCommaSeqElem->next;
        }

        creatorsSeqElem = creatorsSeqElem->next;
    }

    // Read features information
    features_seq_strct* featuresSeqElem = classNode->features_seq;
    while (featuresSeqElem != NULL) {
        feature_decl_seq_strct* featureDeclSeqElem = featuresSeqElem->value;
        while (featureDeclSeqElem != NULL) {
            identifiers_comma_seq_strct* featureNameSeqElem = featureDeclSeqElem->value->identifiers_comma_seq;
            while (featureNameSeqElem != NULL) {
                result->_features[featureNameSeqElem->value] = EFeature::create(result->_name, featureNameSeqElem->value, featureDeclSeqElem->value);
                featureNameSeqElem = featureNameSeqElem->next;
            }

            featureDeclSeqElem = featureDeclSeqElem->next;
        }

        featuresSeqElem = featuresSeqElem->next;
    }

    return result;
}

EType* EClass::getType() {
    return this->_type;
}

void EClass::compile() {
}
