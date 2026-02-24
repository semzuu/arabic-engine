#include <iostream>
#include <string>
#include <MorphEngine.hpp>

#include <locale>
#include <codecvt>

std::wstring utf8_to_wstring(const std::string &s) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    return conv.from_bytes(s);
}
std::string wstring_to_utf8(const std::wstring &w) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    return conv.to_bytes(w);
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

void generateMenu() {
	// TODO: COME BACK LATER
	std::cout <<
		"0. Cancel\n"
		"1. Add a scheme\n"
		"2. Generate word from root\n"
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

int main() {
	MorphEngine engine;
	engine.loadSchemesFromFile(DATA_DIR "/schemes.txt");
	bool quit = false;
	int choice = 0;
	while(!quit) {
		mainMenu();
		std::cin >> choice;
		switch(choice) {
			case 0:
				quit = true;
				break;
			case 1: {
				std::string word, root;
				std::cout << "word > "; std::cin >> word;
				std::cout << "root > "; std::cin >> root;
				if (engine.validateWord(utf8_to_wstring(word), utf8_to_wstring(root)))
					std::cout << "VALID" << std::endl;
				else std::cout << "NOT VALID" << std::endl;
				break;
			}
			case 2: {
				std::string root, scheme;
				std::cout << "root > "; std::cin >> root;
				std::cout << "scheme > "; std::cin >> scheme;
				std::wstring res = engine.generateWord(utf8_to_wstring(root), scheme, true);
				std::cout << wstring_to_utf8(res) << std::endl;
				break;
			}
			case 3: {
				schemeMenu();
				std::cin >> choice;
				switch(choice) {
					case 1: {
						std::string pattern, name;
						engine.schemes.show();
						std::cout << "name > "; std::cin >> name;
						std::cout << "pattern (type # for the replaced characters) > "; std::cin >> pattern;
						engine.addScheme({name, utf8_to_wstring(pattern)});
						std::cout <<  "Scheme Added Successfully" << std::endl;
						break;
					}
					case 2: {
						// print all schemes in a list and delete selected
						std::string scheme = selectScheme(engine);
						engine.schemes.remove(scheme);
						std::cout <<  "Scheme Removed Successfully" << std::endl;
						break;
					}
					case 3: {
						std::string scheme = selectScheme(engine);
						std::string pattern;
						std::cout << "new pattern (type # for the replaced characters) > "; std::cin >> pattern;
						engine.schemes.remove(scheme);
						engine.addScheme({scheme, utf8_to_wstring(pattern)});
						std::cout <<  "Scheme Modified Successfully" << std::endl;
						break;
					}
					case 4: {
						engine.schemes.show();
						break;
					}
				}
				break;
			}
			case 4: {
				std::cout << "BEGIN HISTORY" << "\n";
				engine.roots.print();
				std::cout << "END HISTORY" << std::endl;
				break;
			}
		}
	}
}
