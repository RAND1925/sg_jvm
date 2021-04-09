#pragma once

#include <cstdint>
#include <memory>

#include "Enums.h"
#include "ClassMemberInfo.h"

namespace ClassFile {
	struct MethodInfo: ClassMemberInfo {
		using ClassMemberInfo::ClassMemberInfo;
	};
}

