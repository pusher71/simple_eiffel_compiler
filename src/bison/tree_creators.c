#include "tree_creators.h"
#include <stdio.h>
#include <stdlib.h>

struct identifiers_comma_seq_strct* create_identifiers_comma_seq(unsigned int node_index, char* id_name) {
    struct identifiers_comma_seq_strct* result = (struct identifiers_comma_seq_strct*)malloc(sizeof(struct identifiers_comma_seq_strct));
    result->_node_index = node_index;
    result->value = id_name;
    result->next = NULL;

    return result;
}

struct identifiers_comma_seq_strct* append_identifiers_comma_seq(unsigned int node_index, struct identifiers_comma_seq_strct* identifiers_comma_seq, char* id_name) {
    struct identifiers_comma_seq_strct* begin = identifiers_comma_seq;

    while (identifiers_comma_seq->next != NULL) {
        identifiers_comma_seq = identifiers_comma_seq->next;
    }

    identifiers_comma_seq->next = create_identifiers_comma_seq(node_index, id_name);
    identifiers_comma_seq->next->_node_index = node_index;

    return begin;
}

struct program_strct* create_program(unsigned int node_index, struct class_decl_seq_strct* class_decl_seq) {
    struct program_strct* result = (struct program_strct*)malloc(sizeof(struct program_strct));
    result->_node_index = node_index;
    result->class_decl_seq = class_decl_seq;

    return result;
}

struct class_decl_seq_strct* create_class_decl_seq(unsigned int node_index, struct class_decl_strct* class_decl) {
    struct class_decl_seq_strct* result = (struct class_decl_seq_strct*)malloc(sizeof(struct class_decl_seq_strct));
    result->_node_index = node_index;
    result->value = class_decl;
    result->next = NULL;

    return result;
}

struct class_decl_seq_strct* append_class_decl_seq(unsigned int node_index, struct class_decl_seq_strct* class_decl_seq, struct class_decl_strct* class_decl) {
    struct class_decl_seq_strct* begin = class_decl_seq;

    while (class_decl_seq->next != NULL) {
        class_decl_seq = class_decl_seq->next;
    }

    class_decl_seq->next = create_class_decl_seq(node_index, class_decl);
    class_decl_seq->next->_node_index = node_index;

    return begin;
}

struct class_decl_strct* create_class_decl(unsigned int                 node_index,
                                           char*                        id_name,
                                           struct parent_seq_strct*     parent_seq,
                                           struct creators_seq_strct*   creators_seq,
                                           struct features_seq_strct*   features_seq
                                           )
{
    struct class_decl_strct* result = (struct class_decl_strct*)malloc(sizeof(struct class_decl_strct));
    result->_node_index = node_index;
    result->id_name = id_name;

    result->parent_seq = parent_seq;
    result->creators_seq = creators_seq;
    result->features_seq = features_seq;

    return result;
}

struct parent_seq_strct* create_parent_seq(unsigned int node_index, struct parent_strct* parent) {
    struct parent_seq_strct* result = (struct parent_seq_strct*)malloc(sizeof(struct parent_seq_strct));
    result->_node_index = node_index;
    result->value = parent;
    result->next = NULL;

    return result;
}

struct parent_seq_strct* append_parent_seq(unsigned int node_index, struct parent_seq_strct* parent_seq, struct parent_strct* parent) {
    struct parent_seq_strct* begin = parent_seq;

    while (parent_seq->next != NULL) {
        parent_seq = parent_seq->next;
    }

    parent_seq->next = create_parent_seq(node_index, parent);
    parent_seq->next->_node_index = node_index;

    return begin;
}

struct parent_strct* create_parent(unsigned int                         node_index,
                                   char*                                id_name,
                                   struct rename_seq_strct*             rename_seq,
                                   struct identifiers_comma_seq_strct*  redefine_seq,
                                   struct identifiers_comma_seq_strct*  select_seq)
{
    struct parent_strct* result = (struct parent_strct*)malloc(sizeof(struct parent_strct));
    result->_node_index     = node_index;
    result->id_name         = id_name;

    result->rename_seq      = rename_seq;
    result->redefine_seq    = redefine_seq;
    result->select_seq      = select_seq;

    return result;
}

struct rename_seq_strct* create_rename_seq(unsigned int node_index, char* old_id_name, char* new_id_name) {
    struct rename_seq_strct* result = (struct rename_seq_strct*)malloc(sizeof(struct rename_seq_strct));
    result->_node_index = node_index;
    result->old_id_name = old_id_name;
    result->new_id_name = new_id_name;
    result->next = NULL;

    return result;
}

struct rename_seq_strct* append_rename_seq(unsigned int node_index, struct rename_seq_strct* rename_seq, char* old_id_name, char* new_id_name) {
    struct rename_seq_strct* begin = rename_seq;

    while (rename_seq->next != NULL) {
        rename_seq = rename_seq->next;
    }

    rename_seq->next = create_rename_seq(node_index, old_id_name, new_id_name);
    rename_seq->next->_node_index = node_index;

    return begin;
}

struct creators_seq_strct* create_creators_seq(unsigned int node_index,
                                               struct identifiers_comma_seq_strct* identifiers_comma_seq)
{
    struct creators_seq_strct* result = (struct creators_seq_strct*)malloc(sizeof(struct creators_seq_strct));
    result->_node_index = node_index;
    result->value = identifiers_comma_seq;
    result->next = NULL;

    return result;
}

struct creators_seq_strct* append_creators_seq(unsigned int node_index,
                                               struct creators_seq_strct* creators_seq,
                                               struct identifiers_comma_seq_strct* identifiers_comma_seq)
{
    struct creators_seq_strct* begin = creators_seq;

    while (creators_seq->next != NULL) {
        creators_seq = creators_seq->next;
    }

    creators_seq->next = create_creators_seq(node_index, identifiers_comma_seq);
    creators_seq->next->_node_index = node_index;

    return begin;
}

struct features_seq_strct* create_features_seq(unsigned int node_index, struct feature_decl_seq_strct* feature_decl_seq) {
    struct features_seq_strct* result = (struct features_seq_strct*)malloc(sizeof(struct features_seq_strct));
    result->_node_index = node_index;
    result->value = feature_decl_seq;
    result->next = NULL;

    return result;
}

struct features_seq_strct* append_features_seq(unsigned int node_index,
                                               struct features_seq_strct* features_seq,
                                               struct feature_decl_seq_strct* feature_decl_seq)
{
    struct features_seq_strct* begin = features_seq;

    while (features_seq->next != NULL) {
        features_seq = features_seq->next;
    }

    features_seq->next = create_features_seq(node_index, feature_decl_seq);
    features_seq->next->_node_index = node_index;

    return begin;
}

struct feature_decl_seq_strct* create_feature_decl_seq(unsigned int node_index, struct feature_decl_strct* feature_decl) {
    struct feature_decl_seq_strct* result = (struct feature_decl_seq_strct*)malloc(sizeof(struct feature_decl_seq_strct));
    result->_node_index = node_index;
    result->value = feature_decl;
    result->next = NULL;

    return result;
}

struct feature_decl_seq_strct* append_feature_decl_seq(unsigned int                     node_index,
                                                       struct feature_decl_seq_strct*   feature_decl_seq,
                                                       struct feature_decl_strct*       feature_decl)
{
    struct feature_decl_seq_strct* begin = feature_decl_seq;

    while (feature_decl_seq->next != NULL) {
        feature_decl_seq = feature_decl_seq->next;
    }

    feature_decl_seq->next = create_feature_decl_seq(node_index, feature_decl);
    feature_decl_seq->next->_node_index = node_index;

    return begin;
}

struct feature_decl_strct* create_feature_decl(unsigned int                         node_index,
                                               struct identifiers_comma_seq_strct*  identifiers_comma_seq,
                                               struct type_strct*                   type,
                                               struct ids_with_type_seq_strct*      feature_param_seq,
                                               struct ids_with_type_seq_strct*      local_variables,
                                               struct instruction_seq_strct*        routine_body)
{
    struct feature_decl_strct* result = (struct feature_decl_strct*)malloc(sizeof(struct feature_decl_strct));
    result->_node_index = node_index;
    result->identifiers_comma_seq   = identifiers_comma_seq;
    result->type                    = type;

    result->feature_param_seq       = feature_param_seq;
    result->local_variables         = local_variables;
    result->routine_body            = routine_body;

    return result;
}

struct ids_with_type_seq_strct* create_ids_with_type_seq(unsigned int                           node_index,
                                                         struct identifiers_comma_seq_strct*    identifiers_comma_seq,
                                                         struct type_strct*                     type)
{
    struct ids_with_type_seq_strct* result = (struct ids_with_type_seq_strct*)malloc(sizeof(struct ids_with_type_seq_strct));
    result->_node_index = node_index;

    result->identifiers_comma_seq = identifiers_comma_seq;
    result->type = type;
    result->next = NULL;

    return result;
}

struct ids_with_type_seq_strct* append_ids_with_type_seq(unsigned int                           node_index,
                                                         struct ids_with_type_seq_strct*        ids_with_type_seq,
                                                         struct identifiers_comma_seq_strct*    identifiers_comma_seq,
                                                         struct type_strct*                     type)
{
    struct ids_with_type_seq_strct* begin = ids_with_type_seq;

    while (ids_with_type_seq->next != NULL) {
        ids_with_type_seq = ids_with_type_seq->next;
    }

    ids_with_type_seq->next = create_ids_with_type_seq(node_index, identifiers_comma_seq, type);
    ids_with_type_seq->next->_node_index = node_index;

    return begin;
}

struct type_strct* create_type(unsigned int         node_index,
                               enum type_enum       type,
                               char*                id_name,
                               struct type_strct*   arrayelem_type)
{
    struct type_strct* result = (struct type_strct*)malloc(sizeof(struct type_strct));
    result->_node_index     = node_index;
    result->type            = type;
    result->id_name         = id_name;
    result->arrayelem_type  = arrayelem_type;

    return result;
}

struct instruction_seq_strct* create_instruction_seq(unsigned int node_index, struct instruction_strct* instruction) {
    struct instruction_seq_strct* result = (struct instruction_seq_strct*)malloc(sizeof(struct instruction_seq_strct));
    result->_node_index = node_index;
    result->value = instruction;
    result->next = NULL;

    return result;
}

struct instruction_seq_strct* append_instruction_seq(unsigned int node_index,
                                                     struct instruction_seq_strct* instruction_seq,
                                                     struct instruction_strct* instruction)
{
    struct instruction_seq_strct* begin = instruction_seq;

    while (instruction_seq->next != NULL) {
        instruction_seq = instruction_seq->next;
    }

    instruction_seq->next = create_instruction_seq(node_index, instruction);
    instruction_seq->next->_node_index = node_index;

    return begin;
}

struct instruction_strct* create_create_instruction(unsigned int                node_index,
                                                    char*                       var_name,
                                                    char*                       creator_name,
                                                    struct argument_seq_strct*  argument_seq)
{
    struct instruction_strct* result = (struct instruction_strct*)malloc(sizeof(struct instruction_strct));
    result->_node_index         = node_index;
    result->type                = instruction_create;

    result->first_id_name       = var_name;
    result->second_id_name      = creator_name;
    result->argument_seq        = argument_seq;

    result->assign_expr         = NULL;

    result->condition           = NULL;
    result->branch_true         = NULL;
    result->branch_false        = NULL;

    result->init                = NULL;
    result->body                = NULL;

    result->instruction_as_expr = NULL;

    return result;
}

struct instruction_strct* create_assign_instruction(unsigned int        node_index,
                                                    char*               id_name,
                                                    struct expr_strct*  assign_expr)
{
    struct instruction_strct* result = (struct instruction_strct*)malloc(sizeof(struct instruction_strct));
    result->_node_index         = node_index;
    result->type                = instruction_assign;

    result->first_id_name       = id_name;
    result->second_id_name      = NULL;
    result->argument_seq        = NULL;

    result->assign_expr         = assign_expr;

    result->condition           = NULL;
    result->branch_true         = NULL;
    result->branch_false        = NULL;

    result->init                = NULL;
    result->body                = NULL;

    result->instruction_as_expr = NULL;

    return result;
}

struct instruction_strct* create_if_instruction(unsigned int                    node_index,
                                                struct expr_strct*              condition,
                                                struct instruction_seq_strct*   branch_true,
                                                struct instruction_seq_strct*   branch_false)
{
    struct instruction_strct* result = (struct instruction_strct*)malloc(sizeof(struct instruction_strct));
    result->_node_index         = node_index;
    result->type                = instruction_if;

    result->first_id_name       = NULL;
    result->second_id_name      = NULL;
    result->argument_seq        = NULL;

    result->assign_expr         = NULL;

    result->condition           = condition;
    result->branch_true         = branch_true;
    result->branch_false        = branch_false;

    result->init                = NULL;
    result->body                = NULL;

    result->instruction_as_expr = NULL;

    return result;
}


struct instruction_strct* create_loop_instruction(unsigned int                  node_index,
                                                  struct instruction_seq_strct* init,
                                                  struct expr_strct*            condition,
                                                  struct instruction_seq_strct* body)
{
    struct instruction_strct* result = (struct instruction_strct*)malloc(sizeof(struct instruction_strct));
    result->_node_index         = node_index;
    result->type                = instruction_loop;

    result->first_id_name       = NULL;
    result->second_id_name      = NULL;
    result->argument_seq        = NULL;

    result->assign_expr         = NULL;

    result->condition           = condition;
    result->branch_true         = NULL;
    result->branch_false        = NULL;

    result->init                = init;
    result->body                = body;

    result->instruction_as_expr = NULL;

    return result;
}

struct instruction_strct* create_instruction_as_expr(unsigned int        node_index,
                                                     struct expr_strct*  instruction_as_expr)
{
    struct instruction_strct* result = (struct instruction_strct*)malloc(sizeof(struct instruction_strct));
    result->_node_index         = node_index;
    result->type                = instruction_expr;

    result->first_id_name       = NULL;
    result->second_id_name      = NULL;
    result->argument_seq        = NULL;

    result->assign_expr         = NULL;

    result->condition           = NULL;
    result->branch_true         = NULL;
    result->branch_false        = NULL;

    result->init                = NULL;
    result->body                = NULL;

    result->instruction_as_expr = instruction_as_expr;

    return result;
}

struct argument_seq_strct* create_argument_seq(unsigned int         node_index,
                                               struct expr_strct*   expr)
{
    struct argument_seq_strct* result = (struct argument_seq_strct*)malloc(sizeof(struct argument_seq_strct));
    result->_node_index = node_index;

    result->value       = expr;
    result->next        = NULL;

    return result;
}

struct argument_seq_strct* append_argument_seq(unsigned int                 node_index,
                                               struct argument_seq_strct*   argument_seq,
                                               struct expr_strct*           expr)
{
    struct argument_seq_strct* begin = argument_seq;

    while (argument_seq->next != NULL) {
        argument_seq = argument_seq->next;
    }

    argument_seq->next = create_argument_seq(node_index, expr);
    argument_seq->next->_node_index = node_index;

    return begin;
}

struct expr_strct* create_expr_liter_bool(unsigned int node_index, int liter_bool) {
    struct expr_strct* result = (struct expr_strct*)malloc(sizeof(struct expr_strct));
    result->_node_index         = node_index;
    result->type                = expr_liter_bool;
    result->is_parenthesized    = 0;

    result->class_id_name   = NULL;
    result->method_id_name  = NULL;
    result->argument_seq    = NULL;
    result->is_field_access = 0;

    result->liter_bool      = liter_bool;
    result->liter_int       = 0;
    result->liter_char      = 0;
    result->liter_str       = NULL;

    result->expr_left       = NULL;
    result->expr_right      = NULL;

    result->create_type     = NULL;

    return result;
}

struct expr_strct* create_expr_liter_int(unsigned int node_index, int liter_int) {
    struct expr_strct* result = (struct expr_strct*)malloc(sizeof(struct expr_strct));
    result->_node_index         = node_index;
    result->type                = expr_liter_int;
    result->is_parenthesized    = 0;

    result->class_id_name   = NULL;
    result->method_id_name  = NULL;
    result->argument_seq    = NULL;
    result->is_field_access = 0;

    result->liter_bool      = 0;
    result->liter_int       = liter_int;
    result->liter_char      = 0;
    result->liter_str       = NULL;

    result->expr_left       = NULL;
    result->expr_right      = NULL;

    result->create_type     = NULL;

    return result;
}

struct expr_strct* create_expr_liter_char(unsigned int node_index, char liter_char) {
    struct expr_strct* result = (struct expr_strct*)malloc(sizeof(struct expr_strct));
    result->_node_index         = node_index;
    result->type                = expr_liter_char;
    result->is_parenthesized    = 0;

    result->class_id_name   = NULL;
    result->method_id_name  = NULL;
    result->argument_seq    = NULL;
    result->is_field_access = 0;

    result->liter_bool      = 0;
    result->liter_int       = 0;
    result->liter_char      = liter_char;
    result->liter_str       = NULL;

    result->expr_left       = NULL;
    result->expr_right      = NULL;

    result->create_type     = NULL;

    return result;
}

struct expr_strct* create_expr_liter_str(unsigned int node_index, struct CharArray* liter_str) {
    struct expr_strct* result = (struct expr_strct*)malloc(sizeof(struct expr_strct));
    result->_node_index         = node_index;
    result->type                = expr_liter_str;
    result->is_parenthesized    = 0;

    result->class_id_name   = NULL;
    result->method_id_name  = NULL;
    result->argument_seq    = NULL;
    result->is_field_access = 0;

    result->liter_bool      = 0;
    result->liter_int       = 0;
    result->liter_char      = 0;
    result->liter_str       = liter_str;

    result->expr_left       = NULL;
    result->expr_right      = NULL;

    result->create_type     = NULL;

    return result;
}

struct expr_strct* create_expr_liter_void(unsigned int node_index) {
    struct expr_strct* result = (struct expr_strct*)malloc(sizeof(struct expr_strct));
    result->_node_index         = node_index;
    result->type                = expr_liter_void;
    result->is_parenthesized    = 0;

    result->class_id_name   = NULL;
    result->method_id_name  = NULL;
    result->argument_seq    = NULL;
    result->is_field_access = 0;

    result->liter_bool      = 0;
    result->liter_int       = 0;
    result->liter_char      = 0;
    result->liter_str       = NULL;

    result->expr_left       = NULL;
    result->expr_right      = NULL;

    result->create_type     = NULL;

    return result;
}

struct expr_strct* create_expr_current(unsigned int node_index) {
    struct expr_strct* result = (struct expr_strct*)malloc(sizeof(struct expr_strct));
    result->_node_index         = node_index;
    result->type                = expr_current;
    result->is_parenthesized    = 0;

    result->class_id_name   = NULL;
    result->method_id_name  = NULL;
    result->argument_seq    = NULL;
    result->is_field_access = 0;

    result->liter_bool      = 0;
    result->liter_int       = 0;
    result->liter_char      = 0;
    result->liter_str       = NULL;

    result->expr_left       = NULL;
    result->expr_right      = NULL;

    result->create_type     = NULL;

    return result;
}

struct expr_strct* create_expr_call(unsigned int                 node_index,
                                    enum expr_type               call_type,
                                    char*                        method_id_name,
                                    struct argument_seq_strct*   argument_seq,
                                    int                          is_field_access)
{
    struct expr_strct* result = (struct expr_strct*)malloc(sizeof(struct expr_strct));
    result->_node_index         = node_index;
    result->type                = call_type;
    result->is_parenthesized    = 0;

    result->class_id_name   = NULL;
    result->method_id_name  = method_id_name;
    result->argument_seq    = argument_seq;
    result->is_field_access = is_field_access;

    result->liter_bool      = 0;
    result->liter_int       = 0;
    result->liter_char      = 0;
    result->liter_str       = NULL;

    result->expr_left       = NULL;
    result->expr_right      = NULL;

    result->create_type     = NULL;

    return result;
}

struct expr_strct* create_expr_precursorcall(unsigned int                 node_index,
                                             char*                        class_id_name,
                                             struct argument_seq_strct*   argument_seq)
{
    struct expr_strct* result = (struct expr_strct*)malloc(sizeof(struct expr_strct));
    result->_node_index         = node_index;
    result->type                = expr_call_precursor;
    result->is_parenthesized    = 0;

    result->class_id_name   = class_id_name;
    result->method_id_name  = NULL;
    result->argument_seq    = argument_seq;
    result->is_field_access = 0;

    result->liter_bool      = 0;
    result->liter_int       = 0;
    result->liter_char      = 0;
    result->liter_str       = NULL;

    result->expr_left       = NULL;
    result->expr_right      = NULL;

    result->create_type     = NULL;

    return result;
}

struct expr_strct* create_expr_subcall(unsigned int                 node_index,
                                       struct expr_strct*           expr,
                                       char*                        method_id_name,
                                       struct argument_seq_strct*   argument_seq,
                                       int                          is_field_access)
{
    struct expr_strct* result = (struct expr_strct*)malloc(sizeof(struct expr_strct));
    result->_node_index         = node_index;
    result->type                = expr_subcall;
    result->is_parenthesized    = 0;

    result->class_id_name   = NULL;
    result->method_id_name  = method_id_name;
    result->argument_seq    = argument_seq;
    result->is_field_access = is_field_access;

    result->liter_bool      = 0;
    result->liter_int       = 0;
    result->liter_char      = 0;
    result->liter_str       = NULL;

    result->expr_left       = expr;
    result->expr_right      = NULL;

    result->create_type     = NULL;

    return result;
}

struct expr_strct* create_expr_creation(unsigned int                 node_index,
                                        struct type_strct*           create_type,
                                        char*                        method_id_name,
                                        struct argument_seq_strct*   argument_seq)
{
    struct expr_strct* result = (struct expr_strct*)malloc(sizeof(struct expr_strct));
    result->_node_index         = node_index;
    result->type                = expr_create;
    result->is_parenthesized    = 0;

    result->class_id_name   = NULL;
    result->method_id_name  = method_id_name;
    result->argument_seq    = argument_seq;
    result->is_field_access = 0;

    result->liter_bool      = 0;
    result->liter_int       = 0;
    result->liter_char      = 0;
    result->liter_str       = NULL;

    result->expr_left       = NULL;
    result->expr_right      = NULL;

    result->create_type     = create_type;

    return result;
}

struct expr_strct* create_expr_operation(unsigned int node_index,
                                         enum expr_type operation_type,
                                         struct expr_strct* expr_left,
                                         struct expr_strct* expr_right)
{
    struct expr_strct* result = (struct expr_strct*)malloc(sizeof(struct expr_strct));
    result->_node_index         = node_index;
    result->type                = operation_type;
    result->is_parenthesized    = 0;

    result->class_id_name   = NULL;
    result->method_id_name  = NULL;
    result->argument_seq    = NULL;
    result->is_field_access = 0;

    result->liter_bool      = -1;
    result->liter_int       = 0;
    result->liter_char      = 0;
    result->liter_str       = NULL;

    result->expr_left       = expr_left;
    result->expr_right      = expr_right;

    result->create_type     = NULL;

    return result;
}
