#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include <algorithm>
#include <filesystem>

#include "EiffelModel/EiffelCore/eprogram.h"

// Lexer and Parser functionality and data
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

std::map<std::string, std::string> extractConfigureParameters(std::ifstream& configureFile);

int main(int argc, char** argv) {
    // Set initial compiler settings
    CompilerState compilerState;
    compilerState.isPrintingTreeNodes = false;

    // ================== READ CONFIGURATION FILE OF EIFFEL ==================
    /*
    if (argc != 2) {
        std::cerr << "INPUT ERROR :: No configure file has been provided." << std::endl;
        return -1;
    }
    */

    // Read configuration file
    // std::ifstream configureFile(argv[1]);
    std::ifstream configureFile("build.econf");
    if (!configureFile.is_open()) {
        std::cerr << "INPUT ERROR :: Failed to open configuration file at: \"" << argv[1] << "\"" << std::endl;
    }

    // Extract configuration parameters
    std::map<std::string, std::string> configureParams = extractConfigureParameters(configureFile);

    // Check that configuration file containts needed configuration parameters
    if (!configureParams.count("SOURCE_FILEPATH")) {
        std::cerr << "INPUT ERROR :: No source file has been provided. Add path to source file in build.econf file (SOURCE_FILEPATH = <...>)." << std::endl;
    }

    if (!configureParams.count("MAIN_CLASS_NAME")) {
        std::cerr << "INPUT ERROR :: Main class is not set. Add name of main class in build.econf file (MAIN_CLASS_NAME = <...>)." << std::endl;
    }

    // ============= EXTRACT SOURCE FILE FROM CONFIGURATION FILE =============
    const char* filepath = configureParams.at("SOURCE_FILEPATH").c_str();
    yyin = fopen(filepath, "r");

    // ========================== PARSE SOURCE FILE ==========================
    if (yyin != NULL) {
        yyparse();
        fclose(yyin);
    }
    else {
        std::cerr << "INPUT ERROR :: Failed to read source file at: \"" << filepath << "\"." << std::endl;
        std::cerr << "               Executable filepath: \"" << argv[0] << "\"." << std::endl;
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

    // ================ START SEMANTIC ANALYSIS OF SOURCE CODE ===============
    // Start semantic analysis of source code
    EProgram eiffelProgram;
    std::string mainClassName = configureParams["MAIN_CLASS_NAME"];

    if (tree_root != NULL) {
        std::transform(mainClassName.begin(), mainClassName.end(), mainClassName.begin(), [](unsigned char chr) { return std::toupper(chr); });

        eiffelProgram = EProgram(tree_root, mainClassName);
    }

    // Print semantic analysis errors
    for (const auto& error : EProgram::semanticErrors) {
        std::cerr << error.errorReason() << std::endl;
    }

    // ========================= COMPILE SOURCE CODE =========================
    // Print compiling errors
    if (tree_root != NULL && EProgram::semanticErrors.empty()) {
        eiffelProgram.compileToJVM(mainClassName, argv[0]);
    }

    // Print compiling errors
    for (const auto& error : EProgram::compileErrors) {
        std::cerr << error.errorReason() << std::endl;
    }

    return 0;
}

std::map<std::string, std::string> extractConfigureParameters(std::ifstream& configureFile) {
    std::map<std::string, std::string> result;

    std::string line;
    while(std::getline(configureFile, line)) {
        line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());

        size_t pos = line.find('=');
        std::string key = line.substr(0, pos);
        line.erase(0, pos + 1);
        std::string value = line.substr(0, line.find('='));

        result[key] = value;
    }

    return result;
}
