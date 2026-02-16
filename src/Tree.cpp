#include <Tree.hpp>
#include <iostream>

Tree::Tree() {
	root = nullptr;
}
// Insert a new node 
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
// Searsh for a giving root in the tree and return its data struct pointer
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
// Display the tree (each root with its derivatives)
void Tree::print() {
    std::cout << "\n====== ROOT TREE ======\n\n";
    print_impl(root, "", true);
    std::cout << "\n=======================\n";
}

void Tree::print_impl(Node* node, std::string prefix, bool isLeft) {
    if (!node) return;

    std::cout << prefix;

    std::cout << (isLeft ? "├── " : "└── ");

    // Print root value
    std::cout << node->data.value;

    // Print derivatives
    if (!node->data.derivatives.empty()) {
        std::cout << "  [ ";
        for (const auto& d : node->data.derivatives) {
            std::cout << d << " ";
        }
        std::cout << "]";
    }

    std::cout << std::endl;

    // Prepare next level indentation
    std::string newPrefix = prefix + (isLeft ? "│   " : "    ");

    print_impl(node->left, newPrefix, true);
    print_impl(node->right, newPrefix, false);
}

