#include "eclassrtl.h"

#include <fstream>
#include <filesystem>

EClassRTL::EClassRTL() {}

std::string EClassRTL::javaPackageName() const { return EClass::rtlClassPackageName(); }
