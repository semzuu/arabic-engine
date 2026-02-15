#include <tree.hpp>

Tree::Tree() {
	root = nullptr;
}

Node *Tree::insert_impl(Node *node, const std::string& value) {
	if (!node) return new Node{
		{value, {}},
		nullptr,
		nullptr
	};
	if (value <= node->data.value) {
		node->left = insert_impl(node->left, value);
	}
	else if (value > node->data.value) {
		node->right = insert_impl(node->right, value);
	}
	return node;
}

void Tree::insert(const std::string& value) {
	root = insert_impl(root, value);
}

Node *Tree::search_impl(Node *node, const std::string& value) {
	if (!node) return nullptr;
	if (value == node->data.value) return node;
	if (value < node->data.value) return search_impl(node->left, value);
	return search_impl(node->right, value);
}

Root *Tree::search(const std::string& value) {
	Node *res = search_impl(root, value);
	if (res) return &(res->data);
	else return nullptr;
}
