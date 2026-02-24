#include <Tree.hpp>
#include <iostream>

Tree::Tree() {
	root = nullptr;
}

int Tree::height(Node *node) {
	return (!node) ? 0 : node->height;
}

int Tree::balanceFactor(Node *node) {
	return (!node) ? 0 : height(node->left) - height(node->right);
}

Node *Tree::rotateRight(Node *z) {
	Node *y = z->left;
	Node *t3 = y->right;

	y->right = z;
	z->left = t3;

	z->height = 1 + std::max(height(z->left), height(z->right));
	y->height = 1 + std::max(height(y->left), height(y->right));
	return y;
}

Node *Tree::rotateLeft(Node *z) {
	Node *y = z->right;
	Node *t2 = y->left;

	y->left = z;
	z->right = t2;

	z->height = 1 + std::max(height(z->left), height(z->right));
	y->height = 1 + std::max(height(y->left), height(y->right));
	return y;
}

Node *Tree::rotateLeftRight(Node *z) {
	z->left = rotateLeft(z->left);
	return rotateRight(z);
}

Node *Tree::rotateRightLeft(Node *z) {
	z->right = rotateRight(z->right);
	return rotateLeft(z);
}

Node *Tree::rebalance(Node *node) {
	int balance = balanceFactor(node);
	if (balance > 1) {
		if (balanceFactor(node->left) < 0) {
			return rotateLeftRight(node);
		}
		return rotateRight(node);
	}
	if (balance < -1) {
		if (balanceFactor(node->right) > 0) {
			return rotateRightLeft(node);
		}
		return rotateLeft(node);
	}
	return node;
}

Node *Tree::insert_impl(Node *node, const std::string& value) {
	if (!node) {
		return new Node{
			{value, {}},
			0,
			nullptr,
			nullptr
		};
	}

	if (value <= node->data.value) {
		node->left = insert_impl(node->left, value);
	} else {
		node->right = insert_impl(node->right, value);
	}

	node->height = 1 + std::max(height(node->left), height(node->right));
	return rebalance(node);
}

// Insert a new node
void Tree::insert(const std::string& value) {
	root = insert_impl(root, value);
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
