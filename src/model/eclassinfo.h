#ifndef ECLASSINFO_H
#define ECLASSINFO_H

#include <vector>

#include "efield.h"
#include "emethod.h"

class EClassInfo {
    // ============== ATTRIBUTES ==============
private
    std::string                 _name;

    std::vector<EField*>        _fields;
    std::vector<EMethod*>       _methods;

    std::vector<EClassInfo*>    _parents;
    std::vector<std::pair<std::string, std::string>>    _rename_seq;
    std::vector<std::string>                            _redefine_seq;
    std::vector<std::string>                            _select_seq;

    // ============== OPERATIONS ==============
    // -------- creating --------
public:
    EClassInfo();

    // ------- attributes -------
public:
    std::string name();
    std::vector<EField*> fields();
    std::vector<EMethod*> methods();

    // -------- contract --------

};

#endif // ECLASSINFO_H
