#include "print_tree_nodes.h"

void print_identifiers_comma_seq(FILE* dot_file, struct identifiers_comma_seq_strct* identifiers_comma_seq) {
    fprintf(dot_file, "%u[label=\"id <%s>\"];\n", identifiers_comma_seq->_node_index, identifiers_comma_seq->value);
}

void print_program(FILE* dot_file, struct program_strct* program) {
    fprintf(dot_file, "digraph g {\n");
    fprintf(dot_file, "%u[label=\"program\"];\n", program->_node_index);

    struct class_decl_seq_strct* curr = program->class_decl_seq;
    int curr_index = 0;
    while(curr != NULL) {
        print_class_decl_seq(dot_file, curr);
        fprintf(dot_file, "%u -> %u[label=\"%d\"];\n", program->_node_index, curr->_node_index, curr_index);

        curr = curr->next;
        curr_index++;
    }

    fprintf(dot_file, "}\n");
}

void print_class_decl_seq(FILE* dot_file, struct class_decl_seq_strct* class_decl_seq) {
    fprintf(dot_file, "%u[label=\"class sequence element\"];\n", class_decl_seq->_node_index);

    print_class_decl(dot_file, class_decl_seq->value);
    fprintf(dot_file, "%u -> %u;\n", class_decl_seq->_node_index, class_decl_seq->value->_node_index);
}

void print_class_decl(FILE* dot_file, struct class_decl_strct* class_decl) {
    fprintf(dot_file, "%u[label=\"class <%s>\"];\n", class_decl->_node_index, class_decl->id_name);

    if (class_decl->inheritance_block != NULL) {
        print_inheritance_block(dot_file, class_decl->inheritance_block);
        fprintf(dot_file, "%u -> %u;\n", class_decl->_node_index, class_decl->inheritance_block->_node_index);
    }

    if (class_decl->creators_block != NULL) {
        print_creators_block(dot_file, class_decl->creators_block);
        fprintf(dot_file, "%u -> %u;\n", class_decl->_node_index, class_decl->creators_block->_node_index);
    }

    if (class_decl->features_block != NULL) {
        print_features_block(dot_file, class_decl->features_block);
        fprintf(dot_file, "%u -> %u;\n", class_decl->_node_index, class_decl->features_block->_node_index);
    }
}

void print_inheritance_block(FILE* dot_file, struct inheritance_block_strct* inheritance_block) {
    fprintf(dot_file, "%u[label=\"inheritance block\"];\n", inheritance_block->_node_index);

    struct parent_seq_strct* curr = inheritance_block->parent_seq;
    int curr_index = 0;
    while(curr != NULL) {
        print_parent_seq(dot_file, curr);
        fprintf(dot_file, "%u -> %u[label=\"%d\"];\n", inheritance_block->_node_index, curr->_node_index, curr_index);

        curr = curr->next;
        curr_index++;
    }
}

void print_parent_seq(FILE* dot_file, struct parent_seq_strct* parent_seq) {
    fprintf(dot_file, "%u[label=\"parent sequence element\"];\n", parent_seq->_node_index);

    print_parent(dot_file, parent_seq->value);
    fprintf(dot_file, "%u -> %u;\n", parent_seq->_node_index, parent_seq->value->_node_index);
}

void print_parent(FILE* dot_file, struct parent_strct* parent) {
    fprintf(dot_file, "%u[label=\"parent <%s>\"];\n", parent->_node_index, parent->id_name);

    if (parent->parent_info != NULL) {
        print_parent_info(dot_file, parent->parent_info);
        fprintf(dot_file, "%u -> %u;\n", parent->_node_index, parent->parent_info->_node_index);
    }
}

void print_parent_info(FILE* dot_file, struct parent_info_strct* parent_info) {
    fprintf(dot_file, "%u[label=\"parent info\"];\n", parent_info->_node_index);

    if (parent_info->rename_seq != NULL) {
        struct  rename_seq_strct* curr = parent_info->rename_seq;
        int     curr_index = 0;

        while(curr != NULL) {
            print_rename_seq(dot_file, curr);
            fprintf(dot_file, "%u -> %u[label=\"rename: %d\"];\n", parent_info->_node_index, curr->_node_index, curr_index);

            curr = curr->next;
            curr_index++;
        }
    }

    if (parent_info->undefine_seq != NULL) {
        struct  identifiers_comma_seq_strct* curr = parent_info->undefine_seq;
        int     curr_index = 0;

        while(curr != NULL) {
            print_identifiers_comma_seq(dot_file, curr);
            fprintf(dot_file, "%u -> %u[label=\"undef: %d\"];\n", parent_info->_node_index, curr->_node_index, curr_index);

            curr = curr->next;
            curr_index++;
        }
    }

    if (parent_info->redefine_seq != NULL) {
        struct  identifiers_comma_seq_strct* curr = parent_info->redefine_seq;
        int     curr_index = 0;

        while(curr != NULL) {
            print_identifiers_comma_seq(dot_file, curr);
            fprintf(dot_file, "%u -> %u[label=\"redef: %d\"];\n", parent_info->_node_index, curr->_node_index, curr_index);

            curr = curr->next;
            curr_index++;
        }
    }

    if (parent_info->select_seq != NULL) {
        struct  identifiers_comma_seq_strct* curr = parent_info->select_seq;
        int     curr_index = 0;

        while(curr != NULL) {
            print_identifiers_comma_seq(dot_file, curr);
            fprintf(dot_file, "%u -> %u[label=\"sel: %d\"];\n", parent_info->_node_index, curr->_node_index, curr_index);

            curr = curr->next;
            curr_index++;
        }
    }
}

void print_rename_seq(FILE* dot_file, struct rename_seq_strct* rename_seq) {
    fprintf(dot_file, "%u[label=\"<%s> to <%s>\"];\n", rename_seq->_node_index, rename_seq->old_id_name, rename_seq->new_id_name);
}

void print_creators_block(FILE* dot_file, struct creators_block_strct* creators_block) {
    fprintf(dot_file, "%u[label=\"creators block\"];\n", creators_block->_node_index);

    struct  nonempty_creators_block_strct* curr = creators_block->nonempty_creators_block;
    int     curr_index = 0;

    while(curr != NULL) {
        print_nonempty_creators_block(dot_file, curr);
        fprintf(dot_file, "%u -> %u[label=\"sel: %d\"];\n", creators_block->_node_index, curr->_node_index, curr_index);

        curr = curr->next;
        curr_index++;
    }
}

void print_nonempty_creators_block(FILE* dot_file, struct nonempty_creators_block_strct* nonempty_creators_block) {
    fprintf(dot_file, "%u[label=\"creators block element\"];\n", nonempty_creators_block->_node_index);

    struct  identifiers_comma_seq_strct* curr = nonempty_creators_block->value;
    int     curr_index = 0;

    while(curr != NULL) {
        print_identifiers_comma_seq(dot_file, curr);
        fprintf(dot_file, "%u -> %u[label=\"%d\"];\n", nonempty_creators_block->_node_index, curr->_node_index, curr_index);

        curr = curr->next;
        curr_index++;
    }
}

void print_features_block(FILE* dot_file, struct features_block_strct* features_block) {
    fprintf(dot_file, "%u[label=\"features block\"];\n", features_block->_node_index);

    struct  nonempty_features_block_strct* curr = features_block->nonempty_features_block;
    int     curr_index = 0;

    while(curr != NULL) {
        print_nonempty_features_block(dot_file, curr);
        fprintf(dot_file, "%u -> %u[label=\"%d\"];\n", features_block->_node_index, curr->_node_index, curr_index);

        curr = curr->next;
        curr_index++;
    }
}

void print_nonempty_features_block(FILE* dot_file, struct nonempty_features_block_strct* nonempty_features_block) {
    fprintf(dot_file, "%u[label=\"features block element\"];\n", nonempty_features_block->_node_index);

    if (nonempty_features_block->value != NULL) {
        print_feature_decl_seq(dot_file, nonempty_features_block->value);
        fprintf(dot_file, "%u -> %u;\n", nonempty_features_block->_node_index, nonempty_features_block->value->_node_index);
    }
}

void print_feature_decl_seq(FILE* dot_file, struct feature_decl_seq_strct* feature_decl_seq) {
    fprintf(dot_file, "%u[label=\"features sequence\"];\n", feature_decl_seq->_node_index);

    struct  nonempty_feature_decl_seq_strct* curr = feature_decl_seq->nonempty_feature_decl_seq;
    int     curr_index = 0;

    while(curr != NULL) {
        print_nonempty_feature_decl_seq(dot_file, curr);
        fprintf(dot_file, "%u -> %u[label=\"%d\"];\n", feature_decl_seq->_node_index, curr->_node_index, curr_index);

        curr = curr->next;
        curr_index++;
    }
}

void print_nonempty_feature_decl_seq(FILE* dot_file, struct nonempty_feature_decl_seq_strct* nonempty_feature_decl_seq) {
    fprintf(dot_file, "%u[label=\"features sequence element\"];\n", nonempty_feature_decl_seq->_node_index);

    print_feature_decl(dot_file, nonempty_feature_decl_seq->value);
    fprintf(dot_file, "%u -> %u;\n", nonempty_feature_decl_seq->_node_index, nonempty_feature_decl_seq->value->_node_index);
}

void print_feature_decl(FILE* dot_file, struct feature_decl_strct* feature_decl) {
    if (feature_decl->routine_decl_body == NULL) {
        fprintf(dot_file, "%u[label=\"feature decl: attribute\"];\n", feature_decl->_node_index);
    }
    else {
        fprintf(dot_file, "%u[label=\"feature decl: routine\"];\n", feature_decl->_node_index);
    }

    // Print identifiers
    struct  identifiers_comma_seq_strct* curr = feature_decl->identifiers_comma_seq;
    int     curr_index = 0;

    while(curr != NULL) {
        print_identifiers_comma_seq(dot_file, curr);
        fprintf(dot_file, "%u -> %u[label=\"%d\"];\n", feature_decl->_node_index, curr->_node_index, curr_index);

        curr = curr->next;
        curr_index++;
    }

    // Print type
    if (feature_decl->type != NULL) {
        print_type(dot_file, feature_decl->type);
        fprintf(dot_file, "%u -> %u[label=\"type\"];\n", feature_decl->_node_index, feature_decl->type->_node_index);
    }

    // Print parameters sequence
    if (feature_decl->feature_param_seq != NULL) {
        print_ids_with_type_seq(dot_file, feature_decl->feature_param_seq);
        fprintf(dot_file, "%u -> %u;\n", feature_decl->_node_index, feature_decl->feature_param_seq->_node_index);
    }

    // Print routine body
    if (feature_decl->routine_decl_body != NULL) {
        print_routine_decl_body(dot_file, feature_decl->routine_decl_body);
        fprintf(dot_file, "%u -> %u;\n", feature_decl->_node_index, feature_decl->routine_decl_body->_node_index);
    }
}

void print_ids_with_type_seq(FILE* dot_file, struct ids_with_type_seq_strct* ids_with_type_seq) {
    fprintf(dot_file, "%u[label=\"IDs with type sequence\"];\n", ids_with_type_seq->_node_index);

    struct  nonempty_ids_with_type_seq_strct* curr = ids_with_type_seq->nonempty_ids_with_type_seq;
    int     curr_index = 0;

    while(curr != NULL) {
        print_nonempty_ids_with_type_seq(dot_file, curr);
        fprintf(dot_file, "%u -> %u[label=\"%d\"];\n", ids_with_type_seq->_node_index, curr->_node_index, curr_index);

        curr = curr->next;
        curr_index++;
    }
}

void print_nonempty_ids_with_type_seq(FILE* dot_file, struct nonempty_ids_with_type_seq_strct* nonempty_ids_with_type_seq) {
    fprintf(dot_file, "%u[label=\"IDs with type seq elem\"];\n", nonempty_ids_with_type_seq->_node_index);

    print_ids_with_type(dot_file, nonempty_ids_with_type_seq->value);
    fprintf(dot_file, "%u -> %u;\n", nonempty_ids_with_type_seq->_node_index, nonempty_ids_with_type_seq->value->_node_index);
}

void print_ids_with_type(FILE* dot_file, struct ids_with_type_strct* ids_with_type) {
    fprintf(dot_file, "%u[label=\"IDs with type\"];\n", ids_with_type->_node_index);

    struct  identifiers_comma_seq_strct* curr = ids_with_type->identifiers_comma_seq;
    int     curr_index = 0;

    while(curr != NULL) {
        print_identifiers_comma_seq(dot_file, curr);
        fprintf(dot_file, "%u -> %u[label=\"%d\"];\n", ids_with_type->_node_index, curr->_node_index, curr_index);

        curr = curr->next;
        curr_index++;
    }

    print_type(dot_file, ids_with_type->type);
    fprintf(dot_file, "%u -> %u[label=\"type\"];\n", ids_with_type->_node_index, ids_with_type->type->_node_index);
}

void print_type(FILE* dot_file, struct type_strct* type) {
    switch(type->type) {
        case dtype_user_defined:
            fprintf(dot_file, "%u[label=\"custom dtype <%s>\"];\n", type->_node_index, type->id_name);
            break;
        case dtype_boolean:
            fprintf(dot_file, "%u[label=\"dtype <BOOL>\"];\n", type->_node_index);
            break;
        case dtype_character:
            fprintf(dot_file, "%u[label=\"dtype <CHAR>\"];\n", type->_node_index);
            break;
        case dtype_integer_8:
            fprintf(dot_file, "%u[label=\"dtype <INT_8>\"];\n", type->_node_index);
            break;
        case dtype_integer_16:
            fprintf(dot_file, "%u[label=\"dtype <INT_16>\"];\n", type->_node_index);
            break;
        case dtype_integer_32:
            fprintf(dot_file, "%u[label=\"dtype <INT_32>\"];\n", type->_node_index);
            break;
        case dtype_integer_64:
            fprintf(dot_file, "%u[label=\"dtype <INT_64>\"];\n", type->_node_index);
            break;
        case dtype_natural_8:
            fprintf(dot_file, "%u[label=\"dtype <NAT_8>\"];\n", type->_node_index);
            break;
        case dtype_natural_16:
            fprintf(dot_file, "%u[label=\"dtype <NAT_16>\"];\n", type->_node_index);
            break;
        case dtype_natural_32:
            fprintf(dot_file, "%u[label=\"dtype <NAT_32>\"];\n", type->_node_index);
            break;
        case dtype_natural_64:
            fprintf(dot_file, "%u[label=\"dtype <NAT_64>\"];\n", type->_node_index);
            break;
        case dtype_string:
            fprintf(dot_file, "%u[label=\"dtype <STR>\"];\n", type->_node_index);
            break;
    }
}

void print_routine_decl_body(FILE* dot_file, struct routine_decl_body_strct* routine_decl_body) {
    fprintf(dot_file, "%u[label=\"routine body\"];\n", routine_decl_body->_node_index);
}
