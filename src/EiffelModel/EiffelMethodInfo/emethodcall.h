#ifndef EMETHODCALL_H
#define EMETHODCALL_H

#include "emethod.h"
#include "../EiffelCore/eclass.h"

class EMethodCall
{
public:
    EMethodCall();

    EMethod* findMethodByCall(EClass* classInfo);
};

#endif // EMETHODCALL_H
