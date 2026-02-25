#pragma once

#include "Root.hpp"
#include <deque>
#include <cassert>

struct Node {
	Root data;
	int height;
	Node *left, *right;
};

class Tree {
private:
	void print_impl(Node *node, std::string prefix, bool isLeft);
	Node *insert_impl(Node *node, const std::string& value);
	int height(Node *node);
	int balanceFactor(Node *node);
	Node *rotateRight(Node *z);
	Node *rotateLeft(Node *z);
	Node *rotateLeftRight(Node *z);
	Node *rotateRightLeft(Node *z);
	Node *rebalance(Node *node);
public:
	Node *root;
	Tree();
	void insert(const std::string& value);
	Root *search(const std::string& value);
	void print();

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
