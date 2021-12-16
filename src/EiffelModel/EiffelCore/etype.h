#ifndef EDATATYPE_H
#define EDATATYPE_H

#include <string>
#include "../../bison/tree_nodes.h"

class EType {
    // ================ ATTRIBUTES ================
private:
    type_strct* _type;

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
public:
    EType(type_strct* type);
    EType(const std::string& className);

    static EType voidType();
    static EType boolType();
    static EType intType();
    static EType charType();
    static EType stringType();

    // ----------------- contract -----------------
public:
    bool isUserDefinedSubtypeValid(std::string& outputInvalidUserTypeName) const;

    std::string descriptor() const;
    bool isExpanded() const;

    // ---------------- comparison ----------------
public:
    bool operator==(const EType& other) const;
    bool operator!=(const EType& other) const;

    bool canCastTo(const EType& other) const;

    // ---------------- additional ----------------
public:
    std::string toString() const;
};

#endif // EDATATYPE_H
