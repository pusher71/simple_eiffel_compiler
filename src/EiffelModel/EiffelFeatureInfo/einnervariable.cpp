#include "einnervariable.h"

EInnerVariable::EInnerVariable(short index, const EType& type)
    : _index(index),
      _type(type)
{}

short EInnerVariable::index() const { return this->_index; }
EType EInnerVariable::type() const { return this->_type; }
