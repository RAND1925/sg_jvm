#pragma once

#include "Enums.h"
#include "String.h"

#include "ClassFile.h"

namespace Runtime {
	class MethodArea {};

	class Class;
	class ConstantPool;
	class ClassMember {
	public:
		AccessType access_type;
		String name;
		String descriptor;
		std::weak_ptr<Class> cls;

		ClassMember() {}
	};

	class Field : public ClassMember {

	};

	class Method : public ClassMember {
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
		std::weak_ptr<ConstantPool> constant_pool;
		String class_name;
		std::weak_ptr<Class> cls;
	};


	class ConstantPool {
		//	std::vector<std::unqiue_ptr<Constant>> constants;
	};
	class Class {
	public:
		std::unique_ptr<Field[]> fields;
		std::unique_ptr<Method[]> methods;

		Class(ClassFile::ClassFile class_file){}

	};


	
}