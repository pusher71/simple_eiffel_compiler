#include <iostream>
#include <cstdio>

extern "C" {
    int yylex();
}

extern FILE* yyin;

int main(int argc, char** argv) {
    const char* filepath = argv[1];
    yyin = fopen(filepath, "r");

    if (yyin != NULL) {
        std::cout << "<<< Start FLEX" << std::endl << std::endl;
        yylex();
        std::cout << std::endl << "<<< End FLEX" << std::endl;

        fclose(yyin);
    }
    else {
        std::cerr << "INPUT ERROR :: Failed to read source file at: \"" << filepath << "\"." << std::endl;
        std::cerr << "            :: Executable filepath: \"" << argv[0] << "\"." << std::endl;
    }

    return 0;
}
