#pragma once

// === COMMON ===
struct identifiers_comma_seq_strct {
    unsigned int _node_index;

    char* value;
    struct identifiers_comma_seq_strct* next;
};

// === MAIN ===
struct program_strct {
    unsigned int _node_index;

    struct class_decl_seq_strct* class_decl_seq;
};

struct class_decl_seq_strct {
    unsigned int _node_index;

    struct class_decl_strct* value;
    struct class_decl_seq_strct* next;
};

// CLASS
struct class_decl_strct {
    unsigned int _node_index;

    char* id_name;

    struct inheritance_block_strct*     inheritance_block;
    struct creators_block_strct*        creators_block;
    struct features_block_strct*        features_block;
};

// Inheritance block
struct inheritance_block_strct {
    unsigned int _node_index;

    struct parent_seq_strct* parent_seq;
};

struct parent_seq_strct {
    unsigned int _node_index;

    struct parent_strct* value;
    struct parent_seq_strct* next;
};

struct parent_strct {
    unsigned int _node_index;

    char* id_name;
    struct parent_info_strct* parent_info;
};

struct parent_info_strct {
    unsigned int _node_index;

    struct rename_seq_strct*              rename_seq;
    struct identifiers_comma_seq_strct*   undefine_seq;
    struct identifiers_comma_seq_strct*   redefine_seq;
    struct identifiers_comma_seq_strct*   select_seq;
};

struct rename_seq_strct {
    unsigned int _node_index;

    char* old_id_name;
    char* new_id_name;

    struct rename_seq_strct* next;
};

// Creators block
struct creators_block_strct {
    unsigned int _node_index;
    struct nonempty_creators_block_strct* nonempty_creators_block;
};

struct nonempty_creators_block_strct {
    unsigned int _node_index;

    struct identifiers_comma_seq_strct* value;
    struct nonempty_creators_block_strct* next;
};

// Features block
struct features_block_strct {
    unsigned int _node_index;
    struct nonempty_features_block_strct* nonempty_features_block;
};

struct nonempty_features_block_strct {
    unsigned int _node_index;

    struct feature_decl_seq_strct* value;
    struct nonempty_features_block_strct* next;
};

struct feature_decl_seq_strct {
    unsigned int _node_index;
    struct nonempty_feature_decl_seq_strct* nonempty_feature_decl_seq;
};

struct nonempty_feature_decl_seq_strct {
    unsigned int _node_index;

    struct feature_decl_strct* value;
    struct nonempty_feature_decl_seq_strct* next;
};

struct feature_decl_strct {
    unsigned int _node_index;

    struct identifiers_comma_seq_strct* identifiers_comma_seq;
    struct type_strct* type;

    struct ids_with_type_seq_strct* feature_param_seq;
    struct routine_decl_body_strct* routine_decl_body;
};

struct ids_with_type_seq_strct {
    unsigned int _node_index;
    struct nonempty_ids_with_type_seq_strct* nonempty_ids_with_type_seq;
};

struct nonempty_ids_with_type_seq_strct {
    unsigned int _node_index;

    struct ids_with_type_strct* value;
    struct nonempty_ids_with_type_seq_strct* next;
};

struct ids_with_type_strct {
    unsigned int _node_index;

    struct identifiers_comma_seq_strct* identifiers_comma_seq;
    struct type_strct* type;
};

enum type_enum {
    dtype_user_defined,

    dtype_boolean,
    dtype_character,
    dtype_integer_8,
    dtype_integer_16,
    dtype_integer_32,
    dtype_integer_64,
    dtype_natural_8,
    dtype_natural_16,
    dtype_natural_32,
    dtype_natural_64,
    dtype_string
};

struct type_strct {
    unsigned int _node_index;
    enum type_enum type;

    char* id_name;
};

struct routine_decl_body_strct {
    unsigned int _node_index;
};
