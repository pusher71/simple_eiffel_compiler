#include "efeature.h"
#include "eprogram.h"
#include "eclass.h"
#include "etype.h"

#include "EiffelClasses/euserclass.h"

EFeature::EFeature(const std::string& featureName, EUserClass* ownerClass, feature_decl_strct* featureDecl)
    : _name(featureName),
      _ownerClassName(ownerClass->name()),
      _node(featureDecl),
      _returnType( (featureDecl->type != nullptr ? EType(featureDecl->type) : EType::noType()) )
{}

EFeature::EFeature(const std::string& featureName, const EClass* ownerClass, const EType& returnType)
    : _name(featureName),
      _ownerClassName(ownerClass->name()),
      _node(nullptr),
      _returnType(returnType)
{}

EFeature::~EFeature() {}

void EFeature::validateDataTypes() {
    if (this->_returnType != EType::noType()) {
        std::string invalidUserTypeName;

        if (!this->_returnType.isUserDefinedSubtypeValid(invalidUserTypeName)) {
            std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" :: no user defined subtype \"" + invalidUserTypeName + "\"";
            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::FEATURES__FEATURE_INVALID_TYPE, errorMessage));
        }
    }
}

void EFeature::checkOnNameClashingWithClasses() const {
    if (EProgram::current->getClassBy(this->name()) != nullptr) {
        std::string errorMessage = "feature \""+ this->_ownerClassName + "::" + this->name() + "\" -> class \"" + this->name() + "\"";
        EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::FEATURES__NAME_CLASHES_WITH_CLASS_NAME, errorMessage));
    }
}

std::string EFeature::name() const { return this->_name; }
EType EFeature::returnType() const { return this->_returnType; }
std::string EFeature::ownerClassName() const { return this->_ownerClassName; }

short EFeature::linkUtf8_name() const { return this->_linkUtf8_name; }
short EFeature::linkUtf8_descriptor() const { return this->_linkUtf8_descriptor; }

void EFeature::setLinkUtf8_name(short linkUtf8_name) { this->_linkUtf8_name = linkUtf8_name; }
void EFeature::setLinkUtf8_descriptor(short linkUtf8_descriptor) { this->_linkUtf8_descriptor = linkUtf8_descriptor; }

void EFeature::changeOwnerClass(const EClass* classInfo) { this->_ownerClassName = classInfo->name(); }

std::string EFeature::toString() const {
    std::string result = this->_returnType.toString() + " " + this->_name;
    return result;
}
