# Arabic Morphological Engine
A small C++ project that generates and validates Arabic derived words from triliteral roots using morphological schemes.

## Features
- Generate derived words from a root using morphological schemes.
- Validate whether a word belongs to a root's morphological family.
- Manage schemes in a hash table and roots/derivatives in an AVL tree.
- View explored roots and validated derivatives discovered during use.

## Dependencies
- C++17 or newer
- CMake
- picojson
- WebView

## Build
```console
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
```

Ensure your environment supports UTF-8 for Arabic text.
The full technical report is included in TECHNICAL_REPORT.md.
