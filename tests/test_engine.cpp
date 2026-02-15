#include "MorphEngine.hpp"
#include <cassert>
#include <iostream>
#include <string>

int main() {
	MorphEngine engine;	
	engine.insertRoot("كتب");
	engine.insertRoot("خرط");
	engine.insertRoot("عصب");
	engine.insertRoot("نكح");
	
	std::wstring tmp1 = engine.generateWord(L"كتب", "مفعول");
	engine.roots.print(); // Print Tree
	assert(tmp1 == L"Scheme Not Found!");
	
	std::cout << "Adding schemes...\n";
	engine.addScheme({"مفعول", L"م##و#"});
	engine.addScheme({"فاعل", L"#ا##"});
	
	std::wstring word1 = engine.generateWord(L"خرط", "مفعول");
	assert(word1 == L"مخروط");
		
	std::wstring word2 = engine.generateWord(L"كتب", "فاعل");
	assert(word2 == L"كاتب");

	engine.roots.print(); // Print Tree

	bool val1 = engine.validateWord(L"مكتوب", L"كتب");
	bool val2 = engine.validateWord(L"كاتب", L"كتب");
	
	std::cout << "validateWord('مكتوب', 'كتب') = " << val1 << std::endl;
	std::cout << "validateWord('كاتب', 'كتب') = " << val2 << std::endl;
	
	assert(val1 == true);
	assert(val2 == true);
	
	std::cout << "Testing generateAllWords('كتب'):\n";
	auto allWords = engine.generateAllWords(L"كتب");
	
	return 0;
}
