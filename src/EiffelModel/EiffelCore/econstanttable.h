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
    };

    enum JvmConstantType {
        jvm_invalid,
        jvm_utf8,
        jvm_string,
        jvm_class,
        jvm_nameAndType,
        jvm_fieldRef,
        jvm_methodRef
    };

    // ============== ATTRIBUTES ==============
private:
    std::vector<std::pair<JvmConstantType, JvmConstant>> _constants;

    // ============== OPERATIONS ==============
    // -------- contract --------
public:
    std::pair<JvmConstantType, JvmConstant> getConstant(int constantIndex);

    void appendUtf8(const std::string& stringUtf8);
    void appendString(short utf8Link_string);
    void appendConstClass(short utf8Link_string);
    void appendNameAndType(const std::pair<short, short>& utf8Links_nameAndType);
    void appendFieldRef(const std::pair<short, short>& utf8Links_fieldRef);
    void appendMethodRef(const std::pair<short, short>& utf8Links_methodRef);
};

#endif // ECONSTANTTABLE_H
