#include "tree_creators.h"
#include <stdio.h>
#include <stdlib.h>

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

struct class_decl_strct* create_class_decl(unsigned int node_index,
                                           char* id_name,
                                           struct inheritance_block_strct* inheritance_block,
                                           struct creators_block_strct* creators_block,
                                           struct features_block_strct* features_block
                                           )
{
    struct class_decl_strct* result = (struct class_decl_strct*)malloc(sizeof(struct class_decl_strct));
    result->_node_index = node_index;
    result->id_name = id_name;

    result->inheritance_block = inheritance_block;
    result->creators_block = creators_block;
    result->features_block = features_block;

    return result;
}

struct inheritance_block_strct* create_inheritance_block(unsigned int node_index, struct parent_seq_strct* parent_seq) {
    struct inheritance_block_strct* result = (struct inheritance_block_strct*)malloc(sizeof(struct inheritance_block_strct));
    result->_node_index = node_index;
    result->parent_seq = parent_seq;

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

struct parent_strct* create_parent(unsigned int node_index, char* id_name, struct parent_info_strct* parent_info) {
    struct parent_strct* result = (struct parent_strct*)malloc(sizeof(struct parent_strct));
    result->_node_index = node_index;
    result->id_name = id_name;
    result->parent_info = parent_info;

    return result;
}

struct parent_info_strct* create_parent_info(unsigned int node_index,
                                             struct rename_seq_strct* rename_seq,
                                             struct identifiers_comma_seq_strct* undefine_seq,
                                             struct identifiers_comma_seq_strct* redefine_seq,
                                             struct identifiers_comma_seq_strct* select_seq)
{
    struct parent_info_strct* result = (struct parent_info_strct*)malloc(sizeof(struct parent_info_strct));
    result->_node_index     = node_index;
    result->rename_seq      = rename_seq;
    result->redefine_seq    = redefine_seq;
    result->undefine_seq    = undefine_seq;
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

struct creators_block_strct* create_creators_block(unsigned int node_index, struct nonempty_creators_block_strct* nonempty_creators_block) {
    struct creators_block_strct* result = (struct creators_block_strct*)malloc(sizeof(struct creators_block_strct));
    result->_node_index = node_index;
    result->nonempty_creators_block = nonempty_creators_block;

    return result;
}

struct nonempty_creators_block_strct* create_nonempty_creators_block(unsigned int node_index,
                                                                     struct identifiers_comma_seq_strct* identifiers_comma_seq)
{
    struct nonempty_creators_block_strct* result = (struct nonempty_creators_block_strct*)malloc(sizeof(struct nonempty_creators_block_strct));
    result->_node_index = node_index;
    result->value = identifiers_comma_seq;
    result->next = NULL;

    return result;
}

struct nonempty_creators_block_strct* append_nonempty_creators_block(unsigned int node_index,
                                                                     struct nonempty_creators_block_strct* nonempty_creators_block,
                                                                     struct identifiers_comma_seq_strct* identifiers_comma_seq)
{
    struct nonempty_creators_block_strct* begin = nonempty_creators_block;

    while (nonempty_creators_block->next != NULL) {
        nonempty_creators_block = nonempty_creators_block->next;
    }

    nonempty_creators_block->next = create_nonempty_creators_block(node_index, identifiers_comma_seq);
    nonempty_creators_block->next->_node_index = node_index;

    return begin;
}

struct features_block_strct* create_features_block(unsigned int node_index, struct nonempty_features_block_strct* nonempty_features_block) {
    struct features_block_strct* result = (struct features_block_strct*)malloc(sizeof(struct features_block_strct));
    result->_node_index = node_index;
    result->nonempty_features_block = nonempty_features_block;

    return result;
}

struct nonempty_features_block_strct* create_nonempty_features_block(unsigned int node_index, struct feature_decl_seq_strct* feature_decl_seq) {
    struct nonempty_features_block_strct* result = (struct nonempty_features_block_strct*)malloc(sizeof(struct nonempty_features_block_strct));
    result->_node_index = node_index;
    result->value = feature_decl_seq;
    result->next = NULL;

    return result;
}

struct nonempty_features_block_strct* append_nonempty_features_block(unsigned int node_index,
                                                                     struct nonempty_features_block_strct* nonempty_features_block,
                                                                     struct feature_decl_seq_strct* feature_decl_seq)
{
    struct nonempty_features_block_strct* begin = nonempty_features_block;

    while (nonempty_features_block->next != NULL) {
        nonempty_features_block = nonempty_features_block->next;
    }

    nonempty_features_block->next = create_nonempty_features_block(node_index, feature_decl_seq);
    nonempty_features_block->next->_node_index = node_index;

    return begin;
}

struct feature_decl_seq_strct* create_feature_decl_seq(unsigned int node_index, struct nonempty_feature_decl_seq_strct* nonempty_feature_decl_seq) {
    struct feature_decl_seq_strct* result = (struct feature_decl_seq_strct*)malloc(sizeof(struct feature_decl_seq_strct));
    result->_node_index = node_index;
    result->nonempty_feature_decl_seq = nonempty_feature_decl_seq;

    return result;
}

struct nonempty_feature_decl_seq_strct* create_nonempty_feature_decl_seq(unsigned int node_index, struct feature_decl_strct* feature_decl) {
    struct nonempty_feature_decl_seq_strct* result = (struct nonempty_feature_decl_seq_strct*)malloc(sizeof(struct nonempty_feature_decl_seq_strct));
    result->_node_index = node_index;
    result->value = feature_decl;
    result->next = NULL;

    return result;
}

struct nonempty_feature_decl_seq_strct* append_nonempty_feature_decl_seq(unsigned int node_index,
                                                                         struct nonempty_feature_decl_seq_strct* nonempty_feature_decl_seq,
                                                                         struct feature_decl_strct* feature_decl)
{
    struct nonempty_feature_decl_seq_strct* begin = nonempty_feature_decl_seq;

    while (nonempty_feature_decl_seq->next != NULL) {
        nonempty_feature_decl_seq = nonempty_feature_decl_seq->next;
    }

    nonempty_feature_decl_seq->next = create_nonempty_feature_decl_seq(node_index, feature_decl);
    nonempty_feature_decl_seq->next->_node_index = node_index;

    return begin;
}

struct feature_decl_strct* create_feature_decl(unsigned int node_index,
                                               struct identifiers_comma_seq_strct* identifiers_comma_seq,
                                               struct type_strct* type,
                                               struct ids_with_type_seq_strct* feature_param_seq,
                                               struct routine_decl_body_strct* routine_decl_body)
{
    struct feature_decl_strct* result = (struct feature_decl_strct*)malloc(sizeof(struct feature_decl_strct));
    result->_node_index = node_index;
    result->identifiers_comma_seq   = identifiers_comma_seq;
    result->type                    = type;

    result->feature_param_seq       = feature_param_seq;
    result->routine_decl_body       = routine_decl_body;

    return result;
}

struct ids_with_type_seq_strct* create_ids_with_type_seq(unsigned int node_index, struct nonempty_ids_with_type_seq_strct* nonempty_ids_with_type_seq) {
    struct ids_with_type_seq_strct* result = (struct ids_with_type_seq_strct*)malloc(sizeof(struct ids_with_type_seq_strct));
    result->_node_index = node_index;
    result->nonempty_ids_with_type_seq = nonempty_ids_with_type_seq;

    return result;
}

struct nonempty_ids_with_type_seq_strct* create_nonempty_ids_with_type_seq(unsigned int node_index, struct ids_with_type_strct* ids_with_type) {
    struct nonempty_ids_with_type_seq_strct* result = (struct nonempty_ids_with_type_seq_strct*)malloc(sizeof(struct nonempty_ids_with_type_seq_strct));
    result->_node_index = node_index;
    result->value = ids_with_type;
    result->next = NULL;

    return result;
}

struct nonempty_ids_with_type_seq_strct* append_nonempty_ids_with_type_seq(unsigned int node_index,
                                                                           struct nonempty_ids_with_type_seq_strct* nonempty_ids_with_type_seq,
                                                                           struct ids_with_type_strct* ids_with_type)
{
    struct nonempty_ids_with_type_seq_strct* begin = nonempty_ids_with_type_seq;

    while (nonempty_ids_with_type_seq->next != NULL) {
        nonempty_ids_with_type_seq = nonempty_ids_with_type_seq->next;
    }

    nonempty_ids_with_type_seq->next = create_nonempty_ids_with_type_seq(node_index, ids_with_type);
    nonempty_ids_with_type_seq->next->_node_index = node_index;

    return begin;
}

struct ids_with_type_strct* create_ids_with_type(unsigned int node_index, struct identifiers_comma_seq_strct* identifiers_comma_seq, struct type_strct* type) {
    struct ids_with_type_strct* result = (struct ids_with_type_strct*)malloc(sizeof(struct ids_with_type_strct));
    result->_node_index = node_index;
    result->identifiers_comma_seq = identifiers_comma_seq;
    result->type = type;

    return result;
}

struct type_strct* create_type(unsigned int node_index, enum type_enum type, char* id_name) {
    struct type_strct* result = (struct type_strct*)malloc(sizeof(struct type_strct));
    result->_node_index = node_index;
    result->type = type;
    result->id_name = id_name;

    return result;
}

struct routine_decl_body_strct* create_routine_decl_body(unsigned int node_index,
                                                         struct ids_with_type_seq_strct* local_ids_with_type_seq,
                                                         struct instruction_seq_strct* instruction_seq)
{
    struct routine_decl_body_strct* result = (struct routine_decl_body_strct*)malloc(sizeof(struct routine_decl_body_strct));
    result->_node_index = node_index;
    result->local_ids_with_type_seq = local_ids_with_type_seq;
    result->instruction_seq = instruction_seq;

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

struct instruction_strct* create_create_instruction(unsigned int node_index, char* var_name, char* method_name, struct argument_seq_strct* argument_seq) {
    struct instruction_strct* result = (struct instruction_strct*)malloc(sizeof(struct instruction_strct));
    result->_node_index = node_index;
    result->type = instr_create;

    result->first_id_name   = var_name;
    result->second_id_name  = method_name;
    result->argument_seq    = argument_seq;

    result->call = NULL;

    result->expr_left       = NULL;
    result->expr_right      = NULL;

    result->condition       = NULL;
    result->branch_true     = NULL;
    result->branch_false    = NULL;

    result->init            = NULL;
    result->body            = NULL;

    return result;
}

struct instruction_strct* create_assignment_instruction(unsigned int node_index,
                                                struct expr_strct* expr_left,
                                                struct expr_strct* expr_right) {
    struct instruction_strct* result = (struct instruction_strct*)malloc(sizeof(struct instruction_strct));
    result->_node_index = node_index;
    result->type = instr_assignment;

    result->first_id_name   = NULL;
    result->second_id_name  = NULL;
    result->argument_seq    = NULL;

    result->call = NULL;

    result->expr_left       = expr_left;
    result->expr_right      = expr_right;

    result->condition       = NULL;
    result->branch_true     = NULL;
    result->branch_false    = NULL;

    result->init            = NULL;
    result->body            = NULL;

    return result;
}

struct instruction_strct* create_if_instruction(unsigned int node_index,
                                                struct expr_strct* condition,
                                                struct instruction_seq_strct* branch_true,
                                                struct instruction_seq_strct* branch_false) {
    struct instruction_strct* result = (struct instruction_strct*)malloc(sizeof(struct instruction_strct));
    result->_node_index = node_index;
    result->type = instr_if;

    result->first_id_name   = NULL;
    result->second_id_name  = NULL;
    result->argument_seq    = NULL;

    result->call = NULL;

    result->expr_left       = NULL;
    result->expr_right      = NULL;

    result->condition       = condition;
    result->branch_true     = branch_true;
    result->branch_false    = branch_false;

    result->init            = NULL;
    result->body            = NULL;

    return result;
}


struct instruction_strct* create_loop_instruction(unsigned int node_index,
                                                struct instruction_strct* init,
                                                struct expr_strct* condition,
                                                struct instruction_seq_strct* body) {
    struct instruction_strct* result = (struct instruction_strct*)malloc(sizeof(struct instruction_strct));
    result->_node_index = node_index;
    result->type = instr_loop;

    result->first_id_name   = NULL;
    result->second_id_name  = NULL;
    result->argument_seq    = NULL;

    result->call = NULL;

    result->expr_left       = NULL;
    result->expr_right      = NULL;

    result->condition       = condition;
    result->branch_true     = NULL;
    result->branch_false    = NULL;

    result->init            = init;
    result->body            = body;

    return result;
}

struct instruction_strct* create_call_instruction(unsigned int node_index, struct call_strct* call) {
    struct instruction_strct* result = (struct instruction_strct*)malloc(sizeof(struct instruction_strct));
    result->_node_index = node_index;
    result->type = instr_call;

    result->first_id_name   = NULL;
    result->second_id_name  = NULL;
    result->argument_seq    = NULL;

    result->call = call;

    result->condition       = NULL;
    result->branch_true     = NULL;
    result->branch_false    = NULL;

    result->init            = NULL;
    result->body            = NULL;

    return result;
}

struct call_strct* create_call_my_method(unsigned int node_index,
                                         char* id_name,
                                         struct argument_seq_strct* argument_seq,
                                         struct call_sub_seq_strct* call_sub_seq)
{
    struct call_strct* result = (struct call_strct*)malloc(sizeof(struct call_strct));
    result->_node_index = node_index;
    result->type        = call_my_method;

    result->call_sub_seq        = call_sub_seq;
    result->id_name             = id_name;
    result->argument_seq        = argument_seq;

    result->parenthesized_expr  = NULL;

    return result;
}

struct call_strct* create_call_method_of_current(unsigned int node_index,
                                                 struct call_sub_seq_strct* call_sub_seq)
{
    struct call_strct* result = (struct call_strct*)malloc(sizeof(struct call_strct));
    result->_node_index = node_index;
    result->type        = call_current;

    result->call_sub_seq        = call_sub_seq;
    result->id_name             = NULL;
    result->argument_seq        = NULL;

    result->parenthesized_expr  = NULL;

    return result;
}

struct call_strct* create_call_method_of_result(unsigned int node_index,
                                                struct call_sub_seq_strct* call_sub_seq)
{
    struct call_strct* result = (struct call_strct*)malloc(sizeof(struct call_strct));
    result->_node_index = node_index;
    result->type        = call_result;

    result->call_sub_seq        = call_sub_seq;
    result->id_name             = NULL;
    result->argument_seq        = NULL;

    result->parenthesized_expr  = NULL;

    return result;
}

struct call_strct* create_call_method_of_paren_expr(unsigned int node_index,
                                                    struct expr_strct* parenthesized_expr,
                                                    struct call_sub_seq_strct* call_sub_seq)
{
    struct call_strct* result = (struct call_strct*)malloc(sizeof(struct call_strct));
    result->_node_index = node_index;
    result->type        = call_parenthesized_expr;

    result->call_sub_seq        = call_sub_seq;
    result->id_name             = NULL;
    result->argument_seq        = NULL;

    result->parenthesized_expr  = parenthesized_expr;

    return result;
}

struct call_strct* create_call_precursor(unsigned int node_index,
                                         char* id_name,
                                         struct argument_seq_strct* argument_seq,
                                         struct call_sub_seq_strct* call_sub_seq)
{
    struct call_strct* result = (struct call_strct*)malloc(sizeof(struct call_strct));
    result->_node_index = node_index;
    result->type        = call_precursor;

    result->call_sub_seq        = call_sub_seq;

    result->id_name             = id_name;
    result->argument_seq        = argument_seq;
    result->parenthesized_expr  = NULL;

    return result;
}

struct call_sub_seq_strct* create_call_sub_seq(unsigned int node_index,
                                               char* id_name,
                                               struct argument_seq_strct* argument_seq)
{
    struct call_sub_seq_strct* result = (struct call_sub_seq_strct*)malloc(sizeof(struct call_sub_seq_strct));
    result->_node_index = node_index;

    result->id_name      = id_name;
    result->argument_seq = argument_seq;

    result->next = NULL;

    return result;
}

struct call_sub_seq_strct* append_call_sub_seq(unsigned int node_index,
                                               struct call_sub_seq_strct* call_sub_seq,
                                               char* id_name,
                                               struct argument_seq_strct* argument_seq)
{
    struct call_sub_seq_strct* begin = call_sub_seq;

    while (call_sub_seq->next != NULL) {
        call_sub_seq = call_sub_seq->next;
    }

    call_sub_seq->next = create_call_sub_seq(node_index, id_name, argument_seq);
    call_sub_seq->next->_node_index = node_index;

    return begin;
}

struct argument_seq_strct* create_argument_seq(unsigned int node_index, struct nonempty_argument_seq_strct* nonempty_argument_seq) {
    struct argument_seq_strct* result = (struct argument_seq_strct*)malloc(sizeof(struct argument_seq_strct));
    result->_node_index = node_index;
    result->nonempty_argument_seq = nonempty_argument_seq;

    return result;
}

struct nonempty_argument_seq_strct* create_nonempty_argument_seq(unsigned int node_index,
                                                                 struct expr_strct* expr)
{
    struct nonempty_argument_seq_strct* result = (struct nonempty_argument_seq_strct*)malloc(sizeof(struct nonempty_argument_seq_strct));
    result->_node_index = node_index;

    result->value = expr;
    result->next  = NULL;

    return result;
}

struct nonempty_argument_seq_strct* append_nonempty_argument_seq(unsigned int node_index,
                                                                 struct nonempty_argument_seq_strct* nonempty_argument_seq,
                                                                 struct expr_strct* expr)
{
    struct nonempty_argument_seq_strct* begin = nonempty_argument_seq;

    while (nonempty_argument_seq->next != NULL) {
        nonempty_argument_seq = nonempty_argument_seq->next;
    }

    nonempty_argument_seq->next = create_nonempty_argument_seq(node_index, expr);
    nonempty_argument_seq->next->_node_index = node_index;

    return begin;
}

struct expr_strct* create_expr_liter_bool(unsigned int node_index, int liter_bool) {
    struct expr_strct* result = (struct expr_strct*)malloc(sizeof(struct expr_strct));
    result->_node_index = node_index;
    result->type = expr_liter_bool;

    result->liter_bool  = liter_bool;

    result->liter_str = NULL;
    result->call      = NULL;

    result->expr_left  = NULL;
    result->expr_right = NULL;

    return result;
}

struct expr_strct* create_expr_liter_int(unsigned int node_index, int liter_int) {
    struct expr_strct* result = (struct expr_strct*)malloc(sizeof(struct expr_strct));
    result->_node_index = node_index;
    result->type = expr_liter_int;

    result->liter_int = liter_int;

    result->liter_str = NULL;
    result->call      = NULL;

    result->expr_left  = NULL;
    result->expr_right = NULL;

    return result;
}

struct expr_strct* create_expr_liter_char(unsigned int node_index, char liter_char) {
    struct expr_strct* result = (struct expr_strct*)malloc(sizeof(struct expr_strct));
    result->_node_index = node_index;
    result->type = expr_liter_char;

    result->liter_char  = liter_char;

    result->liter_str = NULL;
    result->call      = NULL;

    result->expr_left  = NULL;
    result->expr_right = NULL;

    return result;
}

struct expr_strct* create_expr_liter_str(unsigned int node_index, struct CharArray* liter_str) {
    struct expr_strct* result = (struct expr_strct*)malloc(sizeof(struct expr_strct));
    result->_node_index = node_index;
    result->type = expr_liter_str;

    result->liter_str = liter_str;
    result->call      = NULL;

    result->expr_left  = NULL;
    result->expr_right = NULL;

    return result;
}

struct expr_strct* create_expr_call(unsigned int node_index, struct call_strct* call) {
    struct expr_strct* result = (struct expr_strct*)malloc(sizeof(struct expr_strct));
    result->_node_index = node_index;
    result->type = expr_call;

    result->liter_str = NULL;
    result->call      = call;

    result->expr_left  = NULL;
    result->expr_right = NULL;

    return result;
}

struct expr_strct* create_expr_operation(unsigned int node_index, struct expr_strct* expr_left, struct expr_strct* expr_right, enum expr_type operation) {
    struct expr_strct* result = (struct expr_strct*)malloc(sizeof(struct expr_strct));
    result->_node_index = node_index;
    result->type = operation;

    result->liter_str = NULL;
    result->call      = NULL;

    result->expr_left  = expr_left;
    result->expr_right = expr_right;

    return result;
}
