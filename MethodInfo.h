#pragma once

#include <cstdint>
#include <memory>

#include "Enums.h"
#include "AttributeInfo.h"

namespace ClassFile {
	struct MethodInfo {
		Method::AccessType access_flags;
		uint16_t name_index;
		uint16_t descriptor_index;
		uint16_t attributes_count;
		std::unique_ptr<AttributeInfo[]> attributes;

		MethodInfo(){}
		MethodInfo(InputClassFileStream& is) {
			is.read(access_flags);
			is.read(name_index);
			is.read(descriptor_index);
			is.read(attributes_count);
			attributes = std::make_unique<AttributeInfo[]>(attributes_count);
			for (uint16_t i = 0; i < attributes_count; ++i) {
				new(&attributes[i]) AttributeInfo(is);
			}
		}
	};
}

