#ifndef ECLASSINFO_H
#define ECLASSINFO_H

#include <vector>
#include <map>
#include <string>

#include "efeature.h"
#include "../../bison/tree_nodes.h"

class EClass {
    // ============== ATTRIBUTES ==============
private:
    struct EParentInfo {
        std::string parentName;

        std::vector<std::pair<std::string, std::string>>    renameSeq;
        std::vector<std::string>                            redefineSeq;
        std::vector<std::string>                            selectSeq;
    };

    std::string                         _name;
    EType*                              _type;

    std::vector<EParentInfo>            _parents;
    std::vector<std::string>            _creators;
    std::map<std::string, EFeature*>    _features;

    // ============== OPERATIONS ==============
    // -------- creating --------
public:
    static EClass* create(class_decl_strct* classNode);

    // ------- attributes -------
public:
    EType* getType();

    // -------- contract --------
public:
    void compile();
};

#endif // ECLASSINFO_H
