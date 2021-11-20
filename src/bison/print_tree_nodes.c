#include "print_tree_nodes.h"
#include "../flex/utilities/chararray_utilities.h"

void print_identifiers_comma_seq(FILE* dot_file, struct identifiers_comma_seq_strct* identifiers_comma_seq) {
    fprintf(dot_file, "%u[label=\"id <%s>\"];\n", identifiers_comma_seq->_node_index, identifiers_comma_seq->value);
}

void print_program(FILE* dot_file, struct program_strct* program) {
    fprintf(dot_file, "digraph g {\n");
    fprintf(dot_file, "%u[label=\"program\"];\n", program->_node_index);

    struct class_decl_seq_strct* curr       = program->class_decl_seq;
    int                          curr_index = 0;
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

    {
        struct parent_seq_strct* curr       = class_decl->parent_seq;
        int                      curr_index = 0;

        while(curr != NULL) {
            print_parent_seq(dot_file, curr);
            fprintf(dot_file, "%u -> %u[label=\"parent: %d\"];\n", class_decl->_node_index, curr->_node_index, curr_index);

            curr = curr->next;
            curr_index++;
        }
    }

    {
        struct creators_seq_strct* curr       = class_decl->creators_seq;
        int                        curr_index = 0;

        while(curr != NULL) {
            print_creators_seq(dot_file, curr);
            fprintf(dot_file, "%u -> %u[label=\"creators: %d\"];\n", class_decl->_node_index, curr->_node_index, curr_index);

            curr = curr->next;
            curr_index++;
        }
    }

    {
        struct features_seq_strct* curr       = class_decl->features_seq;
        int                        curr_index = 0;

        while(curr != NULL) {
            print_features_seq(dot_file, curr);
            fprintf(dot_file, "%u -> %u[label=\"features: %d\"];\n", class_decl->_node_index, curr->_node_index, curr_index);

            curr = curr->next;
            curr_index++;
        }
    }
}

void print_parent_seq(FILE* dot_file, struct parent_seq_strct* parent_seq) {
    fprintf(dot_file, "%u[label=\"parent sequence element\"];\n", parent_seq->_node_index);

    print_parent(dot_file, parent_seq->value);
    fprintf(dot_file, "%u -> %u;\n", parent_seq->_node_index, parent_seq->value->_node_index);
}

void print_parent(FILE* dot_file, struct parent_strct* parent) {
    fprintf(dot_file, "%u[label=\"parent <%s>\"];\n", parent->_node_index, parent->id_name);

    {
        struct  rename_seq_strct* curr = parent->rename_seq;
        int     curr_index = 0;

        while(curr != NULL) {
            print_rename_seq(dot_file, curr);
            fprintf(dot_file, "%u -> %u[label=\"rename: %d\"];\n", parent->_node_index, curr->_node_index, curr_index);

            curr = curr->next;
            curr_index++;
        }
    }

    {
        struct  identifiers_comma_seq_strct* curr = parent->redefine_seq;
        int     curr_index = 0;

        while(curr != NULL) {
            print_identifiers_comma_seq(dot_file, curr);
            fprintf(dot_file, "%u -> %u[label=\"redef: %d\"];\n", parent->_node_index, curr->_node_index, curr_index);

            curr = curr->next;
            curr_index++;
        }
    }

    {
        struct  identifiers_comma_seq_strct* curr = parent->select_seq;
        int     curr_index = 0;

        while(curr != NULL) {
            print_identifiers_comma_seq(dot_file, curr);
            fprintf(dot_file, "%u -> %u[label=\"sel: %d\"];\n", parent->_node_index, curr->_node_index, curr_index);

            curr = curr->next;
            curr_index++;
        }
    }
}

void print_rename_seq(FILE* dot_file, struct rename_seq_strct* rename_seq) {
    fprintf(dot_file, "%u[label=\"<%s> to <%s>\"];\n", rename_seq->_node_index, rename_seq->old_id_name, rename_seq->new_id_name);
}

void print_creators_seq(FILE* dot_file, struct creators_seq_strct* creators_seq) {
    fprintf(dot_file, "%u[label=\"creators block\"];\n", creators_seq->_node_index);

    {
        struct  identifiers_comma_seq_strct* curr = creators_seq->value;
        int curr_index = 0;

        while(curr != NULL) {
            print_identifiers_comma_seq(dot_file, curr);
            fprintf(dot_file, "%u -> %u[label=\"%d\"];\n", creators_seq->_node_index, curr->_node_index, curr_index);

            curr = curr->next;
            curr_index++;
        }
    }
}

void print_features_seq(FILE* dot_file, struct features_seq_strct* features_seq) {
    fprintf(dot_file, "%u[label=\"features block\"];\n", features_seq->_node_index);

    struct  feature_decl_seq_strct* curr = features_seq->value;
    int     curr_index = 0;

    while(curr != NULL) {
        print_feature_decl_seq(dot_file, curr);
        fprintf(dot_file, "%u -> %u[label=\"%d\"];\n", features_seq->_node_index, curr->_node_index, curr_index);

        curr = curr->next;
        curr_index++;
    }
}

void print_feature_decl_seq(FILE* dot_file, struct feature_decl_seq_strct* feature_decl_seq) {
    fprintf(dot_file, "%u[label=\"feature decl\"];\n", feature_decl_seq->_node_index);

    print_feature_decl(dot_file, feature_decl_seq->value);
    fprintf(dot_file, "%u -> %u;\n", feature_decl_seq->_node_index, feature_decl_seq->value->_node_index);
}

void print_feature_decl(FILE* dot_file, struct feature_decl_strct* feature_decl) {
    if (feature_decl->routine_body == NULL) {
        fprintf(dot_file, "%u[label=\"feature decl: attribute\"];\n", feature_decl->_node_index);
    }
    else {
        fprintf(dot_file, "%u[label=\"feature decl: routine\"];\n", feature_decl->_node_index);
    }

    // Print identifiers
    {
        struct  identifiers_comma_seq_strct* curr = feature_decl->identifiers_comma_seq;
        int     curr_index = 0;

        while(curr != NULL) {
            print_identifiers_comma_seq(dot_file, curr);
            fprintf(dot_file, "%u -> %u[label=\"%d\"];\n", feature_decl->_node_index, curr->_node_index, curr_index);

            curr = curr->next;
            curr_index++;
        }
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
    {
        struct ids_with_type_seq_strct* curr = feature_decl->local_variables;
        int curr_index = 0;

        while(curr != NULL) {
            print_ids_with_type_seq(dot_file, curr);
            fprintf(dot_file, "%u -> %u[label=\"local: %d\"];\n", feature_decl->_node_index, curr->_node_index, curr_index);

            curr = curr->next;
            curr_index++;
        }
    }

    {
        struct instruction_seq_strct* curr = feature_decl->routine_body;
        int curr_index = 0;

        while(curr != NULL) {
            print_instruction_seq(dot_file, curr);
            fprintf(dot_file, "%u -> %u[label=\"%d\"];\n", feature_decl->_node_index, curr->_node_index, curr_index);

            curr = curr->next;
            curr_index++;
        }
    }
}

void print_ids_with_type_seq(FILE* dot_file, struct ids_with_type_seq_strct* ids_with_type_seq) {
    fprintf(dot_file, "%u[label=\"IDs with type\"];\n", ids_with_type_seq->_node_index);

    struct identifiers_comma_seq_strct* curr = ids_with_type_seq->identifiers_comma_seq;
    int curr_index = 0;

    while(curr != NULL) {
        print_identifiers_comma_seq(dot_file, curr);
        fprintf(dot_file, "%u -> %u[label=\"%d\"];\n", ids_with_type_seq->_node_index, curr->_node_index, curr_index);

        curr = curr->next;
        curr_index++;
    }

    print_type(dot_file, ids_with_type_seq->type);
    fprintf(dot_file, "%u -> %u[label=\"type\"];\n", ids_with_type_seq->_node_index, ids_with_type_seq->type->_node_index);
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
        case dtype_integer:
            fprintf(dot_file, "%u[label=\"dtype <INT>\"];\n", type->_node_index);
            break;
        case dtype_natural:
            fprintf(dot_file, "%u[label=\"dtype <NAT>\"];\n", type->_node_index);
            break;
        case dtype_string:
            fprintf(dot_file, "%u[label=\"dtype <STR>\"];\n", type->_node_index);
            break;
        case dtype_array:
            fprintf(dot_file, "%u[label=\"dtype <STR>\"];\n", type->_node_index);

            print_type(dot_file, type->arrayelem_type);
            fprintf(dot_file, "%u -> %u[label=\"elem type\"];\n", type->_node_index, type->arrayelem_type->_node_index);
            break;
    }
}

void print_instruction_seq(FILE* dot_file, struct instruction_seq_strct* instruction_seq) {
    fprintf(dot_file, "%u[label=\"instruction seq elem\"];\n", instruction_seq->_node_index);

    if (instruction_seq->value != NULL) {
        print_instruction(dot_file, instruction_seq->value);
        fprintf(dot_file, "%u -> %u;\n", instruction_seq->_node_index, instruction_seq->value->_node_index);
    }
}

void print_instruction(FILE* dot_file, struct instruction_strct* instruction) {
    switch(instruction->type) {
        case instruction_create:
            if (instruction->second_id_name == NULL) {
                fprintf(dot_file, "%u[label=\"instruction :: basic create <%s>\"];\n", instruction->_node_index, instruction->first_id_name);
            }
            else {
                fprintf(dot_file, "%u[label=\"instruction :: create <%s> with creator <%s>\"];\n", instruction->_node_index, instruction->first_id_name, instruction->second_id_name);
            }

            {
                struct argument_seq_strct* curr = instruction->argument_seq;
                int curr_index = 0;

                while(curr != NULL) {
                    print_argument_seq(dot_file, curr);
                    fprintf(dot_file, "%u -> %u[label=\"%d\"];\n", instruction->_node_index, curr->_node_index, curr_index);

                    curr = curr->next;
                    curr_index++;
                }
            }
            break;

        case instruction_assign:
            fprintf(dot_file, "%u[label=\"instruction :: assign to <%s>\"];\n", instruction->_node_index, instruction->first_id_name);

            print_expr(dot_file, instruction->assign_expr);
            fprintf(dot_file, "%u -> %u[label=\"assign expr\"];\n", instruction->_node_index, instruction->assign_expr->_node_index);
            break;

        case instruction_if:
            fprintf(dot_file, "%u[label=\":=\"];\n", instruction->_node_index);

            print_expr(dot_file, instruction->condition);
            fprintf(dot_file, "%u -> %u[label=\"instruction :: condition\"];\n", instruction->_node_index, instruction->condition->_node_index);

            {
                struct instruction_seq_strct* curr = instruction->branch_true;
                int curr_index = 0;

                while(curr != NULL) {
                    print_instruction_seq(dot_file, curr);
                    fprintf(dot_file, "%u -> %u[label=\"true instr: %d\"];\n", instruction->_node_index, curr->_node_index, curr_index);

                    curr = curr->next;
                    curr_index++;
                }
            }

            {
                struct instruction_seq_strct* curr = instruction->branch_false;
                int curr_index = 0;

                while(curr != NULL) {
                    print_instruction_seq(dot_file, curr);
                    fprintf(dot_file, "%u -> %u[label=\"false instr: %d\"];\n", instruction->_node_index, curr->_node_index, curr_index);

                    curr = curr->next;
                    curr_index++;
                }
            }

            break;

        case instruction_loop:
            fprintf(dot_file, "%u[label=\"loop\"];\n", instruction->_node_index);

            {
                struct instruction_seq_strct* curr = instruction->init;
                int curr_index = 0;

                while(curr != NULL) {
                    print_instruction_seq(dot_file, curr);
                    fprintf(dot_file, "%u -> %u[label=\"init instr: %d\"];\n", instruction->_node_index, curr->_node_index, curr_index);

                    curr = curr->next;
                    curr_index++;
                }
            }

            print_expr(dot_file, instruction->condition);
            fprintf(dot_file, "%u -> %u[label=\"condition\"];\n", instruction->_node_index, instruction->condition->_node_index);

            {
                struct instruction_seq_strct* curr = instruction->body;
                int curr_index = 0;

                while(curr != NULL) {
                    print_instruction_seq(dot_file, curr);
                    fprintf(dot_file, "%u -> %u[label=\"body instr: %d\"];\n", instruction->_node_index, curr->_node_index, curr_index);

                    curr = curr->next;
                    curr_index++;
                }
            }

            break;

        case instruction_expr:
            fprintf(dot_file, "%u[label=\"instruction as expr\"];\n", instruction->_node_index);

            print_expr(dot_file, instruction->instruction_as_expr);
            fprintf(dot_file, "%u -> %u;\n", instruction->_node_index, instruction->instruction_as_expr->_node_index);
            break;
    }
}

void print_argument_seq(FILE* dot_file, struct argument_seq_strct* argument_seq) {
    fprintf(dot_file, "%u[label=\"argument\"];\n", argument_seq->_node_index);

    print_expr(dot_file, argument_seq->value);
    fprintf(dot_file, "%u -> %u;\n", argument_seq->_node_index, argument_seq->value->_node_index);
}

void print_expr(FILE* dot_file, struct expr_strct* expr) {
    int isSet = 0;
    switch(expr->type) {
        case expr_liter_bool:
            fprintf(dot_file, "%u[label=\"expr :: bool <%d>\"];\n", expr->_node_index, expr->liter_bool);
            break;

        case expr_liter_int:
            fprintf(dot_file, "%u[label=\"expr :: int <%d>\"];\n", expr->_node_index, expr->liter_int);
            break;

        case expr_liter_char:
            fprintf(dot_file, "%u[label=\"expr :: char <%d>\"];\n", expr->_node_index, expr->liter_char);
            break;

        case expr_liter_str:
            fprintf(dot_file, "%u[label=\"expr :: str <%s>\"];\n", expr->_node_index, chaartostr(expr->liter_str));
            break;

        case expr_liter_void:
            fprintf(dot_file, "%u[label=\"expr :: VOID\"];\n", expr->_node_index);
            break;

        case expr_current:
            fprintf(dot_file, "%u[label=\"expr :: CURRENT\"];\n", expr->_node_index);
            break;

        case expr_call_method_or_var:
            fprintf(dot_file, "%u[label=\"expr :: my method or var <%s>\"];\n", expr->_node_index, expr->method_id_name);
            break;

        case expr_call_method:
            fprintf(dot_file, "%u[label=\"expr :: my method <%s>\"];\n", expr->_node_index, expr->method_id_name);

            {
                struct argument_seq_strct* curr = expr->argument_seq;
                int curr_index = 0;

                while(curr != NULL) {
                    print_argument_seq(dot_file, curr);
                    fprintf(dot_file, "%u -> %u[label=\"%d\"];\n", expr->_node_index, curr->_node_index, curr_index);

                    curr = curr->next;
                    curr_index++;
                }
            }

            break;

        case expr_call_precursor:
            if (expr->class_id_name == NULL) {
                fprintf(dot_file, "%u[label=\"expr :: PRECURSOR method\"];\n", expr->_node_index);
            }
            else {
                fprintf(dot_file, "%u[label=\"expr :: PRECURSOR method of class <%s>\"];\n", expr->_node_index, expr->class_id_name);
            }

            {
                struct argument_seq_strct* curr = expr->argument_seq;
                int curr_index = 0;

                while(curr != NULL) {
                    print_argument_seq(dot_file, curr);
                    fprintf(dot_file, "%u -> %u[label=\"%d\"];\n", expr->_node_index, curr->_node_index, curr_index);

                    curr = curr->next;
                    curr_index++;
                }
            }

            break;

        case expr_subcall:
            fprintf(dot_file, "%u[label=\"expr :: subcall <%s>\"];\n", expr->_node_index, expr->method_id_name);

            print_expr(dot_file, expr->expr_left);
            fprintf(dot_file, "%u -> %u[label=\"expr_left\"];\n", expr->_node_index, expr->expr_left->_node_index);

            {
                struct argument_seq_strct* curr = expr->argument_seq;
                int curr_index = 0;

                while(curr != NULL) {
                    print_argument_seq(dot_file, curr);
                    fprintf(dot_file, "%u -> %u[label=\"%d\"];\n", expr->_node_index, curr->_node_index, curr_index);

                    curr = curr->next;
                    curr_index++;
                }
            }

            break;

        case expr_create:
            if (expr->method_id_name == NULL) {
                fprintf(dot_file, "%u[label=\"expr :: basic create of class <%s>\"];\n", expr->_node_index, expr->class_id_name);
            }
            else {
                fprintf(dot_file, "%u[label=\"expr :: create of class <%s> with method <%s>\"];\n", expr->_node_index, expr->class_id_name, expr->method_id_name);
            }

            {
                struct argument_seq_strct* curr = expr->argument_seq;
                int curr_index = 0;

                while(curr != NULL) {
                    print_argument_seq(dot_file, curr);
                    fprintf(dot_file, "%u -> %u[label=\"%d\"];\n", expr->_node_index, curr->_node_index, curr_index);

                    curr = curr->next;
                    curr_index++;
                }
            }

            break;

        case expr_arrelem:
            fprintf(dot_file, "%u[label=\"expr :: arrelem\"];\n", expr->_node_index);

            print_expr(dot_file, expr->expr_left);
            fprintf(dot_file, "%u -> %u[label=\"expr_left\"];\n", expr->_node_index, expr->expr_left->_node_index);

            print_expr(dot_file, expr->expr_right);
            fprintf(dot_file, "%u -> %u[label=\"expr_right\"];\n", expr->_node_index, expr->expr_right->_node_index);
            break;

        case expr_plus:
            fprintf(dot_file, "%u[label=\"+\"];\n", expr->_node_index);

            print_expr(dot_file, expr->expr_left);
            fprintf(dot_file, "%u -> %u[label=\"expr_left\"];\n", expr->_node_index, expr->expr_left->_node_index);

            print_expr(dot_file, expr->expr_right);
            fprintf(dot_file, "%u -> %u[label=\"expr_right\"];\n", expr->_node_index, expr->expr_right->_node_index);
            break;

        case expr_bminus:
            fprintf(dot_file, "%u[label=\"-\"];\n", expr->_node_index);

            print_expr(dot_file, expr->expr_left);
            fprintf(dot_file, "%u -> %u[label=\"expr_left\"];\n", expr->_node_index, expr->expr_left->_node_index);

            print_expr(dot_file, expr->expr_right);
            fprintf(dot_file, "%u -> %u[label=\"expr_right\"];\n", expr->_node_index, expr->expr_right->_node_index);
            break;

        case expr_mul:
            fprintf(dot_file, "%u[label=\"*\"];\n", expr->_node_index);

            print_expr(dot_file, expr->expr_left);
            fprintf(dot_file, "%u -> %u[label=\"expr_left\"];\n", expr->_node_index, expr->expr_left->_node_index);

            print_expr(dot_file, expr->expr_right);
            fprintf(dot_file, "%u -> %u[label=\"expr_right\"];\n", expr->_node_index, expr->expr_right->_node_index);
            break;

        case expr_idiv:
            fprintf(dot_file, "%u[label=\"//\"];\n", expr->_node_index);

            print_expr(dot_file, expr->expr_left);
            fprintf(dot_file, "%u -> %u[label=\"expr_left\"];\n", expr->_node_index, expr->expr_left->_node_index);

            print_expr(dot_file, expr->expr_right);
            fprintf(dot_file, "%u -> %u[label=\"expr_right\"];\n", expr->_node_index, expr->expr_right->_node_index);
            break;

        case expr_uminus:
            fprintf(dot_file, "%u[label=\"-\"];\n", expr->_node_index);

            print_expr(dot_file, expr->expr_right);
            fprintf(dot_file, "%u -> %u;\n", expr->_node_index, expr->expr_right->_node_index);
            break;

        case expr_less:
            fprintf(dot_file, "%u[label=\"<\"];\n", expr->_node_index);

            print_expr(dot_file, expr->expr_left);
            fprintf(dot_file, "%u -> %u[label=\"expr_left\"];\n", expr->_node_index, expr->expr_left->_node_index);

            print_expr(dot_file, expr->expr_right);
            fprintf(dot_file, "%u -> %u[label=\"expr_right\"];\n", expr->_node_index, expr->expr_right->_node_index);
            break;

        case expr_great:
            fprintf(dot_file, "%u[label=\">\"];\n", expr->_node_index);

            print_expr(dot_file, expr->expr_left);
            fprintf(dot_file, "%u -> %u[label=\"expr_left\"];\n", expr->_node_index, expr->expr_left->_node_index);

            print_expr(dot_file, expr->expr_right);
            fprintf(dot_file, "%u -> %u[label=\"expr_right\"];\n", expr->_node_index, expr->expr_right->_node_index);
            break;

        case expr_less_equal:
            fprintf(dot_file, "%u[label=\"<=\"];\n", expr->_node_index);

            print_expr(dot_file, expr->expr_left);
            fprintf(dot_file, "%u -> %u[label=\"expr_left\"];\n", expr->_node_index, expr->expr_left->_node_index);

            print_expr(dot_file, expr->expr_right);
            fprintf(dot_file, "%u -> %u[label=\"expr_right\"];\n", expr->_node_index, expr->expr_right->_node_index);
            break;

        case expr_great_equal:
            fprintf(dot_file, "%u[label=\">=\"];\n", expr->_node_index);

            print_expr(dot_file, expr->expr_left);
            fprintf(dot_file, "%u -> %u[label=\"expr_left\"];\n", expr->_node_index, expr->expr_left->_node_index);

            print_expr(dot_file, expr->expr_right);
            fprintf(dot_file, "%u -> %u[label=\"expr_right\"];\n", expr->_node_index, expr->expr_right->_node_index);
            break;

        case expr_equal:
            fprintf(dot_file, "%u[label=\"equal\"];\n", expr->_node_index);

            print_expr(dot_file, expr->expr_left);
            fprintf(dot_file, "%u -> %u[label=\"expr_left\"];\n", expr->_node_index, expr->expr_left->_node_index);

            print_expr(dot_file, expr->expr_right);
            fprintf(dot_file, "%u -> %u[label=\"expr_right\"];\n", expr->_node_index, expr->expr_right->_node_index);
            break;

        case expr_notequal:
            fprintf(dot_file, "%u[label=\"notequal\"];\n", expr->_node_index);

            print_expr(dot_file, expr->expr_left);
            fprintf(dot_file, "%u -> %u[label=\"expr_left\"];\n", expr->_node_index, expr->expr_left->_node_index);

            print_expr(dot_file, expr->expr_right);
            fprintf(dot_file, "%u -> %u[label=\"expr_right\"];\n", expr->_node_index, expr->expr_right->_node_index);
            break;

        case expr_and:
            fprintf(dot_file, "%u[label=\"and\"];\n", expr->_node_index);

            print_expr(dot_file, expr->expr_left);
            fprintf(dot_file, "%u -> %u[label=\"expr_left\"];\n", expr->_node_index, expr->expr_left->_node_index);

            print_expr(dot_file, expr->expr_right);
            fprintf(dot_file, "%u -> %u[label=\"expr_right\"];\n", expr->_node_index, expr->expr_right->_node_index);
            break;

        case expr_or:
            fprintf(dot_file, "%u[label=\"or\"];\n", expr->_node_index);

            print_expr(dot_file, expr->expr_left);
            fprintf(dot_file, "%u -> %u[label=\"expr_left\"];\n", expr->_node_index, expr->expr_left->_node_index);

            print_expr(dot_file, expr->expr_right);
            fprintf(dot_file, "%u -> %u[label=\"expr_right\"];\n", expr->_node_index, expr->expr_right->_node_index);
            break;

        case expr_xor:
            fprintf(dot_file, "%u[label=\"xor\"];\n", expr->_node_index);

            print_expr(dot_file, expr->expr_left);
            fprintf(dot_file, "%u -> %u[label=\"expr_left\"];\n", expr->_node_index, expr->expr_left->_node_index);

            print_expr(dot_file, expr->expr_right);
            fprintf(dot_file, "%u -> %u[label=\"expr_right\"];\n", expr->_node_index, expr->expr_right->_node_index);
            break;

        case expr_not:
            fprintf(dot_file, "%u[label=\"not\"];\n", expr->_node_index);

            print_expr(dot_file, expr->expr_right);
            fprintf(dot_file, "%u -> %u;\n", expr->_node_index, expr->expr_right->_node_index);
            break;
    }
}
