#include "HashTable.hpp"
#include <cassert>

int main() {
	HashTable h;
	h.insert({"فاعل", L"#ا##"});
	assert(h.find("فاعل"));
	h.remove("فاعل");
	assert(!h.find("فاعل"));

	return 0;
}
