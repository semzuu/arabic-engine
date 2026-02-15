#include "MorphEngine.hpp"
#include <algorithm>

void MorphEngine::insertRoot(const std::string& root) {
	roots.insert(root);
}

void MorphEngine::addScheme(const Scheme& s) {
	schemes.insert(s);
}

std::string MorphEngine::generateWord(const std::string& root, const std::string& schemeName) {
	Scheme* s = schemes.find(schemeName);
	if (!s || root.size() != 3) return "Scheme Not Found or Invalid Root Length!";

	std::string result = s->pattern;
	int i = 0;
	for (char& c : result)
		if (c == '_' && i < 3)
			c = root[i++];
	return result;
}

std::list<std::string> MorphEngine::generateAllWords(const std::string& root) {
	std::list<std::string> result;
	for (const auto& bucket : schemes.getTable()) {
		for (const auto& e : bucket) 
			result.push_back(MorphEngine::generateWord(root, e.name));
	}
	return result;	
}

bool MorphEngine::validateWord(const std::string& word, const std::string& root) {
	std::list<std::string> words = generateAllWords(root);
	return std::find(words.begin(), words.end(), word) != words.end();
}
