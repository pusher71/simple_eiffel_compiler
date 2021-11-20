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
void print_parent_seq(FILE* dot_file, struct parent_seq_strct* parent_seq);
void print_parent(FILE* dot_file, struct parent_strct* parent);
void print_rename_seq(FILE* dot_file, struct rename_seq_strct* rename_seq);

// Creators block
void print_creators_seq(FILE* dot_file, struct creators_seq_strct* creators_seq);

// Features block
void print_features_seq(FILE* dot_file, struct features_seq_strct* features_seq);
void print_feature_decl_seq(FILE* dot_file, struct feature_decl_seq_strct* feature_decl_seq);
void print_feature_decl(FILE* dot_file, struct feature_decl_strct* feature_decl);

void print_ids_with_type_seq(FILE* dot_file, struct ids_with_type_seq_strct* ids_with_type_seq);
void print_type(FILE* dot_file, struct type_strct* type);

void print_instruction_seq(FILE* dot_file, struct instruction_seq_strct* instruction_seq);
void print_instruction(FILE* dot_file, struct instruction_strct* instruction);

void print_argument_seq(FILE* dot_file, struct argument_seq_strct* argument_seq);
void print_expr(FILE* dot_file, struct expr_strct* expr);
