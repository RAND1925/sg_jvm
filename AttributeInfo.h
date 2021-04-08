#pragma once

#include <cstdint>
#include <memory>

#include "InputClassFileStream.h"

namespace ClassFile {
	struct AttributeInfo {
		uint16_t attribute_name_index = 0;
		uint32_t attribute_length = 0;
		std::unique_ptr<uint8_t[]> info = nullptr; 

		AttributeInfo() {}
		AttributeInfo(InputClassFileStream& is) {
			is.read(attribute_name_index);
			is.read(attribute_length);
			info = std::make_unique<uint8_t[]>(attribute_length);
			is.read_bytes(info.get(), attribute_length);
		}
	};
}

