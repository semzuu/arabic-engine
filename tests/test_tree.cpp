#include <Tree.hpp>
#include <cassert>
#include <iostream>

int main() {
	Tree t;
	t.insert("كتب");
	t.insert("زرع");

	assert(t.search("كتب"));
	assert(!t.search("لعب"));
}
