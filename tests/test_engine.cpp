#include "MorphEngine.hpp"
#include <cassert>
#include <iostream>

int main() {

	MorphEngine engine;
	
	std::cout << "Inserting root: كتب\n";
	engine.insertRoot("كتب");
	
	// Test before adding scheme
	std::string tmp1 = engine.generateWord("كتب", "مفعول");
	std::cout << "generateWord('كتب', 'مفعول') before adding scheme: " << tmp1 << std::endl;
	assert(tmp1 == "Scheme Not Found or Invalid Root Length!"); // should be empty
	
	std::cout << "Adding schemes...\n";
	engine.addScheme({"مفعول", "م_ت_و_"});
	engine.addScheme({"فاعل", "_ا_ل"});
	
	// Test generateWord for each scheme
	std::string word1 = engine.generateWord("كتب", "مفعول");
	std::cout << "generateWord('كتب', 'مفعول') = " << word1 << std::endl;
	assert(word1 == "مكتوب");
	
	std::string word2 = engine.generateWord("كتب", "فاعل");
	std::cout << "generateWord('كتب', 'فاعل') = " << word2 << std::endl;
	assert(word2 == "كاتب");
	
	// Test validation
	bool val1 = engine.validateWord("مكتوب", "كتب");
	bool val2 = engine.validateWord("كاتب", "كتب");
	
	std::cout << "validateWord('مكتوب', 'كتب') = " << val1 << std::endl;
	std::cout << "validateWord('كاتب', 'كتب') = " << val2 << std::endl;
	
	assert(val1 == true);
	assert(val2 == false);
	
	// Test generateAllWords
	std::cout << "Testing generateAllWords('كتب'):\n";
	auto allWords = engine.generateAllWords("كتب");
	for (const auto& w : allWords) {
	    std::cout << "  " << w << std::endl;
	}
	
	std::cout << "All MorphEngine tests passed successfully.\n";
	return 0;
}

