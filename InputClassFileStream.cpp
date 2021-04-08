#include "InputClassFileStream.h"

inline void ClassFile::InputClassFileStream::open(const std::filesystem::path& path) {
	class_file.open(path.c_str(), std::ios::binary);
}
