#pragma once
#include <vector>

#include "Enums.h"
#include "String.h"

#include "ClassFile.h"

namespace Runtime {
	struct ConstantPoolIndex {
		uint16_t index;
	};
	class StringIndex : ConstantPoolIndex {

	};

	class Class;
	class ConstantPool;
	class ClassMemberInfo {
	public:
		AccessType access_type;
		StringIndex name;
		StringIndex descriptor;
		std::weak_ptr<Class> cls;

		ClassMemberInfo() {}
	};

	class Field : public ClassMemberInfo {

	};

	class Method : public ClassMemberInfo {
	public:
		size_t operand_stack_capacity;
		size_t local_variable_table_capacity;
		std::unique_ptr<uint8_t[]> code;
	};

	class Constant{
	};

	class ConstantInt {

	};


	
	class SymbolReference {
		StringIndex class_name;
		StringIndex descriptor;
		std::weak_ptr<Class> cls;
	};


	class ConstantPool {
		//	std::vector<std::unqiue_ptr<Constant>> constants;
	};


	class Attribute{};
	class Code: Attribute{};
	
	class Class {
	public:
		AccessType access_flags;
		std::unique_ptr<Field[]> fields;
		std::unique_ptr<Method[]> methods;
		//std::unique_ptr<Attribute[]> methods;

		Class(const ClassFile::ClassFile& class_file)
		: access_flags(AccessType(class_file.access_flags)) {
			
		}

	};


	template<typename T>
	using AutoIncreasingArray = std::vector<T>;
	class MethodArea {
	public:
		AutoIncreasingArray<Class> clses;
		AutoIncreasingArray<Method> methods;
		AutoIncreasingArray<Method> codes;


	};
	
}