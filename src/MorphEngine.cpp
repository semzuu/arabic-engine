#include "MorphEngine.hpp"
#include <algorithm>
#include <iostream>
#include <codecvt>
#include <locale>

// Insert a new root to the tree
void MorphEngine::insertRoot(const std::string& root) {
	roots.insert(root);
}
// Insert a new scheme to the hashtable
void MorphEngine::addScheme(const Scheme& s) {
	schemes.insert(s);
	//schemes.show();
}
// Generate a new from a giving root and scheme
std::wstring MorphEngine::generateWord(const std::wstring& root, const std::string& schemeName) {
	Scheme* s = schemes.find(schemeName);
	if (!s) return L"Scheme Not Found!";
	std::wstring result = s->pattern;
	// Word generation logic
	int i = 0;
	for (auto& c : result) {
		if (c == L'#') { c = root[i++]; }
	}
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;	
	// Add the root if it's missing from the tree
	std::string r = converter.to_bytes(root);	
	Root* p = roots.search(r);
	if (!p) {
		insertRoot(r);
		p = roots.search(r);
	}
	// Update the root derivatives list 
	std::string res = converter.to_bytes(result);	
	auto& d = p->derivatives;
	if (std::find(d.begin(), d.end(), res) == d.end()) {
		d.push_back(res);
	}
	return result;
}
// Generate all words based on the provided schemes in the hashtable (used for word validation)
std::list<std::wstring> MorphEngine::generateAllWords(const std::wstring& root) {
	std::list<std::wstring> result;
	for (const auto& bucket : schemes.getTable()) {
		for (const auto& e : bucket) 
			result.push_back(MorphEngine::generateWord(root, e.name));
	}
	return result;	
}
// Word validation
bool MorphEngine::validateWord(const std::wstring& word, const std::wstring& root) {
	bool found = false;
	auto words = MorphEngine::generateAllWords(root);
	for (const auto& w : words) {
		if (w == word) { found = true; break; }
	}
	// Update the root derivatives list 
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	if (found) {
		Root* p = roots.search(converter.to_bytes(root));
		if (p) { 
			std::string s = converter.to_bytes(word);			
			auto& d = p->derivatives;
			if (std::find(d.begin(), d.end(), s) == d.end()) {
				d.push_back(s);
			}
		}
	}
	return found;
}
