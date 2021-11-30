#ifndef EPROGRAM_H
#define EPROGRAM_H

#include <map>
#include <string>

#include "eclass.h"
#include "../EiffelErrors/semantic_error.h"
#include "../../bison/tree_nodes.h"

class EProgram {
    // ================ STATIC ================
public:
    static EProgram* current;
    static std::vector<SemanticError> semanticErrors;

    // ============== ATTRIBUTES ==============
private:
    std::map<std::string, EClass*> _classes;

    // ============== OPERATIONS ==============
    // -------- creating --------
public:
    EProgram();
    static EProgram* create(const program_strct* program_node);

    // ------- attributes -------
public:
    EClass* getClassBy(const std::string& className);

    // -------- contract --------
private:
    void runSemanticStage_0(const program_strct* programNode);
    void runSemanticStage_1();
    void runSemanticStage_2();

public:
    bool compileToJVM(const std::string& jvmFilepath);
};

#endif // EPROGRAM_H
