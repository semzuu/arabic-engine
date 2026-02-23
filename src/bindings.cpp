#include <bindings.hpp>
#include <webview/webview.h>
#include <picojson.h>
#include <MorphEngine.hpp>
#include <utils.hpp>

extern MorphEngine engine;

inline picojson::array parse_args(const std::string &arg) {
	picojson::value v;
	std::string err = picojson::parse(v, arg);
	if (!err.empty()) throw std::runtime_error(err);

	return v.get<picojson::array>();
}

void registerBindings(webview::webview &w) {
	// bound functions take a JSON string as arg and should return JSON as return value
	w.bind("hi", [](const std::string &arg) -> std::string {
		picojson::array args = parse_args(arg);
		std::cout << "ma5rout ya " << args[0].get<std::string>() << std::endl;
		return "";
	});

	w.bind("validateWordFromRoot", [](const std::string &arg) -> std::string {
		picojson::array args = parse_args(arg);
		std::string root = args[0].get<std::string>();
		std::string word = args[1].get<std::string>();
		bool isValid = engine.validateWord(utf8_to_wstring(word), utf8_to_wstring(root));
		picojson::value ret(isValid);
		return ret.serialize();
	});
}
