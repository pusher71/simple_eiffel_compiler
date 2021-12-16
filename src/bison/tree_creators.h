#pragma once
#include "tree_nodes.h"

// === COMMON ===
struct identifiers_comma_seq_strct* create_identifiers_comma_seq(unsigned int node_index, char* id_name);
struct identifiers_comma_seq_strct* append_identifiers_comma_seq(unsigned int                           node_index,
                                                                 struct identifiers_comma_seq_strct*    identifiers_comma_seq,
                                                                 char*                                  id_name);

// === MAIN ===
struct program_strct* create_program(unsigned int node_index, struct class_decl_seq_strct* class_decl_seq);

struct class_decl_seq_strct* create_class_decl_seq(unsigned int node_index, struct class_decl_strct* class_decl);
struct class_decl_seq_strct* append_class_decl_seq(unsigned int                 node_index,
                                                   struct class_decl_seq_strct* class_decl_seq,
                                                   struct class_decl_strct*     class_decl);

// === CLASS ===
struct class_decl_strct* create_class_decl(unsigned int                 node_index,
                                           char*                        id_name,
                                           struct parent_seq_strct*     parent_seq,
                                           struct creators_seq_strct*   creators_seq,
                                           struct features_seq_strct*   features_seq
                                           );

// Inheritance block
struct parent_seq_strct* create_parent_seq(unsigned int node_index, struct parent_strct* parent);
struct parent_seq_strct* append_parent_seq(unsigned int node_index, struct parent_seq_strct* parent_seq, struct parent_strct* parent);

struct parent_strct* create_parent(unsigned int                         node_index,
                                   char*                                id_name,
                                   struct rename_seq_strct*             rename_seq,
                                   struct identifiers_comma_seq_strct*  redefine_seq,
                                   struct identifiers_comma_seq_strct*  select_seq);

struct rename_seq_strct* create_rename_seq(unsigned int node_index, char* old_id_name, char* new_id_name);
struct rename_seq_strct* append_rename_seq(unsigned int             node_index,
                                           struct rename_seq_strct* rename_seq,
                                           char*                    old_id_name,
                                           char*                    new_id_name);

// Creators block
struct creators_seq_strct* create_creators_seq(unsigned int node_index,
                                               struct identifiers_comma_seq_strct* identifiers_comma_seq);

struct creators_seq_strct* append_creators_seq(unsigned int node_index,
                                               struct creators_seq_strct* creators_seq,
                                               struct identifiers_comma_seq_strct* identifiers_comma_seq);

// Features block
struct features_seq_strct* create_features_seq(unsigned int node_index, struct feature_decl_seq_strct* feature_decl_seq);
struct features_seq_strct* append_features_seq(unsigned int node_index,
                                               struct features_seq_strct* features_seq,
                                               struct feature_decl_seq_strct* feature_decl_seq);

struct feature_decl_seq_strct* create_feature_decl_seq(unsigned int node_index, struct feature_decl_strct* feature_decl);
struct feature_decl_seq_strct* append_feature_decl_seq(unsigned int                     node_index,
                                                       struct feature_decl_seq_strct*   feature_decl_seq,
                                                       struct feature_decl_strct*       feature_decl);

struct feature_decl_strct* create_feature_decl(unsigned int                         node_index,
                                               struct identifiers_comma_seq_strct*  identifiers_comma_seq,
                                               struct type_strct*                   type,
                                               struct ids_with_type_seq_strct*      feature_param_seq,
                                               struct ids_with_type_seq_strct*      local_variables,
                                               struct instruction_seq_strct*        routine_body);

struct ids_with_type_seq_strct* create_ids_with_type_seq(unsigned int                           node_index,
                                                         struct identifiers_comma_seq_strct*    identifiers_comma_seq,
                                                         struct type_strct*                     type);

struct ids_with_type_seq_strct* append_ids_with_type_seq(unsigned int                           node_index,
                                                         struct ids_with_type_seq_strct*        ids_with_type_seq,
                                                         struct identifiers_comma_seq_strct*    identifiers_comma_seq,
                                                         struct type_strct*                     type);

struct type_strct* create_type(unsigned int         node_index,
                               enum type_enum       type,
                               char*                id_name,
                               struct type_strct*   arrayelem_type);

struct instruction_seq_strct* create_instruction_seq(unsigned int node_index, struct instruction_strct* instruction);
struct instruction_seq_strct* append_instruction_seq(unsigned int                   node_index,
                                                     struct instruction_seq_strct*  instruction_seq,
                                                     struct instruction_strct*      instruction);

// ... Instruction
struct instruction_strct* create_create_instruction(unsigned int                node_index,
                                                    char*                       var_name,
                                                    char*                       method_name,
                                                    struct argument_seq_strct*  argument_seq);

struct instruction_strct* create_assign_instruction(unsigned int        node_index,
                                                    char*               id_name,
                                                    struct expr_strct*  assign_expr);

struct instruction_strct* create_if_instruction(unsigned int                    node_index,
                                                struct expr_strct*              condition,
                                                struct instruction_seq_strct*   branch_true,
                                                struct instruction_seq_strct*   branch_false);

struct instruction_strct* create_loop_instruction(unsigned int                  node_index,
                                                  struct instruction_seq_strct* init,
                                                  struct expr_strct*            condition,
                                                  struct instruction_seq_strct* body);

struct instruction_strct* create_instruction_as_expr(unsigned int        node_index,
                                                     struct expr_strct*  instruction_as_expr);

struct argument_seq_strct* create_argument_seq(unsigned int         node_index,
                                               struct expr_strct*   expr);

struct argument_seq_strct* append_argument_seq(unsigned int                 node_index,
                                               struct argument_seq_strct*   argument_seq,
                                               struct expr_strct*           expr);

// ... Expression
struct expr_strct* create_expr_liter_bool(unsigned int node_index, int liter_bool);
struct expr_strct* create_expr_liter_int (unsigned int node_index, int liter_int);
struct expr_strct* create_expr_liter_char(unsigned int node_index, char liter_char);
struct expr_strct* create_expr_liter_str (unsigned int node_index, struct CharArray* liter_str);

struct expr_strct* create_expr_current(unsigned int node_index);
struct expr_strct* create_expr_call(unsigned int                 node_index,
                                    enum expr_type               call_type,
                                    char*                        method_id_name,
                                    struct argument_seq_strct*   argument_seq);

struct expr_strct* create_expr_precursorcall(unsigned int                 node_index,
                                             char*                        class_id_name,
                                             struct argument_seq_strct*   argument_seq);

struct expr_strct* create_expr_subcall(unsigned int                 node_index,
                                       struct expr_strct*           expr,
                                       char*                        method_id_name,
                                       struct argument_seq_strct*   argument_seq);

struct expr_strct* create_expr_creation(unsigned int                 node_index,
                                        struct type_strct*           create_type,
                                        char*                        method_id_name,
                                        struct argument_seq_strct*   argument_seq);

struct expr_strct* create_expr_operation(unsigned int node_index,
                                         enum expr_type operation_type,
                                         struct expr_strct* expr_left,
                                         struct expr_strct* expr_right);
