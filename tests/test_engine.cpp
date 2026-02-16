#include "MorphEngine.hpp"
#include <cassert>
#include <iostream>
#include <string>

int main() {
	// Insert some roots
	MorphEngine engine;	
	engine.insertRoot("كتب");
	engine.insertRoot("خرط");
	engine.insertRoot("عصب");
	engine.insertRoot("نكح");
	// 1 - Trying to generate a word before providing the scheme	
	std::cout << "<---Generate a word before giving the scheme--->" << std::endl;
	std::wstring tmp1 = engine.generateWord(L"كتب", "مفعول");
	engine.roots.print(); // Print Tree
	assert(tmp1 == L"Scheme Not Found!");
	// 2 - Adding schemes and testing word generation	
	std::cout << "<---Adding schemes and testing word generation--->" << std::endl;
	engine.addScheme({"مفعول", L"م##و#"});
	engine.addScheme({"فاعل", L"#ا##"});
	
	std::wstring word1 = engine.generateWord(L"خرط", "مفعول");
	assert(word1 == L"مخروط");
		
	std::wstring word2 = engine.generateWord(L"عصب", "مفعول");
	assert(word2 == L"معصوب");

	engine.roots.print(); // Print Tree
	// 3 - Testing word validation
	bool val1 = engine.validateWord(L"مكتوب", L"كتب");
	bool val2 = engine.validateWord(L"كاتب", L"كتب");
	engine.roots.print(); // Print Tree

	std::cout << "validateWord('مكتوب', 'كتب') = " << val1 << std::endl;
	std::cout << "validateWord('كاتب', 'كتب') = " << val2 << std::endl;
	
	assert(val1 == true);
	assert(val2 == true);

	return 0;
}
