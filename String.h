#pragma once

#include <string>

using String = std::string;

#ifdef MUTF_STRING
class MUtf8String {

};

using String  = MUtf8String;
#endif