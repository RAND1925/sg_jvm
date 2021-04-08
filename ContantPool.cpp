#include "ContantPool.h"

namespace ClassFile::ConstantInfo {
	std::unique_ptr<ConstantInfo> create_constant_info(ConstantType tag, InputClassFileStream& is) {
		switch (tag) {
		case CONSTANT_Class:
			return std::make_unique<ConstantClassInfo>(is);
		case CONSTANT_Fieldref:
			return std::make_unique<ConstantFieldrefInfo>(is);
		case CONSTANT_Methodref: 
			return std::make_unique<ConstantMethodrefInfo>(is);
		case CONSTANT_InterfaceMethodref: 
			return std::make_unique<ConstantInterfaceMethodrefInfo>(is);
		case CONSTANT_String: 
			return std::make_unique<ConstantStringInfo>(is);
		case CONSTANT_Integer: 
			return std::make_unique<ConstantIntegerInfo>(is);
		case CONSTANT_Float:
			return std::make_unique<ConstantFloatInfo>(is);
		case CONSTANT_Long:
			return std::make_unique<ConstantLongInfo>(is);
		case CONSTANT_Double:
			return std::make_unique<ConstantDoubleInfo>(is);
		case CONSTANT_NameAndType:
			return std::make_unique<ConstantNameAndTypeInfo>(is);
		case CONSTANT_MethodHandle:
			return std::make_unique<ConstantMethodHandleInfo>(is);
		case CONSTANT_MethodType:
			return std::make_unique<ConstantMethodTypeInfo>(is);
		case CONSTANT_InvokeDynamic:
			return std::make_unique<ConstantInvokeDynamicInfo>(is);
		case CONSTANT_Utf8:
			return std::make_unique<ConstantUtf8Info>(is);
		default:
			return nullptr;
		}
	}
}
