#pragma once

#include <string>
#include <Tree.hpp>
#include <MorphEngine.hpp>
#include <filesystem>
#include <picojson.h>

std::string file_url_for(const std::filesystem::path &p);
picojson::array parse_json_args(const std::string &arg);
std::wstring utf8_to_wstring(const std::string &s);
std::string wstring_to_utf8(const std::wstring &w);
std::string selectScheme(MorphEngine engine);
void mainMenu();
void generateMenu(std::string root, std::vector<std::string> schemes);
void schemeMenu();
void print(Node *node);
