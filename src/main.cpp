#include <iostream>
#include <cstdio>

extern "C" {
    int yylex();
    int yyparse();

    void print_program(FILE* dot_file, struct program_strct* program);
}

extern FILE* yyin;
extern struct program_strct* tree_root;

int main(int argc, char** argv) {
    if (argc != 2) {
            std::cerr << "INPUT ERROR :: No source file have been provided." << std::endl;
            return -1;
        }

    bool print_syntaxtree = true;

    // Parse input file if it can be opened
    const char* filepath = argv[1];
    yyin = fopen(filepath, "r");

    if (yyin != NULL) {
        yyparse();
        fclose(yyin);
    }
    else {
        std::cerr << "INPUT ERROR :: Failed to read source file at: \"" << filepath << "\"." << std::endl;
        std::cerr << "            :: Executable filepath: \"" << argv[0] << "\"." << std::endl;
    }

    // Print result tree
    if (print_syntaxtree) {
        if (tree_root != NULL) {
            FILE* output_file = fopen("output_tree.dot", "w");
            print_program(output_file, tree_root);

            fclose(output_file);
        }
        else {
            std::cerr << "FAILED TO PARSE INPUT FILE" << std::endl;
        }
    }

    return 0;
}
