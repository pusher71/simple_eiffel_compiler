#include "euserclass.h"
#include "eclassany.h"
#include "../../EiffelFeatureInfo/eattribute.h"
#include "../../EiffelFeatureInfo/eroutine.h"
#include "../../EiffelCompilation/bytecode.h"
#include "../../EiffelCore/eprogram.h"

#include <filesystem>
#include <fstream>

EUserClass::EUserClass(const class_decl_strct* classNode)
    : _name(classNode->id_name),
      _classNode((class_decl_strct*)classNode)
{
    this->_initSelf();
    this->_fillConstantTableWithSelf();
}

void EUserClass::_fillConstantTableWithSelf() {
    this->_constants.appendUtf8("Code");                        // "Code" attribute
    this->_constants.appendUtf8(this->fullName());              // Self full name
    this->_constants.appendConstClass(2);                       // Class constant of self
    this->_constants.appendUtf8(EClass::javaObjectFullName());  // Java object full name
    this->_constants.appendConstClass(4);                       // Class constant of self
}

void EUserClass::fillConstantTableWithSelfFeatures() {
    for (auto& featureInfo : this->_features) {
        featureInfo.second.get()->setLinkUtf8_name( this->_constants.appendUtf8(featureInfo.second.get()->name()) );
        featureInfo.second.get()->setLinkUtf8_descriptor( this->_constants.appendUtf8(featureInfo.second.get()->descriptor()) );
    }
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

        this->_parents.push_back({parentSeqElem->value->id_name, parentInfo});
        parentSeqElem = parentSeqElem->next;
    }

    // Set ANY class as parent if user class hasn't got any parents
    if (this->_parents.empty()) {
        this->_parents.push_back({EClassANY::classRTLname(), {}});
    }
}

void EUserClass::_defineCreators() {
    const creators_seq_strct* creatorSeq = this->_classNode->creators_seq;

    creators_seq_strct* creatorsSeqElem = (creators_seq_strct*)creatorSeq;
    while (creatorsSeqElem != NULL) {
        identifiers_comma_seq_strct* identifiersCommaSeqElem = creatorsSeqElem->value;

        while (identifiersCommaSeqElem != NULL) {
            this->_creators.push_back({identifiersCommaSeqElem->value, nullptr});
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
                    this->_addFeature(std::make_shared<ERoutine>(ERoutine(featureNameSeqElem->value, this, featureDeclSeqElem->value)));
                }
                else {
                    this->_addFeature(std::make_shared<EAttribute>(EAttribute(featureNameSeqElem->value, this, featureDeclSeqElem->value)));
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

EConstantTable& EUserClass::constants() { return this->_constants; }

void EUserClass::addFeaturesTableInfoToConstantTable() {
    for (auto& featureMetaInfo : this->_featuresTable) {
        std::string featureMarkStr = featureMetaInfo.featureMark().first + ":" + featureMetaInfo.featureMark().second;
        featureMetaInfo.setFeatureMark_utf8Link(this->_constants.appendUtf8(featureMarkStr));

        std::string descriptorStr = "(L" + EClass::javaObjectFullName() + ";";
        if (featureMetaInfo.implementation()->featureType() == EFeature::efeature_routine) {
            for (const auto& formalParamInfo : ((ERoutine*)featureMetaInfo.implementation())->formalParameters()) {
                descriptorStr += formalParamInfo.second.type().descriptor();
            }
        }
        descriptorStr += ")" + featureMetaInfo.implementation()->returnType().descriptor();

        featureMetaInfo.setDescriptor_utf8Link(this->_constants.appendUtf8(descriptorStr));

        for (EClass* classInfo : EProgram::current->classes()) {
            if (this == classInfo || classInfo->isDescendantTo(this)) {
                EFeature* featureWithSameMark = nullptr;
                for (const auto& otherFeatureMetaInfo : classInfo->_featuresTable) {
                    if (featureMetaInfo.featureMark() == otherFeatureMetaInfo.featureMark()) {
                        featureWithSameMark = otherFeatureMetaInfo.implementation();
                    }
                }

                if (featureWithSameMark != nullptr) {
                    short otherClassNameLink = this->_constants.appendUtf8(classInfo->fullName());
                    short otherConstClassLink = this->_constants.appendConstClass(otherClassNameLink);

                    EClass* ownerClass = EProgram::current->getClassBy(featureWithSameMark->ownerClassName());
                    short classNameLink = this->_constants.appendUtf8(ownerClass->fullName());
                    short constClassLink = this->_constants.appendConstClass(classNameLink);

                    short featureNameLink = this->_constants.appendUtf8(featureWithSameMark->name());
                    short featureDescriptorLink = this->_constants.appendUtf8(featureWithSameMark->descriptor());
                    short featureNameAndTypeLink = this->_constants.appendNameAndType({featureNameLink, featureDescriptorLink});

                    short fieldOrMethodRef = 0;

                    if (featureWithSameMark->featureType() == EFeature::efeature_attribute) {
                        fieldOrMethodRef = this->_constants.appendFieldRef({constClassLink, featureNameAndTypeLink});
                    }
                    else {
                        fieldOrMethodRef = this->_constants.appendMethodRef({constClassLink, featureNameAndTypeLink});
                    }

                    featureMetaInfo.addPolymorphicImplementation(otherConstClassLink, {featureWithSameMark->featureType(), fieldOrMethodRef});
                }
            }
        }
    }
}

void EUserClass::resolveRoutines() {
    for (const auto& featureInfo : this->_features) {
        if (featureInfo.second.get()->featureType() == EFeature::efeature_routine) {
            ((ERoutine*)featureInfo.second.get())->resolveBody();
        }
    }
}

void EUserClass::compile(const std::string& outputDirectoryPath) {
    // Create user class file at its java package ...
    // Create java package
    std::filesystem::path javaPackagePath = outputDirectoryPath;
    javaPackagePath /= this->javaPackageName();

    if (!std::filesystem::exists(javaPackagePath)) {
        std::filesystem::create_directory(javaPackagePath);
    }

    // Create class file
    std::filesystem::path outputClassFilePath = javaPackagePath;
    outputClassFilePath /= this->name() + ".class";

    std::ofstream outputClassFile(outputClassFilePath);

    // Generate byte code for user class
    ByteCode byteCode(*this);

    // Write byte code to file
    byteCode.writeToFile(outputClassFile);
}
