#pragma once
#include "Scheme.hpp"
#include <vector>
#include <list>

class HashTable {
	private:
		std::vector<std::list<Scheme>> table;
		size_t hash(const std::string& key);
	
	public:
		HashTable(size_t size = 10);
		std::vector<std::list<Scheme>>& getTable();
		void insert(const Scheme& s);
		void remove(const std::string& name);
		Scheme* find(const std::string& name);
		void show();
};
