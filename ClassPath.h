#pragma once

#include "Cmd.h"
#include "Entry.h"

class Classpath {
public:
	Classpath(const Cmd& cmd) {

	}

	std::string read_class(const std::wstring& class_name) {
		return read_file(get_absolute_path(class_name));
	}

	fs::path get_absolute_path(const std::wstring& class_name) {
		fs::path class_filename{ class_name + L".class" };
		fs::path boot_path{ LR"(D:\projects\sg_jvm\rt\java\lang)" };
		return boot_path / class_filename;
	}

private:
	//Entry bootClassPath;
	//Entry extClassPath;
	//Entry userClassPath;
	fs::path jrePath;

};
