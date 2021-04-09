#pragma once

#include <cstdint>
#include <memory>

#include "Enums.h"
#include "ClassMemberInfo.h"

namespace ClassFile {
	struct FieldInfo : public ClassMemberInfo {
		using ClassMemberInfo::ClassMemberInfo;
	};
}

