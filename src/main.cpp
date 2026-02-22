#include <iostream>
#include <string>
#include <MorphEngine.hpp>
#include <utils.hpp>

MorphEngine engine;

void generateWord() {
	bool done = false;
	int choice;
	std::string root;
	std::vector<std::string> schemes;
	std::cout << "root > "; std::cin >> root;
	while (!done) {
		generateMenu(root, schemes);
		std::cin >> choice;
		switch (choice) {
			case 3: {
				done = true;
				break;
			}
			case 1: {
				std::string scheme = selectScheme(engine);
				schemes.push_back(scheme);
				break;
			}
			case 2: {
				std::string scheme = selectScheme(engine);
				// TODO: remove scheme from table
				//schemes.remove(scheme);
				break;
			}
		}
	}
	for (std::string scheme : schemes) {
		std::wstring res = engine.generateWord(utf8_to_wstring(root), scheme, true);
		std::cout << scheme << ": " << wstring_to_utf8(res) << std::endl;
	}
}

int main() {
	//engine.addScheme({"فاعل", L"#ا##"});
	//engine.addScheme({"مفعول", L"م##و#"});
	bool quit = false;
	int choice = 0;
	while(!quit) {
		mainMenu();
		std::cin >> choice;
		switch(choice) {
			case 0:
				// Exit
				quit = true;
				break;
			case 1: {
				// Validate a word
				std::string word, root;
				std::cout << "word > "; std::cin >> word;
				std::cout << "root > "; std::cin >> root;
				if (engine.validateWord(utf8_to_wstring(word), utf8_to_wstring(root))) 
					std::cout << "VALID" << std::endl;
				else std::cout << "NOT VALID" << std::endl;
				break;
			}
			case 2: {
				// Generate a word from root
				generateWord();
				break;
			}
			case 3: {
				// Modify schemes
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
				// History
				std::cout << "BEGIN HISTORY" << "\n";
				engine.roots.print();
				std::cout << "END HISTORY" << std::endl;
				break;
			}
		}
	}
}
