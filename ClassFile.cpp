#include "ClassFile.h"
/*
const union {
	char BYTES[4];
	uint32_t NUMBER;
} ClassFile::CLASS_FILE_MAGIC{ { 0xCA, 0xFE, 0xBA, 0xBE } };
*/



inline void ClassFile::ClassFile::read(const fs::path& path) {
	is.open(path);
	read();
}

void ClassFile::ClassFile::read_constant_pool() {
	is.read(constant_pool_count);
	constant_pool.reserve(constant_pool_count);
	constant_pool.emplace_back();
	for (decltype(constant_pool_count) i = 1; i < constant_pool_count; ++i) {
		constant_pool.emplace_back(is);
		auto& bck = constant_pool.back();
		if (bck.tag == ConstantInfo::ConstantType::CONSTANT_Long
			|| bck.tag == ConstantInfo::ConstantType::CONSTANT_Double) {
			constant_pool.emplace_back();
			++i;
		}
	}
}

void ClassFile::ClassFile::read_and_check_magic() {
	is.read(magic);
	if (magic == MAGIC_NUMBER) {
		return;
	} else {
		throw std::runtime_error("Magic number check fails.");
	}
}

void ClassFile::ClassFile::read_and_check_version() {
	is.read(minor_version);
	is.read(major_version);

	if (major_version < 45) {
		throw std::runtime_error("Major version is too low");
	}

	switch (major_version) {
	case 46:
	case 47:
	case 48:
	case 49:
	case 50:
	case 51:
	case 52:
		if (minor_version == 0) {
			return;
		}

	}
}
