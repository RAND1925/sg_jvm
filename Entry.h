#pragma once

#include <string>
#include <fstream>
#include <filesystem>
#include <memory>

#include "boost/algorithm/string.hpp"

#include "file.h"

namespace fs = std::filesystem;

class Entry {
public:
	operator std::wstring() {
		return L"";
	};
	const static inline std::wstring pathListSeparator = L";";

    virtual void read_class(std::wstring);
	Entry(const std::wstring&);
	Entry();
};


class DirEntry : public Entry {
public:
	DirEntry(const fs::path& path)
		: path(path), relative_path(path.relative_path()) {}

	DirEntry(const std::wstring& source)
		: DirEntry(fs::path(source)) {}

	operator std::wstring() {
		return relative_path;
	}

	std::string read_class(std::wstring& class_name) {
		fs::path full_path = path / class_name;
		std::wstring p = full_path.relative_path();
		return read_file(p);
	}

private:
	fs::path path;
	std::wstring relative_path;
};


class ZipEntry : public Entry {
public:
	ZipEntry(const std::wstring& source)
		: path(source), relative_path(path.relative_path()) {}
	
private:
	fs::path path;
	std::wstring relative_path;
};

class CompositeEntry : public Entry {
public:
	CompositeEntry(const std::wstring& source)
		: CompositeEntry(fs::path(source)) {
	//	boost::split(paths, source, this->pathListSeparator, boost::token_compress_on);
//		for (auto p : paths) {
	//		//EntryFactory::create(p);
	//	}
	}

	CompositeEntry(const fs::path& path)
		: path(path), relative_path(path.relative_path()) {}
private:
	fs::path path;
	std::wstring relative_path;
	std::vector<std::wstring> paths;
};


class EntryFactory {
	static std::shared_ptr<Entry> create(const std::wstring& source) {

		if (source.find(Entry::pathListSeparator) != std::wstring::npos) {
			return std::make_shared<CompositeEntry>(source);
		}

		fs::path path(source);
		if (!path.has_filename()) {
			return std::make_shared<DirEntry>(path);
		
		}
		auto filename = path.filename();
		if (filename == "*") {
			return {};
			//return std::make_shared<WildcardEntry>(path);

		}

		auto extension = path.extension();

		if (extension == ".zip" || extension == ".jar") {
			return std::make_shared<ZipEntry>(path);
		}
		throw;
	}
};

