#pragma once
#include "tree_nodes.h"

// === MAIN ===
struct program_strct* create_program(unsigned int node_index, struct class_decl_seq_strct* class_decl_seq);

struct class_decl_seq_strct* create_class_decl_seq(unsigned int node_index, struct class_decl_strct* class_decl);
struct class_decl_seq_strct* append_class_decl_seq(unsigned int node_index, struct class_decl_seq_strct* class_decl_seq, struct class_decl_strct* class_decl);

// === COMMON ===
struct identifiers_comma_seq_strct* create_identifiers_comma_seq(unsigned int node_index, char* id_name);
struct identifiers_comma_seq_strct* append_identifiers_comma_seq(unsigned int node_index, struct identifiers_comma_seq_strct* identifiers_comma_seq, char* id_name);

// === CLASS ===
struct class_decl_strct* create_class_decl(unsigned int node_index,
                                           char* id_name,
                                           struct inheritance_block_strct* inheritance_block,
                                           struct creators_block_strct* creators_block,
                                           struct features_block_strct* features_block
                                           );

// Inheritance block
struct inheritance_block_strct* create_inheritance_block(unsigned int node_index, struct parent_seq_strct* parent_seq);

struct parent_seq_strct* create_parent_seq(unsigned int node_index, struct parent_strct* parent);
struct parent_seq_strct* append_parent_seq(unsigned int node_index, struct parent_seq_strct* parent_seq, struct parent_strct* parent);

struct parent_strct* create_parent(unsigned int node_index, char* id_name, struct parent_info_strct* parent_info);
struct parent_info_strct* create_parent_info(unsigned int node_index,
                                             struct rename_seq_strct* rename_seq,
                                             struct identifiers_comma_seq_strct* undefine_seq,
                                             struct identifiers_comma_seq_strct* redefine_seq,
                                             struct identifiers_comma_seq_strct* select_seq);

struct rename_seq_strct* create_rename_seq(unsigned int node_index, char* old_id_name, char* new_id_name);
struct rename_seq_strct* append_rename_seq(unsigned int node_index, struct rename_seq_strct* rename_seq, char* old_id_name, char* new_id_name);

// Creators block
struct creators_block_strct* create_creators_block(unsigned int node_index, struct nonempty_creators_block_strct* nonempty_creators_block);

struct nonempty_creators_block_strct* create_nonempty_creators_block(unsigned int node_index,
                                                                     struct identifiers_comma_seq_strct* identifiers_comma_seq);
struct nonempty_creators_block_strct* append_nonempty_creators_block(unsigned int node_index,
                                                                     struct nonempty_creators_block_strct* nonempty_creators_block,
                                                                     struct identifiers_comma_seq_strct* identifiers_comma_seq);

// Features block
struct features_block_strct* create_features_block(unsigned int node_index, struct nonempty_features_block_strct* nonempty_features_block);

struct nonempty_features_block_strct* create_nonempty_features_block(unsigned int node_index, struct feature_decl_seq_strct* feature_decl_seq);
struct nonempty_features_block_strct* append_nonempty_features_block(unsigned int node_index,
                                                                     struct nonempty_features_block_strct* nonempty_features_block,
                                                                     struct feature_decl_seq_strct* feature_decl_seq);

struct feature_decl_seq_strct* create_feature_decl_seq(unsigned int node_index, struct nonempty_feature_decl_seq_strct* nonempty_feature_decl_seq);

struct nonempty_feature_decl_seq_strct* create_nonempty_feature_decl_seq(unsigned int node_index, struct feature_decl_strct* feature_decl);
struct nonempty_feature_decl_seq_strct* append_nonempty_feature_decl_seq(unsigned int node_index,
                                                                         struct nonempty_feature_decl_seq_strct* nonempty_feature_decl_seq,
                                                                         struct feature_decl_strct* feature_decl);

struct feature_decl_strct* create_feature_decl(unsigned int node_index,
                                               struct identifiers_comma_seq_strct* identifiers_comma_seq,
                                               struct type_strct* type,
                                               struct ids_with_type_seq_strct* feature_param_seq,
                                               struct routine_decl_body_strct* routine_decl_body);

struct ids_with_type_seq_strct* create_ids_with_type_seq(unsigned int node_index, struct nonempty_ids_with_type_seq_strct* nonempty_ids_with_type_seq);

struct nonempty_ids_with_type_seq_strct* create_nonempty_ids_with_type_seq(unsigned int node_index, struct ids_with_type_strct* ids_with_type);
struct nonempty_ids_with_type_seq_strct* append_nonempty_ids_with_type_seq(unsigned int node_index,
                                                                           struct nonempty_ids_with_type_seq_strct* nonempty_ids_with_type_seq,
                                                                           struct ids_with_type_strct* ids_with_type);

struct ids_with_type_strct* create_ids_with_type(unsigned int node_index, struct identifiers_comma_seq_strct* identifiers_comma_seq, struct type_strct* type);

struct type_strct* create_type(unsigned int node_index, enum type_enum type, char* id_name);

struct routine_decl_body_strct* create_routine_decl_body(unsigned int node_index,
                                                         struct ids_with_type_seq_strct* local_ids_with_type_seq,
                                                         struct instruction_seq_strct* instruction_seq);

struct instruction_seq_strct* create_instruction_seq(unsigned int node_index, struct instruction_strct* instruction);
struct instruction_seq_strct* append_instruction_seq(unsigned int node_index,
                                                     struct instruction_seq_strct* instruction_seq,
                                                     struct instruction_strct* instruction);

// ... Instruction
struct instruction_strct* create_create_instruction(unsigned int node_index, char* var_name, char* method_name, struct argument_seq_strct* argument_seq);

struct instruction_strct* create_assignment_instruction(unsigned int node_index,
                                                struct expr_strct* expr_left,
                                                struct expr_strct* expr_right);

struct instruction_strct* create_if_instruction(unsigned int node_index,
                                                struct expr_strct* condition,
                                                struct instruction_seq_strct* branch_true,
                                                struct instruction_seq_strct* branch_false);

struct instruction_strct* create_loop_instruction(unsigned int node_index,
                                                struct instruction_strct* init,
                                                struct expr_strct* condition,
                                                struct instruction_seq_strct* body);

struct instruction_strct* create_call_instruction(unsigned int node_index, struct call_strct* call);

struct call_strct* create_call_my_method(unsigned int node_index,
                                         char* id_name,
                                         struct argument_seq_strct* argument_seq,
                                         struct call_sub_seq_strct* call_sub_seq);

struct call_strct* create_call_method_of_current(unsigned int node_index,
                                                 struct call_sub_seq_strct* call_sub_seq);

struct call_strct* create_call_method_of_result(unsigned int node_index,
                                                struct call_sub_seq_strct* call_sub_seq);

struct call_strct* create_call_method_of_paren_expr(unsigned int node_index,
                                                    struct expr_strct* parenthesized_expr,
                                                    struct call_sub_seq_strct* call_sub_seq);

struct call_strct* create_call_precursor(unsigned int node_index,
                                         char* id_name,
                                         struct argument_seq_strct* argument_seq,
                                         struct call_sub_seq_strct* call_sub_seq);

struct call_sub_seq_strct* create_call_sub_seq(unsigned int node_index,
                                               char* id_name,
                                               struct argument_seq_strct* argument_seq);

struct call_sub_seq_strct* append_call_sub_seq(unsigned int node_index,
                                               struct call_sub_seq_strct* call_sub_seq,
                                               char* id_name,
                                               struct argument_seq_strct* argument_seq);

struct argument_seq_strct* create_argument_seq(unsigned int node_index, struct nonempty_argument_seq_strct* nonempty_argument_seq);

struct nonempty_argument_seq_strct* create_nonempty_argument_seq(unsigned int node_index,
                                                                 struct expr_strct* expr);

struct nonempty_argument_seq_strct* append_nonempty_argument_seq(unsigned int node_index,
                                                                 struct nonempty_argument_seq_strct* nonempty_argument_seq,
                                                                 struct expr_strct* expr);

// ... Expression
struct expr_strct* create_expr_liter_bool(unsigned int node_index, int liter_bool);
struct expr_strct* create_expr_liter_int (unsigned int node_index, int liter_int);
struct expr_strct* create_expr_liter_char(unsigned int node_index, char liter_char);
struct expr_strct* create_expr_liter_str (unsigned int node_index, struct CharArray* liter_str);

struct expr_strct* create_expr_call(unsigned int node_index, struct call_strct* call);

struct expr_strct* create_expr_operation(unsigned int node_index, struct expr_strct* expr_left, struct expr_strct* expr_right, enum expr_type operation);
