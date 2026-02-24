#pragma once

#include "Root.hpp"
#include <deque>
#include <cassert>

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
	void print();
	void print_impl(Node *node, std::string prefix, bool isLeft);

	// Iterator Implemntatino
	// This iterator implementation iterates over the tree
	// using BFS
	class Iterator {
		private:
			Node *it_ptr;
			std::deque<Node *> queue;
		public:
			Iterator(Node *ptr);
			Root& operator*();
			Root* operator->();
			Iterator& operator++();
			bool operator==(const Iterator &that);
			bool operator!=(const Iterator &that);
	};

	Tree::Iterator begin();
	Tree::Iterator end();
};
