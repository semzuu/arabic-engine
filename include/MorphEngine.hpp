#pragma once 
#include "Tree.hpp"
#include "HashTable.hpp"

class MorphEngine {
	private:
		Tree roots;
		HashTable schemes;
		
	public:	
		void insertRoot(const std::string& root);
		void addScheme(const Scheme& s);
		std::wstring generateWord(const std::wstring& root, const std::string& scheme);
		std::list<std::wstring> generateAllWords(const std::wstring& root);
		bool validateWord(const std::wstring& word, const std::wstring& root);
};
