// file_list_generator.cpp : Defines the entry point for the application.
//

#include <filesystem>
#include <fstream>
#include <iostream>

namespace {
	auto const ROOT = std::filesystem::path("src/");
	auto files = std::vector<std::string>();
	constexpr auto const MATCH = int{ 0 };

	bool equals(std::string const & source, std::string const & other) {
		return source.compare(other) == MATCH;
	}

	bool isProjectFile(std::filesystem::path const & file) {
		if (equals(file.extension().string(), (".cpp"))) {
			return true;
		}
		else if (equals(file.extension().string(), (".c"))) {
			return true;
		}

		return false;
	}
}

bool scanDirectory(std::filesystem::path path) {
	for (auto & p : std::filesystem::directory_iterator(path)) {
		if (p.is_directory() && !p.is_symlink()) {
			std::cout << "Sub directory: " << p.path().filename().string() << std::endl;

			scanDirectory(p.path());
		}
		else if (p.is_regular_file()) {
			if (isProjectFile(p.path())) {
				std::cout << "File: " << p.path().filename().string() << std::endl;
				files.push_back(p.path().string());
			}
			else {	
				std::cout << "Ignoring file (unrecognized extension): " << p.path().filename().string() << std::endl;
			}
		}
	}
	return true;
}

bool writeOutput() {

	auto os = std::ofstream("file_list.txt");
	if (os.is_open()) {
		for (auto & f : files) {
			std::replace(f.begin(), f.end(), '\\', '/');
			os << f << std::endl;
		}
		os.close();
		std::cout << "Successfully closed output stream file" << std::endl;
	}
	else {
		std::cerr << "Error: couldn't open output stream file" << std::endl;
		return false;
	}

	return true;
}

int main()
{
	if (std::filesystem::is_directory(ROOT)) {
		std::cout << "Scanning directories" << std::endl;
		scanDirectory(ROOT);


		std::cout << "First line: " << files.front() << std::endl;
		if (!files.empty()) {
			auto const SUCCESS = writeOutput();

			if (SUCCESS) {
				std::cout << "Successfully wrote output list file" << std::endl;
			}
			else {
				std::cerr << "Error: failed to write output list file" << std::endl;
			}
		}
	}
	else {
		std::cerr << "Error: root path is not a directory" << std::endl;
	}
	
	std::cout << "Finished program" << std::endl;
	auto i = int{ 0 };
	std::cin >> i;
	return EXIT_SUCCESS;
}
