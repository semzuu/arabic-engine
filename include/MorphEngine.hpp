#pragma once 
#include "Tree.hpp"
#include "HashTable.hpp"
#include "Scheme.hpp"

class MorphEngine {
	public:	
		HashTable schemes;
		Tree roots;
		void insertRoot(const std::string& root);
		void addScheme(const Scheme& s);
		std::string trim(const std::string& s);
		void loadSchemesFromFile(const std::string& filename);
		std::wstring generateWord(const std::wstring& root, const std::string& scheme, bool updateRoots);
		std::list<std::wstring> generateAllWords(const std::wstring& root);
		bool validateWord(const std::wstring& word, const std::wstring& root);	
};
