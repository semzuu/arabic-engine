#include <utils.hpp>
#include <string>
#include <iostream>
#include <locale>
#include <codecvt>
#include <Tree.hpp>
#include <MorphEngine.hpp>

// since std::wstring_convert is deprecated,
// std::wcstombs is used instead
// based on this article:
// https://www.geeksforgeeks.org/cpp/convert-wstring-to-string-in-c/
std::wstring utf8_to_wstring(const std::string &s) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    return conv.from_bytes(s);
}
std::string wstring_to_utf8(const std::wstring &w) {
	size_t len = std::wcstombs(nullptr, w.c_str(), 0) + 1;
	char *buf = new char[len];
	std::wcstombs(buf, w.c_str(), len);
	std::string str(buf);
	delete[] buf;
	return str;
}

std::string selectScheme(MorphEngine engine) {
	std::cout << "Available schemes:" << std::endl;
	engine.schemes.show();
	std::string selected;
	std::cout << "Type a scheme > "; std::cin >> selected;
	return selected;
}

void mainMenu() {
	std::cout <<
		"0. Exit\n"
		"1. Validate a word\n"
		"2. Generate a word from root\n"
		"3. Modify schemes\n"
		"4. History\n"
		"Choose an option > ";
}

void generateMenu(std::string root, std::vector<std::string> schemes) {
	// TODO: COME BACK LATER
	std::cout <<
		"root: " << root << "\n" <<
		"schemes: " << schemes[0] << "\n" <<
		"0. Cancel\n"
		"1. Add a scheme\n"
		"2. Remove a scheme\n"
		"3. Generate\n"
		"Choose an option > ";
}

void schemeMenu() {
	std::cout <<
		"0. Cancel\n"
		"1. Add a scheme\n"
		"2. Delete a scheme\n"
		"3. Modify a scheme\n"
		"Choose an option > ";
}

void print(Node *node) {
	if (node) {
		std::cout << node->data.value << "\n";
		for (int i = 0; i < node->data.derivatives.size(); i++) {
			std::cout << node->data.derivatives[i] << "\n";
		}
		print(node->left);
		print(node->right);
	}
}
