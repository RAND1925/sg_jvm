#include "file.h"



std::string read_file(const fs::path& path) {
	std::ifstream f{ path, std::ios::binary };
	if (!f) {
		return "";
	}
	std::string res;
	f.seekg(0, std::ios::end);
	const auto size = f.tellg();
	res.resize(size);
	f.seekg(0, std::ios::beg);
	f.read(&res[0], res.size());
	f.close();
	return res;
}