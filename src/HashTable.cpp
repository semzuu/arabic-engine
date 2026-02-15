#include "HashTable.hpp"

HashTable::HashTable(size_t size) : table(size) {}

const std::vector<std::list<Scheme>>& getTable() const {
	return table;
}

size_t HashTable::hash(const std::string& key) {
	size_t h = 0;

	for (char c : key) h = h * 85 + c;
	return h % table.size();
}

void HashTable::insert(const Scheme& s) {
	auto& bucket = table[hash(s.name)];	
	for ( auto& e : bucket )
		if ( e.name == s.name ) { e = s; return; }
	bucket.push_back(s);
}

void HashTable::remove(const std::string& name) {
	auto& bucket = table[hash(name)];
	for (auto it = bucket.begin(); it != bucket.end(); ) {
		if (it->name == name) it = bucket.erase(it);
		else it++;
	}
}

Scheme* HashTable::find(const std::string& name) {
	auto& bucket = table[hash(name)];
	for (auto& s : bucket)
		if (s.name == name) return &s;
	return nullptr;
}
