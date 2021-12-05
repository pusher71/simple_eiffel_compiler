#include "efeature.h"
#include "eprogram.h"
#include "eclass.h"
#include "etype.h"

EFeature::EFeature(const std::string& featureName, const EClass* ownerClass, feature_decl_strct* featureDecl)
    : _name(featureName),
      _ownerClassName(ownerClass->name()),
      _node(featureDecl),
      _type( (featureDecl->type != nullptr ? EType(featureDecl->type) : EType::voidType()) )
{}

EFeature::~EFeature() {}

void EFeature::validate() const {
    // Validate on name clashing
    // ... Check that feature name doesn't clashes with class names
    if (EProgram::current->getClassBy(this->_name) != nullptr) {
        std::string errorMessage = "feature \""+ this->_ownerClassName + "::" + this->_name + "\" -> class \"" + this->_name + "\"";
        EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::FEATURES__NAME_CLASHES_WITH_CLASS_NAME, errorMessage));
    }
    // ... Check that feature name doesn't clashes with names of features of the owner class
    else if (EProgram::current->getClassBy(this->_ownerClassName)->features().count(this->_name) > 1) {
        std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\"";
        EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::FEATURES__NAME_CLASHES_WITH_NAME_OF_SAME_CLASS_FEATURE, errorMessage));
    }

    // Validate type of feature
    if (this->_type != EType::voidType()) {
        std::string invalidUserTypeName;

        if (!this->_type.isUserDefinedSubtypeValid(invalidUserTypeName)) {
            std::string errorMessage = "feature \"" + this->_ownerClassName + "::" + this->_name + "\" :: no user defined subtype \"" + invalidUserTypeName + "\"";
            EProgram::semanticErrors.push_back(SemanticError(SemanticErrorCode::FEATURES__FEATURE_INVALID_TYPE, errorMessage));
        }
    }
}

std::string EFeature::name() const { return this->_name; }
EType EFeature::type() const { return this->_type; }
std::string EFeature::ownerClassName() const { return this->_ownerClassName; }
