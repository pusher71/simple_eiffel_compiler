#ifndef BYTECODE_H
#define BYTECODE_H

#include <vector>
#include <fstream>

#include "../EiffelCore/EiffelClasses/euserclass.h"
#include "../EiffelFeatureInfo/eattribute.h"

class ByteCode {
    // ================ ATTRIBUTES ================
private:
    std::vector<char> _bytes;

    // ================ OPERATIONS ================
    // ----------------- creating -----------------
public:
    ByteCode();
    ByteCode(const EUserClass* userClass);
    ByteCode(const EConstantTable& classConstantTable);
    ByteCode(const EConstantTable& userClassConstants, const EAttribute* classAttribute);
    ByteCode(const EConstantTable& userClassConstants, const ERoutine* classRoutine);
    ByteCode(const EConstantTable& userClassConstants, const instruction_seq_strct* routineBody);

private:
    ByteCode& _appendByte(unsigned char value);
    ByteCode& _appendTwoBytes(unsigned short int value);
    ByteCode& _appendFourBytes(unsigned long int value);
    ByteCode& _append(const ByteCode& other);

    // ----------------- contract -----------------
public:
    bool writeToFile(std::ofstream& outputClassFile) const;
};

#endif // BYTECODE_H
