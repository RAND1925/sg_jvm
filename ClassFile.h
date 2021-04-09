#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include <type_traits>

#include "util.h"
#include "file.h"
#include "InputClassFileStream.h"
#include "ContantPool.h"
#include "AttributeInfo.h"
#include "MethodInfo.h"
#include "FieldInfo.h"

namespace fs = std::filesystem;
namespace ClassFile {
	class ClassFile {
	public:
		const static inline uint32_t MAGIC_NUMBER = 0xCAFEBABE;

		uint32_t magic;
		uint16_t minor_version;
		uint16_t major_version;
		uint16_t constant_pool_count;
		std::vector<ConstantInfo::Constant> constant_pool;
		uint16_t access_flags;
		uint16_t this_class;
		uint16_t super_class;
		uint16_t interfaces_count;
		std::unique_ptr<uint16_t[]> interfaces;
		uint16_t fields_count;
		std::unique_ptr<FieldInfo[]> fields;
		uint16_t methods_count;
		std::unique_ptr<MethodInfo[]> methods;
		uint16_t attributes_count;
		std::unique_ptr<AttributeInfo[]> attributes;

		void read(void) {
			read_and_check_magic();
			read_and_check_version();
			read_constant_pool();
			read_access_flags();
			read_classes();
			read_interfaces();
			read_fields();
			read_methods();
			read_attributes();
			std::cout << "read end" << std::endl;
		}

		void read(const fs::path& path);
		ClassFile(const fs::path& path): is(path) {}
	
	private:
		InputClassFileStream is;
		void read_and_check_magic();
		void read_and_check_version();
		void read_constant_pool();
		void read_access_flags() {
			is.read(access_flags);
		}
		void read_classes() {
			is.read(this_class);
			is.read(super_class);
		}

		void read_interfaces() {
			is.read(interfaces_count);
			interfaces = std::make_unique<uint16_t[]>(interfaces_count);
			for (decltype(interfaces_count) i = 0; i < interfaces_count; ++i) {
				is.read(interfaces[i]);
			}
		}	

		void read_fields() {
			is.read(fields_count);
			fields = std::make_unique<FieldInfo[]>(fields_count);
			for (decltype(fields_count) i = 0; i < fields_count; ++i) {
				new(&(fields[i]))FieldInfo(is);
			}
		}

		void read_methods() {
			is.read(methods_count);
			methods = std::make_unique<MethodInfo[]>(methods_count);
			for (decltype(methods_count) i = 0; i < methods_count; ++i) {
				new(&(methods[i]))MethodInfo(is);
			}
		}

		void read_attributes() {
			is.read(attributes_count);
			attributes = std::make_unique<AttributeInfo[]>(attributes_count);
			for (decltype(attributes_count) i = 0; i < attributes_count; ++i) {
				new(&(attributes[i]))AttributeInfo(is);
			}
		}



		template<typename Size, typename T> 
		void read_table(Size& size, std::unique_ptr<T[]>& table) {
			is.read(size);
			table = std::make_unique<T[]>(table);
			for (auto& t: table) {
				new(&(t))T(is);
			}
		}
	};
}


