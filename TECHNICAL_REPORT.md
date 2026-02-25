# Morphological Engine for the Arabic Language
## Introduction
This project presents the implementation of a morphological generation engine for the Arabic language developed in C++. The engine relies on dedicated data structures to store Arabic root words and morphological schemes, enabling the systematic generation of derived words
according to defined transformation rules.
Based on this architecture, the system provides the following main functionalities:
- Generation of derived words from a given root using selected morphological schemes.
- Validation of a given word to determine whether it belongs to the morphological family of a specified root.
- Management of roots, their validated derivatives, and morphological schemes, allowing the user to access, modify, and extend the stored data.
## Used Data Structures
This app used the following data structures:
### Hash-table
In this project, a hash table with separate chaining was implemented to manage morphological schemes efficiently. The hash table is internally represented as a vector of lists, where each list corresponds to a bucket. When two scheme names produce the same hash value, they are stored in the same bucket; this is why lists were chosen inside the hash table vector structure to store schemes with the same hash.
Each element stored in the hash table is a Scheme structure containing two attributes:
- name: the identifier of the morphological pattern.
- pattern: an abstract template representing the morphological transformation rule.
#### Logic of Derivative Generation Using the Pattern
The pattern encodes the rule used to generate derived words. It contains fixed characters and placeholders (e.g.,#) that are replaced by the root letters during word generation. For example, for the scheme مفعول, the pattern "#و#ت#م "defines how the three root consonants are inserted to
produce words such as مكتوب from the root كتب.
Each scheme name is unique within the hash table and corresponds to a single morphological rule. Therefore, the system checks for duplicates whenever a scheme with an existing name is inserted. This design ensures clarity, avoids ambiguity, and guarantees consistent morphological generation.
This structure provides fast access to transformation rules and supports dynamic management of morphological schemes within the system. The user can access the hash table and update, delete, or insert new schemes as needed.
### Binary Search Tree
For the implementation of root management, a self-balancing binary search tree (AVL tree) was used. Each node of the tree contains:
- The Arabic root (stored as a string),
- A list of its validated derivatives,
- Two pointers referencing the left and right child nodes.
The tree is organized according to the lexicographical order of the roots, which enables efficient search, insertion, and traversal operations. This structure allows the system to quickly determine whether a root already exists and to access its associated derivatives.
At first, the tree was implemented as a normal binary search tree, but the appearance of unbalanced trees was spotted during testing. Which increases the complexity and therefore the use of an AVL tree instead.
The tree plays a central role in the system, as it maintains the relationship between each root and its validated morphological family. It also supports the dynamic insertion of new roots during execution. The engine updates the tree after each validation or word generation operation, ensuring that the derivatives of each root remain up to date. Additionally, any previously
unknown root is automatically inserted, allowing the engine to progressively learn new words and new roots.
### List
For list-based containers, the C++ Standard Library was used, specifically `std::vector` and
`std::list`, since a custom implementation of lists was not required in the project specifications.
- `std::vector` is used for dynamic arrays where fast indexed access and compact storage are needed (e.g., storing validated derivatives of a root).
- `std::list` is used where frequent insertions and deletions are expected (e.g., buckets in the hash table for separate chaining).
Using the Standard Library ensures reliability, efficiency, and code clarity while allowing the project to focus on the core morphological processing logic rather than low-level container implementation.
## Deployed Algorithms
This project implements several key algorithms to manage roots, schemes, and derived words efficiently.
### Binary Search Tree / AVL Operations
- Insertion and Search: Roots are stored in a AVL tree. Insertion and search traverse the tree based on lexicographical order, following a single path from root to leaf.
- Purpose: Enables fast lookup and dynamic insertion of roots and their validated derivatives.
### Hashing Algorithm for Morphological Schemes
- Hash Function: Computes a hash from the scheme name to determine its bucket in a vector of lists.
- Collision Handling: Uses separate chaining (list per bucket) to store multiple schemes with the same hash.
- Purpose: Provides efficient access to schemes for word generation and validation.
### Morphological Generation Algorithm
- Logic: Applies the scheme pattern to a given root by replacing placeholders (e.g., `#`)
with the root letters and update the binary search tree.
.`مكتوب` word Generated` → م#ت#و#` Scheme +` كتب` Root :Example●
- Purpose: Automatically produce all valid derived words from a root and scheme.
Morphological Validation Algorithm
- Logic: Checks if a given word belongs to the morphological family of a root by generating all possible derivatives and comparing and updating the tree with new derivatives and roots.
- Purpose: Ensures correctness of user input or generated words.
Duplicate Detection
- Logic: Before adding a new derivative or scheme, the system checks for existing entries using `std::find`.
- Purpose: Avoids duplicates and ensures consistency of data.
## Complexity Analysis
### Hashtable insertion, modification and deletion
As described previously, the hash table is implemented as a vector of lists, where schemes that produce the same hash value (i.e., the same index in the vector) are stored within the same list.
This approach, known as separate chaining, ensures efficient collision handling.
Under normal conditions and with a well-distributed hash function, insertion, deletion, and search operations run in average constant time O(1). By computing the hash of a given scheme name, the system can directly access the corresponding bucket in the vector without traversing the entire structure. This direct access is the primary advantage of using a hash table.
Worst case: If many elements collide into the same bucket, operations may degrade to linear time O(n), where n is the number of stored schemes.
### Binary Search Tree insertion and search
#### Insertion
Since the tree is implemented as a self-balancing binary search tree, the number of nodes to be examined is halved each iteration. The algorithm follows a single path from the root to a leaf rather than traversing the entire tree.
Formally, the cost depends on the height of the tree. Since a balanced binary search tree is used, the height satisfies: h≈log2(n) where n is the number of nodes.
Therefore, the time complexity for insertion is
T(n) = T_ins(n) + R(n) with n = number of nodes and R is the complexity of the rebalancing operation. R(n) = O(1) since rebalancing can cost at most 2 rotations which is O(1) each. And since the number of examined nodes is halved every iteration, T_ins(n) = O(log_2(n)).
T(n) = O(log_2(n)) + O(1) = O(log_2(n))
That means that the time complexity for insertion is O(log_2(n)). And since the implementation is recursive, space complexity is O(log_2(n)).
#### Search
The search operation follows the same traversal logic as insertion, moving down a single path of the tree based on lexicographical comparisons. Consequently, its time complexity is O(log_2(n)) for a balanced tree, while the space complexity is O(1) due to the iterative implementation and
reuse of variables.
## Encountered Problems
During the development of this project, several challenges were encountered. The most significant ones are outlined below.

Setting up dependencies using CMake was not straightforward for us, as we were initially unfamiliar with CMake and the Make build system. This step required additional research and careful handling of various build errors.

Working with Arabic-compatible strings was also a new experience. Arabic characters are not encoded in the same way as standard ASCII characters, which made their manipulation particularly sensitive. Ensuring correct encoding and display required special attention throughout the implementation.

Implementing and understanding self‑balancing trees was hard due to how late the slowdown caused by the unbalanced binary search tree was found, it was discovered mere days before the project deadline.

Finally, this was our first time developing a full project in C++. We deliberately chose C++ instead of Java, which we already know, in order to challenge ourselves and learn a new language. However, dealing with complex C++ compilation errors, especially while developing in
a terminal-based Arch Linux environment, made debugging more demanding.
## Conclusion
This project implemented a C++ engine for generating and validating Arabic words using roots and morphological schemes. Using a binary search tree for roots and a hash table for schemes, the system efficiently manages, generates, and validates words. It dynamically updates derivatives and can handle new roots, demonstrating a practical application of data structures
and algorithms for Arabic morphology.
