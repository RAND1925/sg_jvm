#pragma once

#include <memory>

#include "Enums.h"
#include "InputClassFileStream.h"

namespace ClassFile {
	struct ClassMemberInfo {
		Field::AccessType access_flags;
		uint16_t name_index;
		uint16_t descriptor_index;
		uint16_t attributes_count;
		std::unique_ptr<ClassMemberInfo[]> attributes;

		ClassMemberInfo() {}
		ClassMemberInfo(InputClassFileStream& is) {
			is.read(access_flags);
			is.read(name_index);
			is.read(descriptor_index);
			is.read(attributes_count);
			attributes = std::make_unique<ClassMemberInfo[]>(attributes_count);
			for (uint16_t i = 0; i < attributes_count; ++i) {
				new(&attributes[i]) ClassMemberInfo(is);
			}
		}
	};
}