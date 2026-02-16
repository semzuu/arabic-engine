#include "HashTable.hpp"
#include <iostream>

HashTable::HashTable(size_t size) : table(size) {}
// Getter for the table
std::vector<std::list<Scheme>>& HashTable::getTable() {
	return table;
}
// The hash function (to determine in which bucket the scheme will be stored)
size_t HashTable::hash(const std::string& key) {
	size_t h = 0;

	for (char c : key) h = h * 85 + c;
	return h % table.size();
}
// Insert a new scheme into the hashtable (if not exists)
void HashTable::insert(const Scheme& s) {
	auto& bucket = table[hash(s.name)];	
	for ( auto& e : bucket )
		if ( e.name == s.name ) { e = s; return; }
	bucket.push_back(s);
}
// Removing a scheme from the hashtable (if exists)
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
// This function was added for debugging purposes
void HashTable::show() {
	int i = 0;
	for (const auto& bucket : table) {
		std::cout << "Hash: " << i++ << std::endl;
		for (const auto& e : bucket) {
			std::cout << "Scheme Name: " << e.name << std::endl;
		}
	}
}
