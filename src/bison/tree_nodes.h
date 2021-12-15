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

    struct parent_seq_strct*    parent_seq;
    struct creators_seq_strct*  creators_seq;
    struct features_seq_strct*  features_seq;
};

// Inheritance block
struct parent_seq_strct {
    unsigned int _node_index;

    struct parent_strct* value;
    struct parent_seq_strct* next;
};

struct parent_strct {
    unsigned int _node_index;

    char* id_name;

    struct rename_seq_strct*              rename_seq;
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
struct creators_seq_strct {
    unsigned int _node_index;

    struct identifiers_comma_seq_strct* value;
    struct creators_seq_strct* next;
};

// Features block
struct features_seq_strct {
    unsigned int _node_index;

    struct feature_decl_seq_strct* value;
    struct features_seq_strct* next;
};

struct feature_decl_seq_strct {
    unsigned int _node_index;

    struct feature_decl_strct* value;
    struct feature_decl_seq_strct* next;
};

struct feature_decl_strct {
    unsigned int _node_index;

    struct identifiers_comma_seq_strct* identifiers_comma_seq;
    struct type_strct* type;

    struct ids_with_type_seq_strct* feature_param_seq;

    struct ids_with_type_seq_strct* local_variables;
    struct instruction_seq_strct*   routine_body;
};

struct ids_with_type_seq_strct {
    unsigned int _node_index;

    struct identifiers_comma_seq_strct* identifiers_comma_seq;
    struct type_strct* type;

    struct ids_with_type_seq_strct* next;
};

enum type_enum {
    dtype_user_defined,
    dtype_array,

    dtype_boolean,
    dtype_character,
    dtype_integer,
    dtype_natural,
    dtype_string
};

struct type_strct {
    unsigned int        _node_index;
    enum type_enum      type;

    char*               id_name;
    struct type_strct*  arrayelem_type;
};

struct instruction_seq_strct {
    unsigned int _node_index;

    struct instruction_strct* value;
    struct instruction_seq_strct* next;
};

enum instruction_enum {
    instruction_create,
    instruction_if,
    instruction_assign,
    instruction_loop,
    instruction_expr
};

struct instruction_strct {
    unsigned int _node_index;
    enum instruction_enum type;

    char* first_id_name;
    char* second_id_name;
    struct argument_seq_strct* argument_seq;

    struct expr_strct* assign_expr;

    struct expr_strct* condition;
    struct instruction_seq_strct* branch_true;
    struct instruction_seq_strct* branch_false;

    struct instruction_seq_strct* init;
    struct instruction_seq_strct* body;

    struct expr_strct* instruction_as_expr;
};

struct argument_seq_strct {
    unsigned int _node_index;

    struct expr_strct* value;
    struct argument_seq_strct* next;
};

enum expr_type {
    expr_liter_bool,
    expr_liter_int,
    expr_liter_char,
    expr_liter_str,

    expr_current,
    expr_call_method_or_var,
    expr_call_method,
    expr_call_precursor,
    expr_subcall,
    expr_create,

    expr_arrelem,
    expr_plus,
    expr_bminus,
    expr_mul,
    expr_idiv,
    expr_uminus,

    expr_less,
    expr_great,
    expr_less_equal,
    expr_great_equal,
    expr_equal,
    expr_notequal,

    expr_and,
    expr_or,
    expr_xor,
    expr_not
};

struct expr_strct {
    unsigned int _node_index;
    enum expr_type type;
    int is_parenthesized;

    char*                       class_id_name;
    char*                       method_id_name;
    struct argument_seq_strct*  argument_seq;

    int                 liter_bool;
    int                 liter_int;
    char                liter_char;
    struct CharArray*   liter_str;

    struct expr_strct*  expr_left;
    struct expr_strct*  expr_right;

    struct type_strct*  create_type;

    // Semantic analysis additional data
    struct type_strct*  result_type;
    int inner_var_number;
};
