#include "efield.h"

EField* EField::create(feature_decl_strct* featureDecl) {
    EField* result = new EField();
    return result;
}

bool EField::initSelf() {
    return true;
}
