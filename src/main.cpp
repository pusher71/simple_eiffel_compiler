#include <iostream>
#include <cstdio>

#include "EiffelModel/EiffelCore/eprogram.h"

extern "C" {
    int yylex();
    int yyparse();

    void print_program(FILE* dot_file, struct program_strct* program);
}

extern "C" FILE* yyin;
extern "C" struct program_strct* tree_root;

struct CompilerState {
    bool isPrintingTreeNodes = false;
};

struct CompilerInfo {
    char* sourceFilepath;
};

int main(int argc, char** argv) {
    CompilerState compilerState;
    compilerState.isPrintingTreeNodes = true;

    if (argc != 2) {
        std::cerr << "INPUT ERROR :: No source file have been provided." << std::endl;
        return -1;
    }

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
    if (compilerState.isPrintingTreeNodes) {
        if (tree_root != NULL) {
            FILE* output_file = fopen("output_tree.dot", "w");
            print_program(output_file, tree_root);

            fclose(output_file);
        }
        else {
            std::cerr << "FAILED TO PARSE INPUT FILE" << std::endl;
        }
    }

    // Perform semantic
    EProgram eiffelProgram;

    if (tree_root != NULL) {
        eiffelProgram = EProgram(tree_root);
    }

    for (const auto& error : EProgram::semanticErrors) {
        std::cerr << error.errorReason() << std::endl;
    }

    // Perform compilation
    if (EProgram::semanticErrors.empty()) {
        eiffelProgram.compileToJVM("out");
        int a = 3;
    }

    return 0;
}
