#ifndef ERROR_CODES_H
#define ERROR_CODES_H

enum SemanticErrorCode {
    // First semantic stage error codes
    CLASSES__NAME_CLASHES_WITH_USER_CLASS_NAME,
    CLASSES__NAME_CLASHES_WITH_RTL_CLASS_NAME,

    // Second semantic stage error codes
    FEATURES__NAME_CLASHES_WITH_CLASS_NAME,
    FEATURES__NAME_CLASHES_WITH_NAME_OF_SAME_CLASS_FEATURE,

    FEATURES__FORMAL_PARAM_NAME_CLASHES_WITH_CLASS_NAME,
    FEATURES__FORMAL_PARAM_NAME_CLASHES_WITH_NAME_OF_SELF_FEATURE,
    FEATURES__FORMAL_PARAM_NAME_CLASHES_WITH_NAME_OF_SAME_CLASS_FEATURE,
    FEATURES__FORMAL_PARAM_NAME_CLASHES_WITH_NAME_OF_OTHER_FORMAL_PARAM,

    FEATURES__LOCAL_VAR_NAME_CLASHES_WITH_CLASS_NAME,
    FEATURES__LOCAL_VAR_NAME_CLASHES_WITH_NAME_OF_SELF_FEATURE,
    FEATURES__LOCAL_VAR_NAME_CLASHES_WITH_NAME_OF_SAME_CLASS_FEATURE,
    FEATURES__LOCAL_VAR_NAME_CLASHES_WITH_NAME_OF_FORMAL_PARAM,
    FEATURES__LOCAL_VAR_NAME_CLASHES_WITH_NAME_OF_OTHER_LOCAL_VAR,

    FEATURES__FEATURE_INVALID_TYPE,
    FEATURES__FORMAL_PARAM_INVALID_TYPE,
    FEATURES__LOCAL_VAR_INVALID_TYPE,

    /*
    // Third semantic stage error codes ...
    // ... Global error codes
    INHERITANCE__INHERIT_CYCLE,

    FEATURES__NAME_CLASHES_WITH_NAME_OF_INHERITED_FEATURE,
    FEATURES__FORMAL_PARAM_NAME_CLASHES_WITH_NAME_OF_INHERITED_FEATURE,
    FEATURES__LOCAL_VAR_NAME_CLASHES_WITH_NAME_OF_INHERITED_FEATURE,

    // ... Rename error codes
    INHERITANCE__RENAME_OF_UKNOWN_FEATURE,
    INHERITANCE__TWO_OR_MORE_RENAMES_OF_SAME_FEATURE,

    // ... Redefine error codes
    INHERITANCE__REDEFINE_UNKNOWN_FEATURE,
    INHERITANCE__REDEFINE_WITHOUT_REDEFINING_IN_CLASS,

    // ... Select error codes

    // Fourth semantic stage error codes
    */
};

#endif // ERROR_CODES_H