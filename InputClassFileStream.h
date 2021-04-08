#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>

#include "file.h"

namespace ClassFile {
	class InputClassFileStream {
	public:
		template <typename T>
		void read(T& value) {
			read_big_endian(class_file, value);
		}

		template <typename T>
		void read_bytes(T* const ptr, size_t size) {
			class_file.read(reinterpret_cast<char*>(ptr), size);
		}

		explicit InputClassFileStream(const std::filesystem::path& path): class_file(path.string(), std::ios::binary) {
		}

		void open(const std::filesystem::path& path);

	private:
		std::ifstream class_file;

	};
}

