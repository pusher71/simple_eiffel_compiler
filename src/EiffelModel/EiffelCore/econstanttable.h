#ifndef ECONSTANTTABLE_H
#define ECONSTANTTABLE_H

#include <string>
#include <vector>

class EConstantTable {
    // ============== INNER CLASSES ===========
public:
    union JvmConstant {
        std::string* jvm_utf8 = nullptr;
        short jvm_string;
        short jvm_class;
        std::pair<short, short> jvm_nameAndType;
        std::pair<short, short> jvm_fieldRef;
        std::pair<short, short> jvm_methodRef;

        JvmConstant();

        bool operator==(const JvmConstant& other) const;
    };

    enum JvmConstantType {
        jvm_invalid         = -1,
        jvm_utf8            = 1,
        jvm_string          = 8,
        jvm_class           = 7,
        jvm_nameAndType     = 12,
        jvm_fieldRef        = 9,
        jvm_methodRef       = 10
    };

    // ============== ATTRIBUTES ==============
private:
    std::vector<std::pair<JvmConstantType, JvmConstant>> _constants;

    // ============== OPERATIONS ==============
    // -------- contract --------
public:
    int size() const;

    std::pair<JvmConstantType, JvmConstant> getConstant(int constantIndex) const;
    short searchUtf8By(const std::string& stringUtf8) const;
    short searchClassConstBy(const std::string& classFullName) const;
    short searchFieldRefBy(const std::string& classFullName, const std::string& fieldName, const std::string& fieldDescriptor) const;
    short searchMethodRefBy(const std::string& classFullName, const std::string& methodName, const std::string& methodDescriptor) const;

    short appendUtf8(const std::string& stringUtf8);
    short appendString(short utf8Link_string);
    short appendConstClass(short utf8Link_string);
    short appendNameAndType(const std::pair<short, short>& utf8Links_nameAndType);
    short appendFieldRef(const std::pair<short, short>& utf8Links_fieldRef);
    short appendMethodRef(const std::pair<short, short>& utf8Links_methodRef);

    short appendFieldRefStr(const std::string& classFullName, const std::string& fieldName, const std::string& fieldDescriptor);
    short appendMethodRefStr(const std::string& classFullName, const std::string& methodName, const std::string& methodDescriptor);
};

#endif // ECONSTANTTABLE_H
