#include "MorphEngine.hpp"
#include <algorithm>
#include <iostream>
#include <codecvt>
#include <locale>

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
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;	
	std::string r = converter.to_bytes(root);	
	Root* p = roots.search(converter.to_bytes(root));
	if (!p) {
		insertRoot(r);
		Root* p = roots.search(r);
	}
	std::string res = converter.to_bytes(result);	
	auto& d = p->derivatives;
	if (std::find(d.begin(), d.end(), res) == d.end()) {
		d.push_back(res);
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
	auto words = MorphEngine::generateAllWords(root);
	for (const auto& w : words) {
		if (w == word) { found = true; break; }
	}	
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
	roots.print();
	return found;
}
