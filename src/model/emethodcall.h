#ifndef EMETHODCALL_H
#define EMETHODCALL_H

#include "emethod.h"
#include "eclass.h"

class EMethodCall
{
public:
    EMethodCall();

    EMethod* findMethodByCall(EClass* class);
};

#endif // EMETHODCALL_H
