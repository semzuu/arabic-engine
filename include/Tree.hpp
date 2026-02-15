#pragma once

#include "root.hpp"

struct Node {
	Root data;
	Node *left, *right;
};

class Tree {
private:
	Node *insert_impl(Node *node, const std::string& value);
	Node *search_impl(Node *node, const std::string& value);
public:
	Node *root;
	Tree();
	void insert(const std::string& value);
	Root *search(const std::string& value);
};
