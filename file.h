#pragma once

#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>

#if _HAS_CXX20
	#include <bit>	
	using std::endian;
#else
	enum class endian {
	#ifdef _WIN32
		little = 0,
		big = 1,
		native = little
	#else
		little = __ORDER_LITTLE_ENDIAN__,
		big = __ORDER_BIG_ENDIAN__,
		native = __BYTE_ORDER__
	#endif
	};
#endif 

namespace fs = std::filesystem;

template <typename T, size_t size = sizeof(T)>
inline constexpr void bit_swap(T& val) {
	char* const start = reinterpret_cast<char*>(&val);
	std::reverse(start, start + size);
}

template <typename T>
inline constexpr std::istream& read_big_endian(std::istream& is, T& val) {
	is.read(reinterpret_cast<char*>(&val), sizeof(T));

	if constexpr (endian::native == endian::little) {
		bit_swap(val);
	}
	return is;
}

template <typename T>
inline constexpr std::istream& read_litte_endian(std::istream& is, T& val) {
	is.read(reinterpret_cast<char*>(&val), sizeof(T));

	if constexpr (endian::native == endian::big) {
		bit_swap(val);
	}
	return is;
}

template <typename T>
inline constexpr std::istream& read_specific_size(std::istream& is, T& val, size_t size) {
	is.read(reinterpret_cast<char*>(&val), size);
}

std::string read_file(const fs::path& path);
