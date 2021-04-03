#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include <type_traits>

#include "util.h"
#include "file.h"
#include "ContantPool.h"


namespace fs = std::filesystem;


class ClassFile {
public:

	const static inline uint32_t MAGIC_NUMBER = 0xCAFEBABE;

	uint32_t magic;
	uint16_t minor_version;
	uint16_t major_version;
	uint16_t constant_pool_count;
	// cp_info constant_pool
	//ConstantPool constant_pool;
	uint16_t access_flags;
	uint16_t this_class;
	uint16_t super_class;
	uint16_t interfaces_count;
	// interfaces
	uint16_t fields_count;
	// fields
	uint16_t methods_count;
	// methods
	uint16_t attributes_count;
	// attributes;
	void read(std::istream& is) {
		read_and_check_magic(is);
		read_and_check_version(is);
	}
	std::vector<std::unique_ptr<ConstantInfo::ConstantInfo> > constant_pool;

	void read(const fs::path& path) {
		std::ifstream is{path.c_str(), std::ios::binary};
		read_and_check_magic(is);
		read_and_check_version(is);
		read_constant_pool_count(is);
		read_constant_pool(is);
		
	}

	
private:
	std::istream& read_constant_pool(std::istream& is) {
		constant_pool.reserve(constant_pool_count);
		constant_pool.emplace_back();
		for (decltype(constant_pool_count) i = 1; i < constant_pool_count; ++i) {
			constant_pool.emplace_back(ConstantInfo::create_constant_info(is));
			if ((constant_pool.back()->tag == ConstantInfo::CONSTANT_Long)
				|| (constant_pool.back()->tag == ConstantInfo::CONSTANT_Double)) {
				++i;
			}
		}
		return is;
	}

	std::istream& read_constant_pool_count(std::istream& is) {
		read_big_endian(is, constant_pool_count);
		return is;
	}

	std::istream& read_and_check_magic(std::istream& is) {
		read_big_endian(is, magic);
		if (magic == MAGIC_NUMBER) {
			return is;
		} else {
			throw std::runtime_error("Magic number check fails.");
		}
	}

	std::istream& read_and_check_version(std::istream& is) {
		read_big_endian(is, minor_version);
		read_big_endian(is, major_version);

		switch (major_version) {
			case 45:
				return is;
			case 46:
			case 47:
			case 48:
			case 49:
			case 50:
			case 51:
			case 52:
				if (minor_version == 0)
				return is;
				
		}
		if (major_version < 45) {
			throw std::runtime_error("Major version is too low");
		}
		return is;
	 }
};

