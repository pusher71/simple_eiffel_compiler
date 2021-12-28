#ifndef EPROGRAM_H
#define EPROGRAM_H

#include <map>
#include <string>

#include "eclass.h"
#include "../EiffelErrors/semantic_error.h"
#include "../EiffelErrors/compile_error.h"
#include "../../bison/tree_nodes.h"

class EProgram {
    // ================ STATIC ================
public:
    static EProgram* current;
    static std::vector<SemanticError>   semanticErrors;
    static std::vector<CompileError>    compileErrors;

    static EUserClass* mainClass;
    static std::string eiffelMainFunctionName();
    static std::string javaMainFunctionName();
    static std::string javaMainFunctionDescriptor();

    static std::string javaDefaultConstructorName();
    static std::string javaDefaultConstructorDescriptor();

    // ============== ATTRIBUTES ==============
private:
    std::map<std::string, std::shared_ptr<EClass>> _classes;

    // ============== OPERATIONS ==============
    // -------- creating --------
public:
    EProgram();
    EProgram(const program_strct* programNode, const std::string& mainClassName);

    // ------- attributes -------
public:
    EClass* getClassBy(const std::string& className);
    std::vector<EClass*> classes() const;

    // -------- contract --------
private:
    void runSemanticStage_0(const program_strct* programNode);
    void runSemanticStage_1();
    void runSemanticStage_2();
    void runSemanticStage_3(const std::string& mainClassName);
    void runSemanticStage_4();

public:
    bool compileToJVM(const std::string& mainClassName, const std::string& compilerExeFilePath);
};

#endif // EPROGRAM_H
