#pragma once

#include <cstdint>
#include <iostream>
#include "file.h"
#include "InputClassFileStream.h"

namespace ClassFile::ConstantInfo {
	enum ConstantType: uint8_t {
		CONSTANT_Unknown = 0,
		CONSTANT_Blank = 0,
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
	};

	struct ConstantClassInfo: public ConstantInfo {
		uint16_t name_index;

		ConstantClassInfo(InputClassFileStream& is) {
			is.read(name_index);
		}
	};

	// ref Info
	struct ConstantRefInfo : public ConstantInfo {
		uint16_t class_index;
		uint16_t name_and_type_index;
		
		ConstantRefInfo(InputClassFileStream& is) {
			is.read(class_index);
			is.read(name_and_type_index);
		}
	};

	struct ConstantFieldrefInfo : public ConstantRefInfo {
		using ConstantRefInfo::ConstantRefInfo;
	};

	struct ConstantMethodrefInfo : public ConstantRefInfo {
		using ConstantRefInfo::ConstantRefInfo;
	};

	struct ConstantInterfaceMethodrefInfo : public ConstantRefInfo {
		using ConstantRefInfo::ConstantRefInfo;
	};

	// value info
	struct ConstantIntegerInfo: public ConstantInfo {
		uint32_t bytes;

		ConstantIntegerInfo(InputClassFileStream& is) {
			is.read(bytes);
		}
	};

	struct ConstantFloatInfo: public ConstantInfo {
		uint32_t bytes;
		
		ConstantFloatInfo(InputClassFileStream& is) {
			is.read(bytes);
		}
	};

	struct ConstantLongInfo: public ConstantInfo {
		uint32_t high_bytes;
		uint32_t low_bytes;

		ConstantLongInfo(InputClassFileStream& is) {
			is.read(high_bytes);
			is.read(low_bytes);
		}
	};

	struct ConstantDoubleInfo: public ConstantInfo {
		uint32_t high_bytes;
		uint32_t low_bytes;

		ConstantDoubleInfo(InputClassFileStream& is) {
			is.read(high_bytes);
			is.read(low_bytes);
		}
	};

	struct ConstantStringInfo: public ConstantInfo {
		uint16_t string_index;

		ConstantStringInfo(InputClassFileStream& is) {
			is.read(string_index);
		}
	};

	struct ConstantUtf8Info : public ConstantInfo {
		uint16_t length;
		std::unique_ptr<std::byte[]> bytes;

		ConstantUtf8Info(InputClassFileStream& is) {
			is.read(length);
			bytes = std::make_unique<std::byte[]>(length);
			is.read_bytes(bytes.get(), length);
		}
	};
	
	struct ConstantNameAndTypeInfo: public ConstantInfo {
		uint16_t name_index;
		uint16_t descriptor_index;	

		ConstantNameAndTypeInfo(InputClassFileStream& is) {
			is.read(name_index);
			is.read(descriptor_index);
		}
	};

	struct ConstantMethodHandleInfo: public ConstantInfo {
		uint8_t reference_kind;
		uint16_t reference_index;

		ConstantMethodHandleInfo(InputClassFileStream& is) {
			is.read(reference_kind);
			is.read(reference_index);
		}
	};

	struct ConstantMethodTypeInfo: public ConstantInfo {
		uint16_t descriptor_index;

		ConstantMethodTypeInfo(InputClassFileStream& is) {
			is.read(descriptor_index);
		}
	};

	struct ConstantInvokeDynamicInfo: public ConstantInfo {
		uint16_t booststrap_method_attr_index;
		uint16_t name_and_type_index;

		ConstantInvokeDynamicInfo(InputClassFileStream& is) {
			is.read(booststrap_method_attr_index);
			is.read(name_and_type_index);
		}
	};

	std::unique_ptr<ConstantInfo> create_constant_info(const ConstantType tag, InputClassFileStream& is);

	struct Constant {
		ConstantType tag{ CONSTANT_Blank };
		std::unique_ptr<ConstantInfo> info = nullptr;

		Constant() {}
		Constant(InputClassFileStream& is) {
			is.read(tag);
			info = create_constant_info(tag, is);
		}
	};

}
