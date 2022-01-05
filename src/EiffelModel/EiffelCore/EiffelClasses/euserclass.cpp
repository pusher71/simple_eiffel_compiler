#include "euserclass.h"
#include "RTLclasses/eclassany.h"
#include "RTLclasses/eclassconsoleio.h"
#include "../../EiffelFeatureInfo/eattribute.h"
#include "../../EiffelFeatureInfo/eroutine.h"
#include "../../EiffelCompilation/bytecode.h"
#include "../../EiffelCore/eprogram.h"

#include <filesystem>
#include <fstream>

EUserClass::EUserClass(const class_decl_strct* classNode)
    : _name(classNode->id_name),
      _classNode((class_decl_strct*)classNode),
      _isMainClass(false)
{
    this->_initSelf();
    this->_fillConstantTableWithSelf();
}

void EUserClass::_fillConstantTableWithSelf() {
    this->_constants.append(JvmConstant::UTF8("Code"));                       // "Code" attribute
    this->_constants.append(JvmConstant::UTF8(this->fullName()));             // Self full name
    this->_constants.append(JvmConstant::ConstClass(2));                      // Class constant of self
    this->_constants.append(JvmConstant::UTF8(EClass::javaObjectFullName())); // Java object full name
    this->_constants.append(JvmConstant::ConstClass(4));                      // Class constant of parent

    this->_constants.appendMethodRef(EClass::javaObjectFullName(), EProgram::javaDefaultConstructorName(), EProgram::javaDefaultConstructorDescriptor());

    this->_constants.appendFieldRef(this->fullName(), "IO", "L" + EClassCONSOLEIO::classRTLfullName() + ";");
    this->_constants.appendMethodRef("rtl/CONSOLEIO", "<init>", "()V");
}

void EUserClass::fillConstantTableWithSelfFeatures() {
    for (auto& featureInfo : this->_features) {
        featureInfo.second.get()->setLinkUtf8_name( this->_constants.append(JvmConstant::UTF8(featureInfo.second.get()->name())) );
        featureInfo.second.get()->setLinkUtf8_descriptor( this->_constants.append(JvmConstant::UTF8(featureInfo.second.get()->descriptor())) );
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
std::string EUserClass::javaPackageName() const { return EClass::userClassPackageName(); }

EConstantTable& EUserClass::constants() { return this->_constants; }

bool EUserClass::isMainClass() const { return this->_isMainClass; }
void EUserClass::becomeMainClass() {
    if (EProgram::mainClass == nullptr) {
        this->_isMainClass = true;
        EProgram::mainClass = this;

        this->_constants.append(JvmConstant::UTF8(EProgram::javaMainFunctionName()));
        this->_constants.append(JvmConstant::UTF8(EProgram::javaMainFunctionDescriptor()));
        this->_constants.appendMethodRef(this->fullName(), EProgram::javaDefaultConstructorName(), EProgram::javaDefaultConstructorDescriptor());
        this->_constants.appendMethodRef(this->fullName(), EProgram::eiffelMainFunctionName(), "()V");

        // Check that class has creator with name "make" (analysis of "main" function in Java)
        if (!std::count_if(this->_creators.begin(), this->_creators.end(), [&](const auto& creatorInfo) { return (creatorInfo.first == EProgram::eiffelMainFunctionName() &&
                                                                                                                  ((ERoutine*)creatorInfo.second)->formalParamsCount() == 0); }))
        {
            std::string errorMessage = "class \"" + this->fullName() + "\" is the main class but has no valid \"" + EProgram::eiffelMainFunctionName() + "\" creator method";

            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::CREATORS__MAIN_CLASS_WITHOUT_MAIN_FUNCTION, errorMessage));
        }
    }
    else {
        throw std::runtime_error("EXCEPTION ERROR :: try to set Main class twice");
    }
}

void EUserClass::addFeaturesTableInfoToConstantTable() {
    for (auto& featureMetaInfo : this->_featuresTable) {
        this->_addFeatureInfoFromMetaToConstantTable(featureMetaInfo);
        this->_addPolyMethodInfoFromMetaToConstantTable(featureMetaInfo);
    }
}

void EUserClass::_addFeatureInfoFromMetaToConstantTable(EFeatureMetaInfo& featureMetaInfo) {
    featureMetaInfo.setFeatureName_utf8Link( this->_constants.append(JvmConstant::UTF8(featureMetaInfo.finalName())) );
    featureMetaInfo.setFeatureDescriptor_utf8Link( this->_constants.append(JvmConstant::UTF8(featureMetaInfo.implementation()->descriptor())) );
}

void EUserClass::_addPolyMethodInfoFromMetaToConstantTable(EFeatureMetaInfo& featureMetaInfo) {
    std::string featureMarkStr = featureMetaInfo.featureMark().first + ":" + featureMetaInfo.featureMark().second;
    featureMetaInfo.setPolyMethodName_utf8Link( this->_constants.append(JvmConstant::UTF8(featureMarkStr)) );

    std::string descriptorStr = "(L" + EClass::javaObjectFullName() + ";";
    if (featureMetaInfo.implementation()->featureType() == EFeature::efeature_routine) {
        for (const auto& formalParamInfo : ((ERoutine*)featureMetaInfo.implementation())->formalParameters()) {
            descriptorStr += "L" + EClass::javaObjectFullName() + ";";
        }
    }
    descriptorStr += ")";

    EClass* ownerClassInfo = EProgram::current->getClassBy(featureMetaInfo.implementation()->ownerClassName());
    if (dynamic_cast<EClassRTL*>(ownerClassInfo) == nullptr) {
        if (featureMetaInfo.implementation()->returnType() != EType::noType())  { descriptorStr += "L" + EClass::javaObjectFullName() + ";"; }
        else                                                                    { descriptorStr += "V"; }
    }
    else {
        descriptorStr += featureMetaInfo.implementation()->returnType().descriptor();
    }

    featureMetaInfo.setPolyMethodDescriptor_utf8Link( this->_constants.append(JvmConstant::UTF8(descriptorStr)) );

    for (EClass* classInfo : EProgram::current->classes()) {
        if (this == classInfo || classInfo->isDescendantTo(this) || this->isDescendantTo(classInfo)) {
            EFeatureMetaInfo* featureMetaWithSameMark = nullptr;
            for (auto& otherFeatureMetaInfo : classInfo->_featuresTable) {
                if (featureMetaInfo.featureMark() == otherFeatureMetaInfo.featureMark()) {
                    featureMetaWithSameMark = &otherFeatureMetaInfo;
                }
            }

            if (featureMetaWithSameMark != nullptr) {
                int16_t fieldOrMethodRef = 0;

                if (featureMetaWithSameMark->featureType() == EFeature::efeature_attribute)     { fieldOrMethodRef = this->_constants.appendFieldRef(classInfo->fullName(), featureMetaWithSameMark->finalName(), featureMetaWithSameMark->implementation()->descriptor()); }
                else                                                                            { fieldOrMethodRef = this->_constants.appendMethodRef(classInfo->fullName(), featureMetaWithSameMark->finalName(), featureMetaWithSameMark->implementation()->descriptor()); }

                featureMetaInfo.addPolyMethodImplementation(this->_constants.appendConstClass(classInfo->fullName()), EPolymorphicImplementationInfo(featureMetaWithSameMark->featureType(), fieldOrMethodRef));
            }
            else {
                short exceptionClass_constLink          = this->_constants.appendConstClass("java/lang/RuntimeException");
                short exceptionMethodRef_constLink      = this->_constants.appendMethodRef("java/lang/RuntimeException", "<init>", "(Ljava/lang/String;)V");
                short exceptionMessageString_constLink  = this->_constants.appendString("No attribute or routine \"" + featureMetaInfo.finalName() + "\" in class \"" + classInfo->fullName() + "\"");

                featureMetaInfo.addPolyMethodImplementation(this->_constants.appendConstClass(classInfo->fullName()), EPolymorphicImplementationInfo(exceptionClass_constLink, exceptionMethodRef_constLink, exceptionMessageString_constLink));
            }
        }
    }
}

void EUserClass::resolveRoutines() {
    for (auto& featureMetaInfo : this->_featuresTable) {
        if (featureMetaInfo.featureType() == EFeature::efeature_routine) {
            // Make copy of routine implementation if routine doesn't belong to self
            if (featureMetaInfo.implementation()->ownerClassName() != this->name()) {
                ERoutine* routineCopy = new ERoutine(*((ERoutine*)featureMetaInfo.implementation()));
                // routineCopy->changeOwnerClass(this);

                featureMetaInfo.setImplementation(routineCopy);
                featureMetaInfo.setCurrentOwnerClassName(this->name());
            }

            ((ERoutine*)featureMetaInfo.implementation())->resolveBody(featureMetaInfo);
        }
    }
}

void EUserClass::checkUsageOfAttributesAndLocals() {
    // Get list of attributes that must be initialized
    for (const auto& attributeMetaInfo : this->attributesMetaInfo()) {
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

    // Write byte code to the file
    byteCode.writeToFile(outputClassFile);

    outputClassFile.close();
}
