#include "MorphEngine.hpp"
#include <cassert>
#include <iostream>
#include <string>

int main() {
	MorphEngine engine;	
	std::cout << "Inserting root: كتب\n";
	engine.insertRoot("كتب");
	
	std::wstring tmp1 = engine.generateWord(L"كتب", "مفعول");
	assert(tmp1 == L"Scheme Not Found!");
	
	std::cout << "Adding schemes...\n";
	engine.addScheme({"مفعول", L"م##و#"});
	engine.addScheme({"فاعل", L"#ا##"});
	
	std::wstring word1 = engine.generateWord(L"كتب", "مفعول");
	assert(word1 == L"مكتوب");
	
	std::wstring word2 = engine.generateWord(L"كتب", "فاعل");
	assert(word2 == L"كاتب");
	
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

