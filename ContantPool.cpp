#include "ContantPool.h"

namespace ConstantInfo {
	std::unique_ptr<ConstantInfo> create_constant_info(std::istream& is) {
		ConstantType tag;
		read_big_endian(is, tag);
		ConstantInfo subobject{tag};

		uint8_t u8_1;
		uint16_t u16_1;
		uint16_t u16_2;
		uint32_t u32_1;
		uint32_t u32_2;
		switch (tag) {

		case CONSTANT_Class: {
			auto ptr = std::make_unique<ConstantClassInfo>(subobject);
			read_big_endian(is, ptr->name_index);
			return ptr;
		}
		
		default:
		{
			auto ptr = std::make_unique<ConstantClassInfo>(subobject);
			read_big_endian(is, ptr->name_index);
			return ptr;
		}
		
		/*
		

		case CONSTANT_Fieldref: {
			
			read_big_endian(is, u16_1);
			read_big_endian(is, u16_2);
			return std::make_unique<ConstantFieldrefInfo>(tag, u16_1, u16_2);
		}
		case CONSTANT_Methodref:
			read_big_endian(is, u16_1);
			read_big_endian(is, u16_2);
			return std::make_unique<ConstantMethodrefInfo>(tag, u16_1, u16_2);
		
		case CONSTANT_InterfaceMethodref:
			read_big_endian(is, u16_1);
			read_big_endian(is, u16_2);
			return std::make_unique<ConstantInterfaceMethodrefInfo>(tag, u16_1, u16_2);
		
		case CONSTANT_String: 
			read_big_endian(is, u16_1);
			return std::make_unique<ConstantStringInfo>(tag, u16_1);

		case CONSTANT_Integer:
			read_big_endian(is, u32_1);
			return std::make_unique<ConstantIntegerInfo>(tag, u32_1);

		case CONSTANT_Float:
			read_big_endian(is, u32_1);
			return std::make_unique<ConstantFloatInfo>(tag, u32_1);

		case CONSTANT_Long:
			read_big_endian(is, u32_1);
			read_big_endian(is, u32_2);
			return std::make_unique<ConstantLongInfo>(tag, u32_1, u32_2);

		case CONSTANT_Double:
			read_big_endian(is, u32_1);
			read_big_endian(is, u32_2);
			return std::make_unique<ConstantDoubleInfo>(tag, u32_1, u32_2);

		case CONSTANT_NameAndType:
			read_big_endian(is, u16_1);
			read_big_endian(is, u16_2);
			return std::make_unique<ConstantNameAndTypeInfo>(tag, u16_1, u16_2);

		case CONSTANT_MethodHandle:
			read_big_endian(is, u8_1);
			read_big_endian(is, u16_2);
			return std::make_unique<ConstantMethodHandle>(tag, u8_1, u16_1);

		case CONSTANT_MethodType:
			read_big_endian(is, u16_1);
			return std::make_unique<ConstantMethodType>(tag, u16_1);
			
		case CONSTANT_InvokeDynamic:
			read_big_endian(is, u16_1);
			read_big_endian(is, u16_2);
			return std::make_unique<ConstantInvokeDynamic>(tag, u16_1, u16_2);


		case CONSTANT_Utf8:
		{
			read_big_endian(is, u16_1);
			auto ptr = std::make_unique<ConstantUtf8Info>(tag, u16_1, u16_1);
			is.read(reinterpret_cast<char*>(ptr->bytes.get()), u16_1);
			return std::move(ptr);
		}
		default:
			return {};
		}*/
		}
	}
}
