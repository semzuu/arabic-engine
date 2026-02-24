#include <utils.hpp>
#include <string>
#include <iostream>
#include <locale>
#include <codecvt>
#include <Tree.hpp>
#include <MorphEngine.hpp>
#include <picojson.h>

std::string file_url_for(const std::filesystem::path &p) {
  auto abs = std::filesystem::absolute(p).lexically_normal();
#ifdef _WIN32
  // file:///C:/path/to/file
  std::string s = "file:///" + abs.string();
  for (auto &c : s) if (c == '\\') c = '/';
  return s;
#else
  // file:///absolute/path
  return std::string("file://") + abs.string();
#endif
}

picojson::array parse_json_args(const std::string &arg) {
	picojson::value v;
	std::string err = picojson::parse(v, arg);
	if (!err.empty()) throw std::runtime_error(err);

	return v.get<picojson::array>();
}

// since std::wstring_convert is deprecated,
// std::wcstombs is used instead
// based on this article:
// https://www.geeksforgeeks.org/cpp/convert-wstring-to-string-in-c/
std::wstring utf8_to_wstring(const std::string &s) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    return conv.from_bytes(s);
}

std::string wstring_to_utf8(const std::wstring &w) {
	size_t len = std::wcstombs(nullptr, w.c_str(), 0) + 1;
	char *buf = new char[len];
	std::wcstombs(buf, w.c_str(), len);
	std::string str(buf);
	delete[] buf;
	return str;
}
