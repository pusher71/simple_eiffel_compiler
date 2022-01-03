#ifndef ECONSTANTTABLE_H
#define ECONSTANTTABLE_H

#include <string>
#include <vector>
#include <map>

#include "jvmconstant.h"

class EConstantTable {
    // ============== ATTRIBUTES ==============
private:
    int16_t _nextAvailableIndex;
    std::map<int16_t, JvmConstant> _constants;

    // ============== OPERATIONS ==============
    // -------- creating --------
public:
    EConstantTable();

    // -------- contract --------
public:
    std::map<int16_t, JvmConstant> constants() const;
    int16_t size() const;

    int16_t append(const JvmConstant& jvmConstant);

    int16_t appendConstClass(const std::string& classFullName);
    int16_t appendString(const std::string& stringValue);
    int16_t appendFieldRef(const std::string& classFullName, const std::string& fieldName, const std::string& fieldDescriptor);
    int16_t appendMethodRef(const std::string& classFullName, const std::string& methodName, const std::string& methodDescriptor);

    JvmConstant getConstant(int constantIndex) const;
    int16_t searchUTF8By(const std::string& stringUTF8) const;
    int16_t searchClassConstBy(const std::string& classFullName) const;
    int16_t searchFieldRefBy(const std::string& classFullName, const std::string& fieldName, const std::string& fieldDescriptor) const;
    int16_t searchMethodRefBy(const std::string& classFullName, const std::string& methodName, const std::string& methodDescriptor) const;
};

#endif // ECONSTANTTABLE_H
