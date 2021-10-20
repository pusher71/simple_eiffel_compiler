#pragma once
#include <stdio.h>
#include "tree_nodes.h"

// === COMMON ===
void print_identifiers_comma_seq(FILE* dot_file, struct identifiers_comma_seq_strct* identifiers_comma_seq);

// === MAIN ===
void print_program(FILE* dot_file, struct program_strct* program);
void print_class_decl_seq(FILE* dot_file, struct class_decl_seq_strct* class_decl_seq);

// === CLASS ===
void print_class_decl(FILE* dot_file, struct class_decl_strct* class_decl);

// Inheritance block
void print_inheritance_block(FILE* dot_file, struct inheritance_block_strct* inheritance_block);

void print_parent_seq(FILE* dot_file, struct parent_seq_strct* parent_seq);
void print_parent(FILE* dot_file, struct parent_strct* parent);
void print_parent_info(FILE* dot_file, struct parent_info_strct* parent_info);
void print_rename_seq(FILE* dot_file, struct rename_seq_strct* rename_seq);

// Creators block
void print_creators_block(FILE* dot_file, struct creators_block_strct* creators_block);
void print_nonempty_creators_block(FILE* dot_file, struct nonempty_creators_block_strct* nonempty_creators_block);

// Features block
void print_features_block(FILE* dot_file, struct features_block_strct* features_block);
void print_nonempty_features_block(FILE* dot_file, struct nonempty_features_block_strct* nonempty_features_block);

void print_feature_decl_seq(FILE* dot_file, struct feature_decl_seq_strct* feature_decl_seq);
void print_nonempty_feature_decl_seq(FILE* dot_file, struct nonempty_feature_decl_seq_strct* nonempty_feature_decl_seq);

void print_feature_decl(FILE* dot_file, struct feature_decl_strct* feature_decl);

void print_ids_with_type_seq(FILE* dot_file, struct ids_with_type_seq_strct* ids_with_type_seq);
void print_nonempty_ids_with_type_seq(FILE* dot_file, struct nonempty_ids_with_type_seq_strct* nonempty_ids_with_type_seq);
void print_ids_with_type(FILE* dot_file, struct ids_with_type_strct* ids_with_type);

void print_type(FILE* dot_file, struct type_strct* type);

void print_routine_decl_body(FILE* dot_file, struct routine_decl_body_strct* routine_decl_body);

void print_instruction_seq(FILE* dot_file, struct instruction_seq_strct* instruction_seq);
void print_instruction(FILE* dot_file, struct instruction_strct* instruction);

void print_call(FILE* dot_file, struct call_strct* call);
void print_call_sub_seq(FILE* dot_file, struct call_sub_seq_strct* call_sub_seq);

void print_argument_seq(FILE* dot_file, struct argument_seq_strct* argument_seq);
void print_nonempty_argument_seq(FILE* dot_file, struct nonempty_argument_seq_strct* nonempty_argument_seq);

void print_expr(FILE* dot_file, struct expr_strct* expr);
