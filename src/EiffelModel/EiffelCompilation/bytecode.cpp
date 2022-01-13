#include "bytecode.h"
#include "../EiffelCore/eclass.h"
#include "../EiffelCore/EiffelClasses/RTLclasses/eclassconsoleio.h"
#include "../EiffelCore/eprogram.h"

#include <iostream>

ByteCode::ByteCode() {}

ByteCode::ByteCode(const EUserClass& userClass) {
    // Main bytecode values
    this->_appendFourBytes(0xCAFEBABE);     // "Magic" java constant
    this->_appendTwoBytes(0x0000);          // Minor version of java
    this->_appendTwoBytes(0x0037);          // Major version of java

    // Bytecode of constant table
    ByteCode constantTableByteCode(userClass._constants);
    this->_append(constantTableByteCode);

    // Self class info
    this->_appendTwoBytes(0x0001);          // Access flags (0x0001 - PUBLIC class)
    this->_appendTwoBytes(userClass._constants.searchClassConstBy(userClass.fullName())); // Link to self constant class in constant table
    this->_appendTwoBytes(userClass._constants.searchClassConstBy(EClass::javaObjectFullName())); // Link to parent constantn class in constant table (java.lang.Object is parent)
    this->_appendTwoBytes(0x0000);          // Count of interfaces which class implements

    // Fields info
    const auto& userClassAttributesMetaInfo = userClass.attributesMetaInfo();
    this->_appendTwoBytes(userClassAttributesMetaInfo.size());

    for (const auto& attributeMetaInfo : userClassAttributesMetaInfo) {
        this->_append(ByteCode::attributesMetaByteCode(userClass._constants, *attributeMetaInfo));
    }

    // Methods info
    const auto& userClassRoutinesMetaInfo = userClass.routinesMetaInfo();
    this->_appendTwoBytes(1 + userClassRoutinesMetaInfo.size() + userClass._featuresTable.size() + userClass.isMainClass());

    // ... Compile default constructor to bytecode
    this->_append(ByteCode::defaultConstructorByteCode(userClass._constants, userClass));

    // ... Compile methods to bytecode
    for (const auto& routineMetaInfo : userClassRoutinesMetaInfo) {
        this->_append(ByteCode::routinesMetaByteCode(userClass._constants, *routineMetaInfo));
    }

    // ... Compile polymethods to bytecode
    for (const auto& featureMetaInfo : userClass._featuresTable) {
        this->_append(ByteCode::polyMethodByteCode(userClass._constants, featureMetaInfo));
    }

    // ... Compile main function to bytecode if user class is the main class
    if (userClass.isMainClass()) {
        this->_append(ByteCode::mainFunctionByteCode(userClass._constants, userClass));
    }

    // Class attributes info
    this->_appendTwoBytes(0x0000); // Class attributes count
}

ByteCode::ByteCode(const EConstantTable& classConstantTable) {
    this->_appendTwoBytes(classConstantTable.size()+1);

    for (const auto& jvmConstantInfo : classConstantTable.constants()) {
        this->_appendByte(jvmConstantInfo.second.type());

        std::string stringValue;
        std::vector<char> stringBytes;

        int64_t longValue;

        switch (jvmConstantInfo.second.type()) {
            case JvmConstant::jvm_utf8:
                this->_appendTwoBytes(jvmConstantInfo.second.utf8_value().size());

                stringValue = jvmConstantInfo.second.utf8_value();
                stringBytes = std::vector<char>(stringValue.begin(), stringValue.end());
                for (char stringByte : stringBytes) {
                    this->_appendByte(stringByte);
                }
                break;

            case JvmConstant::jvm_integer:
                this->_appendFourBytes(jvmConstantInfo.second.integer_value());
                break;

            case JvmConstant::jvm_long:
                longValue = jvmConstantInfo.second.long_value();

                this->_appendFourBytes( *((int32_t*)&longValue + 1) );
                this->_appendFourBytes( *((int32_t*)&longValue + 0) );

                break;

            case JvmConstant::jvm_string:
                this->_appendTwoBytes(jvmConstantInfo.second.string_value());
                break;

            case JvmConstant::jvm_class:
                this->_appendTwoBytes(jvmConstantInfo.second.class_value());
                break;

            case JvmConstant::jvm_nameAndType:
                this->_appendTwoBytes(jvmConstantInfo.second.nameAndType_value().first);
                this->_appendTwoBytes(jvmConstantInfo.second.nameAndType_value().second);
                break;

            case JvmConstant::jvm_fieldRef:
                this->_appendTwoBytes(jvmConstantInfo.second.fieldRef_value().first);
                this->_appendTwoBytes(jvmConstantInfo.second.fieldRef_value().second);
                break;

            case JvmConstant::jvm_methodRef:
                this->_appendTwoBytes(jvmConstantInfo.second.methodRef_value().first);
                this->_appendTwoBytes(jvmConstantInfo.second.methodRef_value().second);
                break;

            default:
                break;
        }
    }
}

ByteCode ByteCode::attributesMetaByteCode(const EConstantTable& userClassConstants, const EFeatureMetaInfo& featureMetaInfo) {
    ByteCode result;
    result._appendTwoBytes(0x0001);
    result._appendTwoBytes(featureMetaInfo.featureName_utf8Link());
    result._appendTwoBytes(featureMetaInfo.featureDescriptor_utf8Link());
    result._appendTwoBytes(0x0000);

    return result;
}

ByteCode ByteCode::routinesMetaByteCode(const EConstantTable& userClassConstants, const EFeatureMetaInfo& featureMetaInfo) {
    ERoutine* classRoutine = (ERoutine*)featureMetaInfo.implementation();

    ByteCode result;
    result._appendTwoBytes(0x0001);
    result._appendTwoBytes(featureMetaInfo.featureName_utf8Link());
    result._appendTwoBytes(featureMetaInfo.featureDescriptor_utf8Link());
    result._appendTwoBytes(0x0001);

    // "Code" attribute of method
    ByteCode codeAttribute;
    codeAttribute._appendTwoBytes(0x1000);
    codeAttribute._appendTwoBytes((short)classRoutine->_formalParameters.size() + (short)classRoutine->_localVariables.size() + 1);

    ByteCode routineBodyCode(userClassConstants, classRoutine, classRoutine->_instrInfo, classRoutine->_exprInfo);

    codeAttribute._appendFourBytes((unsigned long)routineBodyCode._bytes.size());
    codeAttribute._append(routineBodyCode);
    codeAttribute._appendFourBytes(0x00000000);

    result._appendTwoBytes(0x0001);
    result._appendFourBytes((unsigned long)codeAttribute._bytes.size());
    result._append(codeAttribute);

    return result;
}

ByteCode ByteCode::mainFunctionByteCode(const EConstantTable& userClassConstants, const EUserClass& mainClass) {
    ByteCode result;
    result._appendTwoBytes(0x0009);
    result._appendTwoBytes(userClassConstants.searchUTF8By(EProgram::javaMainFunctionName()));
    result._appendTwoBytes(userClassConstants.searchUTF8By(EProgram::javaMainFunctionDescriptor()));
    result._appendTwoBytes(0x0001);

    // "Code" attribute of method
    ByteCode codeAttribute;
    codeAttribute._appendTwoBytes(0x1000);
    codeAttribute._appendTwoBytes(0x02);

    // Create main class
    ByteCode routineBodyCode;

    routineBodyCode._append(ByteCode::new_(userClassConstants.searchClassConstBy(mainClass.fullName())));
    routineBodyCode._append(ByteCode::dup());
    routineBodyCode._append(ByteCode::invokespecial(userClassConstants.searchMethodRefBy(mainClass.fullName(), EProgram::javaDefaultConstructorName(), EProgram::javaDefaultConstructorDescriptor()), 0));
    routineBodyCode._append(ByteCode::astore(0x01));

    // Run main method of main class
    routineBodyCode._append(ByteCode::aload(0x01));
    routineBodyCode._append(ByteCode::invokevirtual(userClassConstants.searchMethodRefBy(mainClass.fullName(), EProgram::eiffelMainFunctionName(), EProgram::javaDefaultConstructorDescriptor()), 0));

    routineBodyCode._append(ByteCode::_return());

    codeAttribute._appendFourBytes((unsigned long)routineBodyCode._bytes.size());
    codeAttribute._append(routineBodyCode);
    codeAttribute._appendFourBytes(0x00000000);

    result._appendTwoBytes(0x0001);
    result._appendFourBytes((unsigned long)codeAttribute._bytes.size());
    result._append(codeAttribute);

    return result;
}

ByteCode ByteCode::polyMethodByteCode(const EConstantTable& userClassConstants, const EFeatureMetaInfo& featureMetaInfo) {
    ByteCode result;

    result._appendTwoBytes(0x0009);
    result._appendTwoBytes(featureMetaInfo.polyMethodName_utf8Link());
    result._appendTwoBytes(featureMetaInfo.polyMethodDescriptor_utf8Link());
    result._appendTwoBytes(0x0001);

    // "Code" attribute of method
    ByteCode codeAttribute;
    codeAttribute._appendTwoBytes(0x1000);

    short formalParamsCount = 0;
    if (featureMetaInfo.implementation()->featureType() == EFeature::efeature_routine) {
        formalParamsCount = ((ERoutine*)featureMetaInfo.implementation())->_formalParameters.size();
    }

    codeAttribute._appendTwoBytes(1 + formalParamsCount);

    ByteCode featureMetaInfoBodyCode;

    for (const auto& polymorphicFeatureInfo : featureMetaInfo.polyMethodImplementations()) {
        featureMetaInfoBodyCode._append(ByteCode::aload(0x0));
        featureMetaInfoBodyCode._append(ByteCode::instanceof(polymorphicFeatureInfo.first));

        ByteCode ifBlock;
        if (!polymorphicFeatureInfo.second.isExceptionThrow()) {
            ifBlock._append(ByteCode::aload(0x0));
            for (short i=0; i<formalParamsCount; i++) {
                ifBlock._append(ByteCode::aload(i+1));
            }

            ifBlock._append((polymorphicFeatureInfo.second.featureType() == EFeature::efeature_attribute
                             ? ByteCode::getfield(polymorphicFeatureInfo.second.fieldOrMethodRef_constLink())
                             : ByteCode::invokevirtual(polymorphicFeatureInfo.second.fieldOrMethodRef_constLink(), formalParamsCount)));

            switch (featureMetaInfo.returnType()) {
                case EFeatureMetaInfo::ereturntype_void:    ifBlock._append(ByteCode::_return()); break;
                case EFeatureMetaInfo::ereturntype_integer: ifBlock._append(ByteCode::ireturn()); break;
                case EFeatureMetaInfo::ereturntype_object:  ifBlock._append(ByteCode::areturn()); break;
            }
        }
        else {
            ifBlock._append(ByteCode::new_(polymorphicFeatureInfo.second.exceptionClass_constLink()));
            ifBlock._append(ByteCode::dup());
            ifBlock._append(ByteCode::ldc_w(polymorphicFeatureInfo.second.exceptionString_constLink()));
            ifBlock._append(ByteCode::invokespecial(polymorphicFeatureInfo.second.exceptionMethodRef_constLink(), 0));
            ifBlock._append(ByteCode::athrow());
            ifBlock._append(ByteCode::pop());
            ifBlock._append(ByteCode::_return());
        }

        featureMetaInfoBodyCode._append(ByteCode::ifeq(0x03 + ifBlock._bytes.size()));
        featureMetaInfoBodyCode._append(ifBlock);
    }

    switch (featureMetaInfo.returnType()) {
        case EFeatureMetaInfo::ereturntype_void:
            featureMetaInfoBodyCode._append(ByteCode::_return());
            break;
        case EFeatureMetaInfo::ereturntype_integer:
            featureMetaInfoBodyCode._append(ByteCode::iconst(0));
            featureMetaInfoBodyCode._append(ByteCode::ireturn());
            break;
        case EFeatureMetaInfo::ereturntype_object:
            featureMetaInfoBodyCode._append(ByteCode::const_null());
            featureMetaInfoBodyCode._append(ByteCode::areturn());
            break;
    }

    codeAttribute._appendFourBytes((unsigned long)featureMetaInfoBodyCode._bytes.size());
    codeAttribute._append(featureMetaInfoBodyCode);
    codeAttribute._appendFourBytes(0x00000000);

    result._appendTwoBytes(0x0001);
    result._appendFourBytes((unsigned long)codeAttribute._bytes.size());
    result._append(codeAttribute);

    return result;
}

ByteCode ByteCode::defaultConstructorByteCode(const EConstantTable& userClassConstants, const EUserClass& userClass) {
    ByteCode result;
    result._appendTwoBytes(0x0001);
    result._appendTwoBytes(userClassConstants.searchUTF8By(EProgram::javaDefaultConstructorName()));
    result._appendTwoBytes(userClassConstants.searchUTF8By(EProgram::javaDefaultConstructorDescriptor()));
    result._appendTwoBytes(0x0001);

    // "Code" attribute of method
    ByteCode codeAttribute;
    codeAttribute._appendTwoBytes(0x1000);
    codeAttribute._appendTwoBytes(0x01);

    ByteCode routineBodyCode;
    // Call this.super
    routineBodyCode._append(ByteCode::aload(0x0));
    routineBodyCode._append(ByteCode::invokespecial(userClassConstants.searchMethodRefBy(EClass::javaObjectFullName(), EProgram::javaDefaultConstructorName(), EProgram::javaDefaultConstructorDescriptor() ), 0));

    // Initialize all IO variables and attributes that has default initialization
    for (const auto& attributeMetaInfo : userClass.attributesMetaInfo()) {
        std::string attributeTypeFirstClassName = attributeMetaInfo->implementation()->returnType().firstElemClassName();
        std::string attributeTypeFirstClassFullName = EProgram::current->getClassBy( attributeTypeFirstClassName )->fullName();

        std::string attributeDescriptor;
        if (attributeMetaInfo->implementation()->returnType().hasDefaultInitialization()) {
            attributeDescriptor= attributeMetaInfo->implementation()->descriptor();
        }
        else if (attributeTypeFirstClassName == EClassCONSOLEIO::classRTLname()) {
            attributeDescriptor = "L" + attributeTypeFirstClassFullName + ";";
        }

        if (!attributeDescriptor.empty()) {
            routineBodyCode._append(ByteCode::aload(0x0));
            routineBodyCode._append(ByteCode::new_(userClassConstants.searchClassConstBy(attributeTypeFirstClassFullName)));
            routineBodyCode._append(ByteCode::dup());
            routineBodyCode._append(ByteCode::invokespecial(userClassConstants.searchMethodRefBy(attributeTypeFirstClassFullName, "<init>", "()V"), 0));
            short fieldRef = userClassConstants.searchFieldRefBy(userClass.fullName(), attributeMetaInfo->finalName(), attributeDescriptor);
            routineBodyCode._append(ByteCode::putfield(fieldRef));
        }
    }

    routineBodyCode._append(ByteCode::_return());

    codeAttribute._appendFourBytes((unsigned long)routineBodyCode._bytes.size());
    codeAttribute._append(routineBodyCode);
    codeAttribute._appendFourBytes(0x00000000);

    result._appendTwoBytes(0x0001);
    result._appendFourBytes((unsigned long)codeAttribute._bytes.size());
    result._append(codeAttribute);

    return result;
}

ByteCode::ByteCode(const EConstantTable&                                                userClassConstants,
                   const ERoutine*                                                      routineInfo,
                   const std::map<const instruction_strct*, ERoutine::InstructionInfo>& instructionInfo,
                   const std::map<const expr_strct*, ERoutine::ExpressionInfo>&         expressionInfo)
{
    // Initialize local variables for its usage
    for (const auto& localVarInfo : routineInfo->_localVariables) {
        if (localVarInfo.second.type().hasDefaultInitialization()) {
            std::string localVarTypeClassName = localVarInfo.second.type().firstElemClassName();
            EClass* localVarTypeClassInfo = EProgram::current->getClassBy(localVarInfo.second.type().firstElemClassName());

            this->_append(ByteCode::new_(userClassConstants.searchClassConstBy(localVarTypeClassInfo->fullName())));
            this->_append(ByteCode::dup());
            this->_append(ByteCode::invokespecial(userClassConstants.searchMethodRefBy(localVarTypeClassInfo->fullName(), "<init>", "()V"), 0));
            this->_append(ByteCode::astore(localVarInfo.second.index()));
        }
    }

    // Compile routine body
    const instruction_seq_strct* instructionSeqElem = routineInfo->_routineBody->next;

    while (instructionSeqElem != NULL) {
        this->_append(ByteCode(userClassConstants, instructionSeqElem->value, instructionInfo, expressionInfo));
        instructionSeqElem = instructionSeqElem->next;
    }

    // Add return command in the end of the routine
    if (routineInfo->returnType() == EType::noType()) {
        this->_append(ByteCode::_return());
    }
    else {
        this->_append(ByteCode::aload(routineInfo->_localVariables.at("RESULT").index()));
        this->_append(ByteCode::areturn());
    }
}

ByteCode::ByteCode(const EConstantTable&                                                    userClassConstants,
                   const instruction_strct*                                                 instruction,
                   const std::map<const instruction_strct*, ERoutine::InstructionInfo>&     instructionInfo,
                   const std::map<const expr_strct*, ERoutine::ExpressionInfo>&             expressionInfo)
{
    switch (instruction->type) {
        case instruction_create:
            this->_append(ByteCode::createInstructionByteCode(userClassConstants, instruction, instructionInfo, expressionInfo));
            break;
        case instruction_assign:
            this->_append(ByteCode::assignInstructionByteCode(userClassConstants, instruction, instructionInfo, expressionInfo));
            break;
        case instruction_if:
            this->_append(ByteCode::ifInstructionByteCode(userClassConstants, instruction, instructionInfo, expressionInfo));
            break;
        case instruction_loop:
            this->_append(ByteCode::loopInstructionByteCode(userClassConstants, instruction, instructionInfo, expressionInfo));
            break;
        case instruction_expr:
            this->_append(ByteCode(userClassConstants, instruction->instruction_as_expr, expressionInfo));
            break;
    }
}

ByteCode ByteCode::createInstructionByteCode(const EConstantTable&                                                  userClassConstants,
                                             const instruction_strct*                                               createInstruction,
                                             const std::map<const instruction_strct*, ERoutine::InstructionInfo>&   instructionInfo,
                                             const std::map<const expr_strct*, ERoutine::ExpressionInfo>&           expressionInfo)
{
    ByteCode result;
    // Push "this"
    if (instructionInfo.at(createInstruction).fieldRef_constLink != 0) {
        result._append(ByteCode::aload(0x0));
    }

    // Create object with given type
    result._append(ByteCode::new_(instructionInfo.at(createInstruction).constClass_constLink));
    result._append(ByteCode::dup());
    result._append(ByteCode::invokespecial(userClassConstants.searchMethodRefBy(instructionInfo.at(createInstruction).ownerClassFullName, "<init>", "()V"), 0));

    // Call "creator" routine
    if (instructionInfo.at(createInstruction).creatorMethodRef_constLink != 0) {
        result._append(ByteCode::dup());

        int16_t argumentsCount = 0;
        result._append(ByteCode::argumentsByteCode(userClassConstants, createInstruction->argument_seq, expressionInfo, argumentsCount));

        result._append(ByteCode::invokevirtual(instructionInfo.at(createInstruction).creatorMethodRef_constLink, argumentsCount));
    }

    // Store created object
    if (instructionInfo.at(createInstruction).fieldRef_constLink != 0)  { result._append(ByteCode::putfield( instructionInfo.at(createInstruction).fieldRef_constLink )); }
    else if (instructionInfo.at(createInstruction).localVarNumber != 0) { result._append(ByteCode::astore( instructionInfo.at(createInstruction).localVarNumber )); }

    return result;
}

ByteCode ByteCode::assignInstructionByteCode(const EConstantTable&                                                  userClassConstants,
                                             const instruction_strct*                                               assignInstruction,
                                             const std::map<const instruction_strct*, ERoutine::InstructionInfo>&   instructionInfo,
                                             const std::map<const expr_strct*, ERoutine::ExpressionInfo>&           expressionInfo)
{
    ByteCode result;
    // Push "this" if assignment is performed for a field
    if (instructionInfo.at(assignInstruction).fieldRef_constLink != 0) {
        result._append(ByteCode::aload(0x0));
    }

    // Push expression
    if (instructionInfo.at(assignInstruction).creatorMethodRef_constLink != 0) {
        result._append(ByteCode::new_(instructionInfo.at(assignInstruction).constClass_constLink));
        result._append(ByteCode::dup());
        result._append(ByteCode::dup());
        result._append(ByteCode::invokespecial(instructionInfo.at(assignInstruction).creatorMethodRef_constLink, 0));
    }

    result._append(ByteCode(userClassConstants, assignInstruction->assign_expr, expressionInfo));

    if (instructionInfo.at(assignInstruction).creatorMethodRef_constLink != 0) {
        result._append(ByteCode::invokevirtual(instructionInfo.at(assignInstruction).methodRef_constLink, 0));
    }

    // Store expression in field or local variable
    if (instructionInfo.at(assignInstruction).fieldRef_constLink != 0) {
        result._append(ByteCode::putfield(instructionInfo.at(assignInstruction).fieldRef_constLink));
    }
    else if (instructionInfo.at(assignInstruction).localVarNumber != 0) {
        result._append(ByteCode::astore(instructionInfo.at(assignInstruction).localVarNumber));
    }

    return result;
}

ByteCode ByteCode::ifInstructionByteCode(const EConstantTable&                                                  userClassConstants,
                                         const instruction_strct*                                               ifInstruction,
                                         const std::map<const instruction_strct*, ERoutine::InstructionInfo>&   instructionInfo,
                                         const std::map<const expr_strct*, ERoutine::ExpressionInfo>&           expressionInfo)
{
    ByteCode result;
    result._append(ByteCode(userClassConstants, ifInstruction->condition, expressionInfo));

    if (expressionInfo.at(ifInstruction->condition).getterConstClass_constLink != 0) {
        result._append(ByteCode::checkcast(expressionInfo.at(ifInstruction->condition).getterConstClass_constLink));
        result._append(ByteCode::invokevirtual(expressionInfo.at(ifInstruction->condition).getterMethodRef_constLink, 0));
    }

    ByteCode branchTrue;
    const instruction_seq_strct* branchTrueInstructionSeqElem = ifInstruction->branch_true->next;
    while (branchTrueInstructionSeqElem != NULL) {
        branchTrue._append(ByteCode(userClassConstants, branchTrueInstructionSeqElem->value, instructionInfo, expressionInfo));
        branchTrueInstructionSeqElem = branchTrueInstructionSeqElem->next;
    }

    ByteCode branchFalse;
    if (ifInstruction->branch_false != NULL) {
        const instruction_seq_strct* branchFalseInstructionSeqElem = ifInstruction->branch_false->next;
        while (branchFalseInstructionSeqElem != NULL) {
            branchFalse._append(ByteCode(userClassConstants, branchFalseInstructionSeqElem->value, instructionInfo, expressionInfo));
            branchFalseInstructionSeqElem = branchFalseInstructionSeqElem->next;
        }
    }

    branchTrue._append(ByteCode::goto_(0x03 + branchFalse._bytes.size()));

    result._append(ByteCode::ifeq(0x03 + branchTrue._bytes.size()));
    result._append(branchTrue);
    result._append(branchFalse);

    return result;
}

ByteCode ByteCode::loopInstructionByteCode(const EConstantTable&                                                userClassConstants,
                                         const instruction_strct*                                               loopInstruction,
                                         const std::map<const instruction_strct*, ERoutine::InstructionInfo>&   instructionInfo,
                                         const std::map<const expr_strct*, ERoutine::ExpressionInfo>&           expressionInfo)
{
    ByteCode result;

    // Generate bytecode of loop init block
    const instruction_seq_strct* loopInitInstructionSeqElem = loopInstruction->init->next;
    while (loopInitInstructionSeqElem != NULL) {
        result._append(ByteCode(userClassConstants, loopInitInstructionSeqElem->value, instructionInfo, expressionInfo));
        loopInitInstructionSeqElem = loopInitInstructionSeqElem->next;
    }

    // Generate bytecode of expression in loop condition
    ByteCode condition;
    condition._append(ByteCode(userClassConstants, loopInstruction->condition, expressionInfo));

    if (expressionInfo.at(loopInstruction->condition).getterConstClass_constLink != 0) {
        condition._append(ByteCode::checkcast(expressionInfo.at(loopInstruction->condition).getterConstClass_constLink));
        condition._append(ByteCode::invokevirtual(expressionInfo.at(loopInstruction->condition).getterMethodRef_constLink, 0));
    }

    // Generate bytecode of loop body block
    ByteCode loopBody;
    const instruction_seq_strct* loopBodyInstructionSeqElem = loopInstruction->body->next;
    while (loopBodyInstructionSeqElem != NULL) {
        loopBody._append(ByteCode(userClassConstants, loopBodyInstructionSeqElem->value, instructionInfo, expressionInfo));
        loopBodyInstructionSeqElem = loopBodyInstructionSeqElem->next;
    }

    loopBody._append(ByteCode::goto_(-(condition._bytes.size() + 0x03 + loopBody._bytes.size())));

    result._append(condition);
    result._append(ByteCode::ifne(0x03 + loopBody._bytes.size()));
    result._append(loopBody);

    return result;
}

ByteCode::ByteCode(const EConstantTable& userClassConstants, const expr_strct* expression, const std::map<const expr_strct*, ERoutine::ExpressionInfo>& expressionInfo) {
    switch(expression->type) {
        case expr_liter_bool:
        case expr_liter_int:
        case expr_liter_char:
        case expr_liter_str:
        case expr_liter_void:           this->_append(ByteCode::literExprByteCode(userClassConstants, expression, expressionInfo)); break;

        case expr_current:              this->_append(ByteCode::currentExprByteCode(userClassConstants, expression, expressionInfo)); break;
        case expr_call_selffeature:     this->_append(ByteCode::exprCallSelffeatureByteCode(userClassConstants, expression, expressionInfo)); break;
        case expr_call_precursor:       this->_append(ByteCode::exprCallSelffeatureByteCode(userClassConstants, expression, expressionInfo)); break;
        case expr_subcall:              this->_append(ByteCode::exprCallSubcallByteCode(userClassConstants, expression, expressionInfo)); break;
        case expr_create:               this->_append(ByteCode::createExprByteCode(userClassConstants, expression, expressionInfo)); break;

        case expr_arrelem:              this->_append(ByteCode::arrElemExprByteCode(userClassConstants, expression, expressionInfo)); break;

        case expr_plus:
        case expr_bminus:
        case expr_mul:
        case expr_idiv:                 this->_append(ByteCode::binArithmExprByteCode(userClassConstants, expression, expressionInfo)); break;
        case expr_uminus:               this->_append(ByteCode::unArithmExprByteCode(userClassConstants, expression, expressionInfo)); break;

        case expr_less:
        case expr_great:
        case expr_less_equal:
        case expr_great_equal:          this->_append(ByteCode::compareExprByteCode(userClassConstants, expression, expressionInfo)); break;
        case expr_equal:
        case expr_notequal:             this->_append(ByteCode::equalityCompareExprByteCode(userClassConstants, expression, expressionInfo)); break;

        case expr_and:                  this->_append(ByteCode::logicAndExprByteCode(userClassConstants, expression, expressionInfo)); break;
        case expr_or:                   this->_append(ByteCode::logicOrExprByteCode(userClassConstants, expression, expressionInfo)); break;
        case expr_xor:                  this->_append(ByteCode::logicXorExprByteCode(userClassConstants, expression, expressionInfo)); break;
        case expr_not:                  this->_append(ByteCode::logicNotExprByteCode(userClassConstants, expression, expressionInfo)); break;
    }
}

ByteCode ByteCode::literExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression, const std::map<const expr_strct*, ERoutine::ExpressionInfo>& expressionInfo) {
    ByteCode result;
    int16_t shortIntLiteral = 0;
    int32_t intLiteral = 0;

    switch(expression->type) {
        case expr_liter_bool:
            result._append(ByteCode::iconst(expression->liter_bool));
            break;
        case expr_liter_int:
            shortIntLiteral = expression->liter_int;
            intLiteral      = expression->liter_int;

            if (expression->liter_int == shortIntLiteral) {
                result._append(ByteCode::sipush(shortIntLiteral));
                result._append(ByteCode::i2l());
            }
            else if (expression->liter_int == intLiteral) {
                result._append(ByteCode::ldc_w(expressionInfo.at(expression).liter_constLink));
                result._append(ByteCode::i2l());
            }
            else {
                result._append(ByteCode::ldc2_w(expressionInfo.at(expression).liter_constLink));
            }

            break;
        case expr_liter_char:
            result._append(ByteCode::bipush(expression->liter_char));
            break;
        case expr_liter_str:
            result._append(ByteCode::ldc_w(expressionInfo.at(expression).liter_constLink));
            break;
        case expr_liter_void:
            result._append(ByteCode::const_null());
            break;

        default: break;
    }

    return result;
}

ByteCode ByteCode::currentExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression, const std::map<const expr_strct*, ERoutine::ExpressionInfo>& expressionInfo) {
    ByteCode result;
    result._append(ByteCode::aload(0x0));

    return result;
}

ByteCode ByteCode::exprCallSelffeatureByteCode(const EConstantTable& userClassConstants, const expr_strct* expression, const std::map<const expr_strct*, ERoutine::ExpressionInfo>& expressionInfo) {
    ByteCode result;
    if (expressionInfo.at(expression).innerVarNumber == 0) {
        result._append(ByteCode::aload(0x0));
    }

    int16_t argumentsCount = 0;
    result._append(ByteCode::argumentsByteCode(userClassConstants, expression->argument_seq, expressionInfo, argumentsCount));

    if (expressionInfo.at(expression).fieldRef_constLink != 0)          { result._append(ByteCode::getfield(expressionInfo.at(expression).fieldRef_constLink)); }
    else if (expressionInfo.at(expression).methodRef_constLink != 0)    { result._append(ByteCode::invokevirtual(expressionInfo.at(expression).methodRef_constLink, argumentsCount)); }
    else if (expressionInfo.at(expression).innerVarNumber != 0)         { result._append(ByteCode::aload(expressionInfo.at(expression).innerVarNumber)); }

    return result;
}

ByteCode ByteCode::exprCallSubcallByteCode(const EConstantTable& userClassConstants, const expr_strct* expression, const std::map<const expr_strct*, ERoutine::ExpressionInfo>& expressionInfo) {
    ByteCode result;
    result._append(ByteCode(userClassConstants, expression->expr_left, expressionInfo));

    int16_t argumentsCount = 0;
    result._append(ByteCode::argumentsByteCode(userClassConstants, expression->argument_seq, expressionInfo, argumentsCount));

    if (expressionInfo.at(expression).fieldRef_constLink != 0) { result._append(ByteCode::getfield(expressionInfo.at(expression).fieldRef_constLink)); }
    else if (expressionInfo.at(expression).methodRef_constLink != 0) {
        if (expressionInfo.at(expression).isRTLcall)    { result._append(ByteCode::invokevirtual(expressionInfo.at(expression).methodRef_constLink, argumentsCount)); }
        else                                            { result._append(ByteCode::invokestatic(expressionInfo.at(expression).methodRef_constLink, argumentsCount+1)); }
    }

    return result;
}

ByteCode ByteCode::createExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression, const std::map<const expr_strct*, ERoutine::ExpressionInfo>& expressionInfo) {
    ByteCode result;
    // Create object with given type
    result._append(ByteCode::new_(expressionInfo.at(expression).constClass_constLink));
    result._append(ByteCode::dup());
    result._append(ByteCode::invokespecial(userClassConstants.searchMethodRefBy(expressionInfo.at(expression).ownerClassFullName, "<init>", "()V"), 0));

    // Call "creator" routine
    if (expressionInfo.at(expression).methodRef_constLink != 0) {
        result._append(ByteCode::dup());

        int16_t argumentsCount = 0;
        result._append(ByteCode::argumentsByteCode(userClassConstants, expression->argument_seq, expressionInfo, argumentsCount));

        result._append(ByteCode::invokevirtual(expressionInfo.at(expression).methodRef_constLink, argumentsCount));
    }

    result._append(ByteCode::checkcast(expressionInfo.at(expression).constClass_constLink));

    return result;
}

ByteCode ByteCode::argumentsByteCode(const EConstantTable& userClassConstants, const argument_seq_strct* argumentsSeq, const std::map<const expr_strct*, ERoutine::ExpressionInfo>& expressionInfo, int16_t& argumentsCount) {
    ByteCode result;

    argumentsCount = 0;
    const argument_seq_strct* argumentSeqElem = argumentsSeq;
    while (argumentSeqElem != NULL) {
        if (expressionInfo.at(argumentSeqElem->value).setterConstClass_constLink != 0) {
            result._append(ByteCode::new_(expressionInfo.at(argumentSeqElem->value).setterConstClass_constLink));
            result._append(ByteCode::dup());
            result._append(ByteCode::dup());
            result._append(ByteCode::invokespecial(expressionInfo.at(argumentSeqElem->value).methodRef_constLink, 0));
        }

        result._append(ByteCode(userClassConstants, argumentSeqElem->value, expressionInfo));

        if (expressionInfo.at(argumentSeqElem->value).setterConstClass_constLink != 0) {
            result._append(ByteCode::invokevirtual(expressionInfo.at(argumentSeqElem->value).setterMethodRef_constLink, 0));
        }
        else if (expressionInfo.at(argumentSeqElem->value).getterConstClass_constLink != 0) {
            result._append(ByteCode::checkcast(expressionInfo.at(argumentSeqElem->value).getterConstClass_constLink));
            result._append(ByteCode::invokevirtual(expressionInfo.at(argumentSeqElem->value).getterMethodRef_constLink, 0));
        }

        argumentsCount++;
        argumentSeqElem = argumentSeqElem->next;
    }

    return result;
}

ByteCode ByteCode::arrElemExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression, const std::map<const expr_strct*, ERoutine::ExpressionInfo>& expressionInfo) {
    ByteCode result;
    result._append(ByteCode(userClassConstants, expression->expr_left, expressionInfo));

    result._append(ByteCode(userClassConstants, expression->expr_right, expressionInfo));
    if (expressionInfo.at(expression->expr_right).getterConstClass_constLink != 0) {
        result._append(ByteCode::checkcast(expressionInfo.at(expression->expr_right).getterConstClass_constLink));
        result._append(ByteCode::invokevirtual(expressionInfo.at(expression->expr_right).getterMethodRef_constLink, 0));
    }

    result._append(ByteCode::invokevirtual(expressionInfo.at(expression).methodRef_constLink, 1));

    return result;
}

ByteCode ByteCode::binArithmExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression, const std::map<const expr_strct*, ERoutine::ExpressionInfo>& expressionInfo) {
    ByteCode result;

    result._append(ByteCode(userClassConstants, expression->expr_left, expressionInfo));
    if (expressionInfo.at(expression->expr_left).getterConstClass_constLink != 0) {
        result._append(ByteCode::checkcast(expressionInfo.at(expression->expr_left).getterConstClass_constLink));
        result._append(ByteCode::invokevirtual(expressionInfo.at(expression->expr_left).getterMethodRef_constLink, 0));
    }

    result._append(ByteCode(userClassConstants, expression->expr_right, expressionInfo));
    if (expressionInfo.at(expression->expr_right).getterConstClass_constLink != 0) {
        result._append(ByteCode::checkcast(expressionInfo.at(expression->expr_right).getterConstClass_constLink));
        result._append(ByteCode::invokevirtual(expressionInfo.at(expression->expr_right).getterMethodRef_constLink, 0));
    }

    switch (expression->type) {
        case expr_plus:     result._append(ByteCode::ladd()); break;
        case expr_bminus:   result._append(ByteCode::lsub()); break;
        case expr_mul:      result._append(ByteCode::lmul()); break;
        case expr_idiv:     result._append(ByteCode::ldiv()); break;

        default: break;
    }

    return result;
}

ByteCode ByteCode::unArithmExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression, const std::map<const expr_strct*, ERoutine::ExpressionInfo>& expressionInfo) {
    ByteCode result;

    result._append(ByteCode(userClassConstants, expression->expr_right, expressionInfo));
    if (expressionInfo.at(expression->expr_right).getterConstClass_constLink != 0) {
        result._append(ByteCode::checkcast(expressionInfo.at(expression->expr_right).getterConstClass_constLink));
        result._append(ByteCode::invokevirtual(expressionInfo.at(expression->expr_right).getterMethodRef_constLink, 0));
    }

    result._append(ByteCode::lneg());

    return result;
}

ByteCode ByteCode::compareExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression, const std::map<const expr_strct*, ERoutine::ExpressionInfo>& expressionInfo) {
    ByteCode result;

    result._append(ByteCode(userClassConstants, expression->expr_left, expressionInfo));
    if (expressionInfo.at(expression->expr_left).getterConstClass_constLink != 0) {
        result._append(ByteCode::checkcast(expressionInfo.at(expression->expr_left).getterConstClass_constLink));
        result._append(ByteCode::invokevirtual(expressionInfo.at(expression->expr_left).getterMethodRef_constLink, 0));
    }
    if (expressionInfo.at(expression->expr_left).resultType.isType(dtype_character)) {
        result._append(ByteCode::i2l());
    }

    result._append(ByteCode(userClassConstants, expression->expr_right, expressionInfo));
    if (expressionInfo.at(expression->expr_right).getterConstClass_constLink != 0) {
        result._append(ByteCode::checkcast(expressionInfo.at(expression->expr_right).getterConstClass_constLink));
        result._append(ByteCode::invokevirtual(expressionInfo.at(expression->expr_right).getterMethodRef_constLink, 0));
    }
    if (expressionInfo.at(expression->expr_right).resultType.isType(dtype_character)) {
        result._append(ByteCode::i2l());
    }

    result._append(ByteCode::lcmp());

    ByteCode cmpBlock;

    cmpBlock._append(ByteCode::iconst(0x0));
    cmpBlock._append(ByteCode::goto_(0x3 + 0x1));

    switch (expression->type) {
        case expr_great:        result._append(ByteCode::ifgt(0x3 + cmpBlock._bytes.size())); break;
        case expr_great_equal:  result._append(ByteCode::ifge(0x3 + cmpBlock._bytes.size())); break;
        case expr_less:         result._append(ByteCode::iflt(0x3 + cmpBlock._bytes.size())); break;
        case expr_less_equal:   result._append(ByteCode::ifle(0x3 + cmpBlock._bytes.size())); break;

        default: break;
    }

    result._append(cmpBlock);
    result._append(ByteCode::iconst(0x1));

    return result;
}

ByteCode ByteCode::equalityCompareExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression, const std::map<const expr_strct*, ERoutine::ExpressionInfo>& expressionInfo) {
}

ByteCode ByteCode::logicAndExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression, const std::map<const expr_strct*, ERoutine::ExpressionInfo>& expressionInfo) {
    ByteCode result;

    result._append(ByteCode(userClassConstants, expression->expr_left, expressionInfo));
    if (expressionInfo.at(expression->expr_left).getterConstClass_constLink != 0) {
        result._append(ByteCode::checkcast(expressionInfo.at(expression->expr_left).getterConstClass_constLink));
        result._append(ByteCode::invokevirtual(expressionInfo.at(expression->expr_left).getterMethodRef_constLink, 0));
    }

    ByteCode leftIsTrueLogicBlock;

    ByteCode rightIsTrueLogicBlock;
    rightIsTrueLogicBlock._append(ByteCode::iconst(0x1));
    rightIsTrueLogicBlock._append(ByteCode::goto_(0x3 + 0x1));

    leftIsTrueLogicBlock._append(ByteCode(userClassConstants, expression->expr_right, expressionInfo));
    if (expressionInfo.at(expression->expr_right).getterConstClass_constLink != 0) {
        leftIsTrueLogicBlock._append(ByteCode::checkcast(expressionInfo.at(expression->expr_right).getterConstClass_constLink));
        leftIsTrueLogicBlock._append(ByteCode::invokevirtual(expressionInfo.at(expression->expr_right).getterMethodRef_constLink, 0));
    }

    leftIsTrueLogicBlock._append(ByteCode::ifeq(0x3 + rightIsTrueLogicBlock._bytes.size()));
    leftIsTrueLogicBlock._append(rightIsTrueLogicBlock);

    result._append(ByteCode::ifeq(0x3 + leftIsTrueLogicBlock._bytes.size()));
    result._append(leftIsTrueLogicBlock);
    result._append(ByteCode::iconst(0x0));

    return result;
}

ByteCode ByteCode::logicOrExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression, const std::map<const expr_strct*, ERoutine::ExpressionInfo>& expressionInfo) {
    ByteCode result;

    result._append(ByteCode(userClassConstants, expression->expr_left, expressionInfo));
    if (expressionInfo.at(expression->expr_left).getterConstClass_constLink != 0) {
        result._append(ByteCode::checkcast(expressionInfo.at(expression->expr_left).getterConstClass_constLink));
        result._append(ByteCode::invokevirtual(expressionInfo.at(expression->expr_left).getterMethodRef_constLink, 0));
    }

    ByteCode leftIsFalseLogicBlock;

    ByteCode rightIsFalseLogicBlock;
    rightIsFalseLogicBlock._append(ByteCode::iconst(0x0));
    rightIsFalseLogicBlock._append(ByteCode::goto_(0x3 + 0x1));

    leftIsFalseLogicBlock._append(ByteCode(userClassConstants, expression->expr_right, expressionInfo));
    if (expressionInfo.at(expression->expr_right).getterConstClass_constLink != 0) {
        leftIsFalseLogicBlock._append(ByteCode::checkcast(expressionInfo.at(expression->expr_right).getterConstClass_constLink));
        leftIsFalseLogicBlock._append(ByteCode::invokevirtual(expressionInfo.at(expression->expr_right).getterMethodRef_constLink, 0));
    }

    leftIsFalseLogicBlock._append(ByteCode::ifne(0x3 + rightIsFalseLogicBlock._bytes.size()));
    leftIsFalseLogicBlock._append(rightIsFalseLogicBlock);

    result._append(ByteCode::ifne(0x3 + leftIsFalseLogicBlock._bytes.size()));
    result._append(leftIsFalseLogicBlock);
    result._append(ByteCode::iconst(0x1));

    return result;
}

ByteCode ByteCode::logicXorExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression, const std::map<const expr_strct*, ERoutine::ExpressionInfo>& expressionInfo) {
    ByteCode result;

    result._append(ByteCode(userClassConstants, expression->expr_left, expressionInfo));
    if (expressionInfo.at(expression->expr_left).getterConstClass_constLink != 0) {
        result._append(ByteCode::checkcast(expressionInfo.at(expression->expr_left).getterConstClass_constLink));
        result._append(ByteCode::invokevirtual(expressionInfo.at(expression->expr_left).getterMethodRef_constLink, 0));
    }

    result._append(ByteCode(userClassConstants, expression->expr_right, expressionInfo));
    if (expressionInfo.at(expression->expr_right).getterConstClass_constLink != 0) {
        result._append(ByteCode::checkcast(expressionInfo.at(expression->expr_right).getterConstClass_constLink));
        result._append(ByteCode::invokevirtual(expressionInfo.at(expression->expr_right).getterMethodRef_constLink, 0));
    }

    ByteCode logicBlock;

    logicBlock._append(ByteCode::iconst(0x1));
    logicBlock._append(ByteCode::goto_(0x3 + 0x1));

    result._append(ByteCode::if_icmpeq(0x3 + logicBlock._bytes.size()));

    result._append(logicBlock);
    result._append(ByteCode::iconst(0x0));

    return result;
}

ByteCode ByteCode::logicNotExprByteCode(const EConstantTable& userClassConstants, const expr_strct* expression, const std::map<const expr_strct*, ERoutine::ExpressionInfo>& expressionInfo) {
    ByteCode result;

    result._append(ByteCode(userClassConstants, expression->expr_right, expressionInfo));
    if (expressionInfo.at(expression->expr_right).getterConstClass_constLink != 0) {
        result._append(ByteCode::checkcast(expressionInfo.at(expression->expr_right).getterConstClass_constLink));
        result._append(ByteCode::invokevirtual(expressionInfo.at(expression->expr_right).getterMethodRef_constLink, 0));
    }

    ByteCode logicBlock;

    logicBlock._append(ByteCode::iconst(0x0));
    logicBlock._append(ByteCode::goto_(0x3 + 0x1));

    result._append(ByteCode::ifeq(0x3 + logicBlock._bytes.size()));

    result._append(logicBlock);
    result._append(ByteCode::iconst(0x1));

    return result;
}

ByteCode& ByteCode::_appendByte(unsigned char value) {
    this->_bytes.push_back(value);
    return *this;
}

ByteCode& ByteCode::_appendTwoBytes(unsigned short int value) {
    for (int i=1; i>=0; i--) {
        unsigned char eachByte = *(((char*)(&value)) + i);
        this->_bytes.push_back(eachByte);
    }

    return *this;
}

ByteCode& ByteCode::_appendFourBytes(unsigned long int value) {
    for (int i=3; i>=0; i--) {
        unsigned char eachByte = *(((char*)(&value)) + i);
        this->_bytes.push_back(eachByte);
    }

    return *this;
}

ByteCode& ByteCode::_append(const ByteCode& other) {
    for (char byteValue : other._bytes) {
        this->_bytes.push_back(byteValue);
    }

    return *this;
}

bool ByteCode::writeToFile(std::ofstream& outputClassFile) const {
    if (outputClassFile.is_open()) {
        outputClassFile.clear();

        std::string resultByteCode;
        for (char byte : this->_bytes) { resultByteCode += byte; }

        outputClassFile << resultByteCode;

        return true;
    }
    else {
        return false;
    }
}

ByteCode ByteCode::iconst(signed char i) {
    ByteCode result;

    if ( i < -1 || i > 5) { throw "Invalid parameter for \"iconst\" command (must be an integer in [-1; 5])"; }

    result._appendByte(i+3);
    return result;
}

ByteCode ByteCode::const_null() {
    ByteCode result;
    result._appendByte(0x01);

    return result;
}

ByteCode ByteCode::bipush(char s1) {
    ByteCode result;
    result._appendByte(0x10);
    result._appendByte(s1);

    return result;
}

ByteCode ByteCode::sipush(short int s2) {
    ByteCode result;
    result._appendByte(0x11);
    result._appendTwoBytes(s2);

    return result;
}

ByteCode ByteCode::i2l() {
    ByteCode result;
    result._appendByte(0x85);

    return result;
}

ByteCode ByteCode::ldc(char u1) {
    ByteCode result;
    result._appendByte(0x12);
    result._appendByte(u1);

    return result;
}

ByteCode ByteCode::ldc_w(short int u2) {
    ByteCode result;
    result._appendByte(0x13);
    result._appendTwoBytes(u2);

    return result;
}

ByteCode ByteCode::ldc2_w(short int u2) {
    ByteCode result;
    result._appendByte(0x14);
    result._appendTwoBytes(u2);

    return result;
}

ByteCode ByteCode::iload(char u1) {
    ByteCode result;
    result._appendByte(0x15);
    result._appendByte(u1);

    return result;
}

ByteCode ByteCode::aload(char u1) {
    ByteCode result;
    result._appendByte(0x19);
    result._appendByte(u1);

    return result;
}

ByteCode ByteCode::istore(char u1) {
    ByteCode result;
    result._appendByte(0x36);
    result._appendByte(u1);

    return result;
}

ByteCode ByteCode::astore(char u1) {
    ByteCode result;
    result._appendByte(0x3A);
    result._appendByte(u1);

    return result;
}

ByteCode ByteCode::pop() {
    ByteCode result;
    result._appendByte(0x57);

    return result;
}

ByteCode ByteCode::dup() {
    ByteCode result;
    result._appendByte(0x59);

    return result;
}

ByteCode ByteCode::dup2() {
    ByteCode result;
    result._appendByte(0x5C);

    return result;
}

ByteCode ByteCode::ladd() {
    ByteCode result;
    result._appendByte(0x61);

    return result;
}

ByteCode ByteCode::lmul() {
    ByteCode result;
    result._appendByte(0x69);

    return result;
}

ByteCode ByteCode::lsub() {
    ByteCode result;
    result._appendByte(0x65);

    return result;
}

ByteCode ByteCode::lneg() {
    ByteCode result;
    result._appendByte(0x75);

    return result;
}

ByteCode ByteCode::ldiv() {
    ByteCode result;
    result._appendByte(0x6D);

    return result;
}

ByteCode ByteCode::iinc(char u1, signed char i) {
    ByteCode result;
    result._appendByte(0x84);
    result._appendByte(u1);
    result._appendByte(i);

    return result;
}

ByteCode ByteCode::lcmp() {
    ByteCode result;
    result._appendByte(0x94);

    return result;
}

ByteCode ByteCode::if_icmpeq(short int s2) {
    ByteCode result;
    result._appendByte(0x9F);
    result._appendTwoBytes(s2);

    return result;
}

ByteCode ByteCode::if_icmpne(short int s2) {
    ByteCode result;
    result._appendByte(0xA0);
    result._appendTwoBytes(s2);

    return result;
}

ByteCode ByteCode::if_icmplt(short int s2) {
    ByteCode result;
    result._appendByte(0xA1);
    result._appendTwoBytes(s2);

    return result;
}

ByteCode ByteCode::if_icmpge(short int s2) {
    ByteCode result;
    result._appendByte(0xA2);
    result._appendTwoBytes(s2);

    return result;
}

ByteCode ByteCode::if_icmpgt(short int s2) {
    ByteCode result;
    result._appendByte(0xA3);
    result._appendTwoBytes(s2);

    return result;
}

ByteCode ByteCode::if_icmple(short int s2) {
    ByteCode result;
    result._appendByte(0xA4);
    result._appendTwoBytes(s2);

    return result;
}

ByteCode ByteCode::ifeq(short int s2) {
    ByteCode result;
    result._appendByte(0x99);
    result._appendTwoBytes(s2);

    return result;
}

ByteCode ByteCode::ifne(short int s2) {
    ByteCode result;
    result._appendByte(0x9A);
    result._appendTwoBytes(s2);

    return result;
}

ByteCode ByteCode::iflt(short int s2) {
    ByteCode result;
    result._appendByte(0x9B);
    result._appendTwoBytes(s2);

    return result;
}

ByteCode ByteCode::ifle(short int s2) {
    ByteCode result;
    result._appendByte(0x9E);
    result._appendTwoBytes(s2);

    return result;
}

ByteCode ByteCode::ifgt(short int s2) {
    ByteCode result;
    result._appendByte(0x9D);
    result._appendTwoBytes(s2);

    return result;
}

ByteCode ByteCode::ifge(short int s2) {
    ByteCode result;
    result._appendByte(0x9C);
    result._appendTwoBytes(s2);

    return result;
}

ByteCode ByteCode::if_acmpeq(short int s2) {
    ByteCode result;
    result._appendByte(0xA5);
    result._appendTwoBytes(s2);

    return result;
}

ByteCode ByteCode::if_acmpne(short int s2) {
    ByteCode result;
    result._appendByte(0xA6);
    result._appendTwoBytes(s2);

    return result;
}

ByteCode ByteCode::goto_(short int s2) {
    ByteCode result;
    result._appendByte(0xA7);
    result._appendTwoBytes(s2);

    return result;
}

ByteCode ByteCode::newarray(char u1) {
    ByteCode result;
    result._appendByte(0xBC);
    result._appendByte(u1);

    return result;
}

ByteCode ByteCode::anewarray(short int u2) {
    ByteCode result;
    result._appendByte(0xBD);
    result._appendTwoBytes(u2);

    return result;
}

ByteCode ByteCode::arraylength() {
    ByteCode result;
    result._appendByte(0xBE);

    return result;
}

ByteCode ByteCode::iaload() {
    ByteCode result;
    result._appendByte(0x2E);

    return result;
}

ByteCode ByteCode::aaload() {
    ByteCode result;
    result._appendByte(0x32);

    return result;
}

ByteCode ByteCode::iastore() {
    ByteCode result;
    result._appendByte(0x4F);
    return result;
}

ByteCode ByteCode::aastore() {
    ByteCode result;
    result._appendByte(0x53);
    return result;
}

ByteCode ByteCode::new_(short int u2) {
    ByteCode result;
    result._appendByte(0xBB);
    result._appendTwoBytes(u2);

    return result;
}

ByteCode ByteCode::getfield(short int u2) {
    ByteCode result;
    result._appendByte(0xB4);
    result._appendTwoBytes(u2);

    return result;
}

ByteCode ByteCode::putfield(short int u2) {
    ByteCode result;
    result._appendByte(0xB5);
    result._appendTwoBytes(u2);

    return result;
}

ByteCode ByteCode::instanceof(short int u2) {
    ByteCode result;
    result._appendByte(0xC1);
    result._appendTwoBytes(u2);

    return result;
}

ByteCode ByteCode::checkcast(short int u2) {
    ByteCode result;
    result._appendByte(0xC0);
    result._appendTwoBytes(u2);

    return result;
}

ByteCode ByteCode::athrow() {
    ByteCode result;
    result._appendByte(0xBF);

    return result;
}

ByteCode ByteCode::invokevirtual(short int u2, short int argCount) {
    ByteCode result;
    result._appendByte(0xB6);
    result._appendTwoBytes(u2);

    return result;
}

ByteCode ByteCode::invokespecial(short int u2, short int argCount) {
    ByteCode result;
    result._appendByte(0xB7);
    result._appendTwoBytes(u2);

    return result; }

ByteCode ByteCode::invokestatic(short int u2, short int argCount) {
    ByteCode result;
    result._appendByte(0xB8);
    result._appendTwoBytes(u2);

    return result;
}

ByteCode ByteCode::_return() {
    ByteCode result;
    result._appendByte(0xB1);

    return result;
}

ByteCode ByteCode::ireturn() {
    ByteCode result;
    result._appendByte(0xAC);

    return result;
}

ByteCode ByteCode::lreturn() {
    ByteCode result;
    result._appendByte(0xAD);

    return result;
}

ByteCode ByteCode::areturn() {
    ByteCode result;
    result._appendByte(0xB0);

    return result;
}
