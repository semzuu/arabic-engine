#include "MorphEngine.hpp"
#include <cassert>
#include <iostream>

int main() {

	MorphEngine engine;
	engine.insertRoot("كتب");
	
	assert(engine.generateWord("كتب", "مفعول") == ""); 
	
	engine.addScheme({"مفعول", "م_ت_و_"});
	engine.addScheme({"فاعل", "_ا_ل"});

	std::string word1 = engine.generateWord("كتب", "مفعول");
	assert(word1 == "مكتوب");
	
	std::string word2 = engine.generateWord("كتب", "فاعل");
	assert(word2 == "كاتب");
	
	assert(engine.validateWord("مكتوب", "كتب") == true);
	assert(engine.validateWord("كاتب", "كتب") == false); 
	
	std::cout << "All MorphEngine tests passed successfully.\n";
	return 0;
}

