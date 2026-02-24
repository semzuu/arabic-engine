#include <Tree.hpp>
#include <iostream>

Tree::Tree() {
	root = nullptr;
}

// Insert a new node 
void Tree::insert(const std::string& value) {
	if (!root) {
		root = new Node{
			{value, {}},
			nullptr,
			nullptr
		};
		return;
	}
	Node *curr = root, *prev = nullptr;
	bool left = true; // just a boolean to know which direction to insert in
	while (curr) {
		prev = curr;
		if (value <= curr->data.value) {
			curr = curr->left;
			left = true;
		}
		else if (value > curr->data.value) {
			curr = curr->right;
			left = false;
		}
	}
	if (prev) {
		Node *temp = new Node{
			{value, {}},
			nullptr,
			nullptr
		};
		if (left) prev->left = temp;
		else prev->right = temp;
	}
}

// Searsh for a giving root in the tree and return its data struct pointer
Root *Tree::search(const std::string& value) {
	Node *curr = root;
	while (curr) {
		if (value < curr->data.value) curr = curr->left;
		else if (value > curr->data.value) curr = curr->right;
		else return &(curr->data);
	}
	return nullptr;
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


// Iterator Implementation
Tree::Iterator::Iterator(Node *ptr) {
	if (ptr) {
		queue.push_back(ptr);
		it_ptr = queue.front();
	} else it_ptr = nullptr;
}

Root& Tree::Iterator::operator*() {
	assert(it_ptr != nullptr);
	return it_ptr->data;
}

Root* Tree::Iterator::operator->() {
	return &Iterator::operator*();
}

Tree::Iterator& Tree::Iterator::operator++() {
	if (queue.empty()) {
		it_ptr = nullptr;
		return *this;
	}

	Node *curr = queue.front();
	queue.pop_front();

	if (curr->left) queue.push_back(curr->left);
	if (curr->right) queue.push_back(curr->right);

	it_ptr = queue.empty() ? nullptr : queue.front();
	return *this;
}

bool Tree::Iterator::operator==(const Tree::Iterator &that) { return it_ptr == that.it_ptr; }
bool Tree::Iterator::operator!=(const Tree::Iterator &that) { return it_ptr != that.it_ptr; }

Tree::Iterator Tree::begin() { return Tree::Iterator(root); };
Tree::Iterator Tree::end() { return Tree::Iterator(nullptr); };
