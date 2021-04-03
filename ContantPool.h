#pragma once

#include <cstdint>
#include <iostream>
#include "file.h"

namespace ConstantInfo {
	enum ConstantType: uint8_t {
		CONSTANT_Class = 7,
		CONSTANT_Fieldref = 9,
		CONSTANT_Methodref = 10,
		CONSTANT_InterfaceMethodref = 11,
		CONSTANT_String = 8,
		CONSTANT_Integer = 3,
		CONSTANT_Float = 4,
		CONSTANT_Long = 5,
		CONSTANT_Double = 6,
		CONSTANT_NameAndType = 12,
		CONSTANT_Utf8 = 1,
		CONSTANT_MethodHandle = 15,
		CONSTANT_MethodType = 16,
		CONSTANT_InvokeDynamic = 18
	};

	struct ConstantInfo {
		ConstantType tag{0};
	};

	struct ConstantClassInfo: public ConstantInfo {
		const ConstantType tag{CONSTANT_Class};
		uint16_t name_index;
	};

	struct ConstantFieldrefInfo: public ConstantInfo {
		const ConstantType tag{CONSTANT_Fieldref};
		uint16_t class_index;
		uint16_t name_and_type_index;
	};

	struct ConstantMethodrefInfo: public ConstantInfo {
		const ConstantType tag{ CONSTANT_Methodref };
		uint16_t class_index;
		uint16_t name_and_type_index;
	};
	
	struct ConstantInterfaceMethodrefInfo: public ConstantInfo {
		const ConstantType tag{CONSTANT_InterfaceMethodref};
		uint16_t class_index;
		uint16_t name_and_type_index;
	};

	struct ConstantIntegerInfo: public ConstantInfo {
		const ConstantType tag{ CONSTANT_Integer };
		uint32_t bytes;
	};

	struct ConstantFloatInfo: public ConstantInfo {
		const ConstantType tag{ CONSTANT_Float };
		uint32_t bytes;
	};

	struct ConstantLongInfo: public ConstantInfo {
		const ConstantType tag{ CONSTANT_Long };
		uint32_t high_bytes;
		uint32_t low_bytes;
	};

	struct ConstantDoubleInfo: public ConstantInfo {
		const ConstantType tag{ CONSTANT_Double };
		uint32_t high_bytes;
		uint32_t low_bytes;
	};

	struct ConstantStringInfo: public ConstantInfo {
		const ConstantType tag{ CONSTANT_String };
		uint16_t string_index;
	};

	struct ConstantUtf8Info : public ConstantInfo {
		const ConstantType tag{ CONSTANT_Utf8 };
		uint16_t length;
		std::unique_ptr<uint8_t[]> bytes;
	};
	
	struct ConstantNameAndTypeInfo: public ConstantInfo {
		const ConstantType tag{ CONSTANT_NameAndType };
		uint16_t name_index;
		uint16_t descriptor_index;	
	};

	struct ConstantMethodHandle: public ConstantInfo {
		const ConstantType tag{ CONSTANT_MethodHandle};
		uint8_t reference_kind;
		uint16_t reference_index;
	};

	struct ConstantMethodType: public ConstantInfo {
		const ConstantType tag{ CONSTANT_MethodHandle };
		uint16_t descriptor_index;
	};

	struct ConstantInvokeDynamic: public ConstantInfo {
		const ConstantType tag{ CONSTANT_MethodHandle };
		uint16_t booststrap_method_attr_index;
		uint16_t name_and_type_index;
	};

	std::unique_ptr<ConstantInfo> create_constant_info(std::istream& is);

}
