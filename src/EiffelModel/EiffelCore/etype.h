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

    static EType noType();
    static EType voidLiterType();
    static EType boolType(bool isClass = false);
    static EType intType(bool isClass = false);
    static EType charType(bool isClass = false);
    static EType stringType(bool isClass = false);
    static EType classType(const std::string& classTypeName);

    // ----------------- contract -----------------
public:
    bool isUserDefinedSubtypeValid(std::string& outputInvalidUserTypeName) const;
    bool isClass() const;

    std::string descriptor() const;
    bool isExpanded() const;

    type_strct* getRawTypeCopy() const;

    // ---------------- comparison ----------------
public:
    bool operator==(const EType& other) const;
    bool operator!=(const EType& other) const;

    bool canCastTo(const EType& other) const;

    // ---------------- additional ----------------
public:
    std::string toString() const;
    std::string firstElemClassName() const;
};

#endif // EDATATYPE_H
