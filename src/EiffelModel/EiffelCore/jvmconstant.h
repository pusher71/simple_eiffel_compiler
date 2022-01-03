#ifndef JVMCONSTANT_H
#define JVMCONSTANT_H

#include <string>
#include <cstdint>
#include <vector>

class JvmConstant {
    // ============== INNER CLASSES ===========
public:
    enum JvmConstantType {
        jvm_invalid         = -1,
        jvm_utf8            = 1,
        jvm_integer         = 3,
        jvm_long            = 5,
        jvm_string          = 8,
        jvm_class           = 7,
        jvm_nameAndType     = 12,
        jvm_fieldRef        = 9,
        jvm_methodRef       = 10
    };

    // ============== ATTRIBUTES ==============
private:
    JvmConstantType _type;

    std::string                     _utf8_value;
    int32_t                         _integer_value;
    int64_t                         _long_value;
    int16_t                         _string_value;
    int16_t                         _constClass_value;
    std::pair<int16_t, int16_t>     _nameAndType_value;
    std::pair<int16_t, int16_t>     _fieldRef_value;
    std::pair<int16_t, int16_t>     _methodRef_value;

    // ============== OPERATIONS ==============
    // -------- creating --------
public:
    JvmConstant();

private:
    JvmConstant(JvmConstantType type);

public:
    static JvmConstant UTF8(const std::string& utf8_value);
    static JvmConstant Integer(int32_t integer_value);
    static JvmConstant Long(int64_t long_value);
    static JvmConstant String(int16_t string_value);
    static JvmConstant ConstClass(int16_t constClass_value);
    static JvmConstant NameAndType(const std::pair<int16_t, int16_t>& nameAndType_value);
    static JvmConstant FieldRef(const std::pair<int16_t, int16_t>& fieldRef_value);
    static JvmConstant MethodRef(const std::pair<int16_t, int16_t>& methodRef_value);

    // -------- contract --------
public:
    JvmConstantType type() const;

    std::string                     utf8_value() const;
    int32_t                         integer_value() const;
    int64_t                         long_value() const;
    int16_t                         string_value() const;
    int16_t                         class_value() const;
    std::pair<int16_t, int16_t>     nameAndType_value() const;
    std::pair<int16_t, int16_t>     fieldRef_value() const;
    std::pair<int16_t, int16_t>     methodRef_value() const;

    // ------- comparison -------
public:
    bool operator==(const JvmConstant& other) const;
};

#endif // JVMCONSTANT_H
