#include "MorphEngine.hpp"
#include <algorithm>
#include <iostream>

void MorphEngine::insertRoot(const std::string& root) {
	roots.insert(root);
}

void MorphEngine::addScheme(const Scheme& s) {
	schemes.insert(s);
	//schemes.show();
}

std::wstring MorphEngine::generateWord(const std::wstring& root, const std::string& schemeName) {
	Scheme* s = schemes.find(schemeName);
	if (!s) return L"Scheme Not Found!";
	std::wstring result = s->pattern;
	int i = 0;
	for (auto& c : result) {
		if (c == L'#') { c = root[i++]; }
	}
	return result;
}

std::list<std::wstring> MorphEngine::generateAllWords(const std::wstring& root) {
	std::list<std::wstring> result;
	for (const auto& bucket : schemes.getTable()) {
		for (const auto& e : bucket) 
			result.push_back(MorphEngine::generateWord(root, e.name));
	}
	return result;	
}

bool MorphEngine::validateWord(const std::wstring& word, const std::wstring& root) {
	bool found = false;
	std::list<std::wstring> words = MorphEngine::generateAllWords(root);
	for (const auto& w : words) {
		if (w == word) { found = true; break; }
	}	
	return found;
}
