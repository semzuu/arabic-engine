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
		std::string generateWord(const std::string& root, const std::string& scheme);
		std::list<std::string> generateAllWords(const std::string& root);
		bool validateWord(const std::string& word, const std::string& root);
};
