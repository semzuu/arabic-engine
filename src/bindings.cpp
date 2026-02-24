#include <bindings.hpp>
#include <webview/webview.h>
#include <picojson.h>
#include <MorphEngine.hpp>
#include <utils.hpp>

extern MorphEngine engine;

void registerBindings(webview::webview &w) {
	// bound functions take a JSON string as arg and should return JSON as return value
	w.bind("hi", [](const std::string &arg) -> std::string {
		picojson::array args = parse_json_args(arg);
		std::cout << "ma5rout ya " << args[0].get<std::string>() << std::endl;
		return "";
	});

	w.bind("validateWordFromRoot", [](const std::string &arg) -> std::string {
		picojson::array args = parse_json_args(arg);
		std::string root = args[0].get<std::string>();
		std::string word = args[1].get<std::string>();
		bool isValid = engine.validateWord(utf8_to_wstring(word), utf8_to_wstring(root));
		picojson::value ret(isValid);
		return ret.serialize();
	});
	w.bind("getRoots", [](const std::string &arg) -> std::string {
		(void)arg;
		picojson::array tree;
		for (Root root: engine.roots) {
			picojson::object obj;
			obj["root"] = picojson::value(std::string(root.value));
			picojson::array deriv;
			for (const auto d: root.derivatives) {
				deriv.push_back(picojson::value(std::string(d)));
			}
			obj["derivatives"] = picojson::value(deriv);
			tree.push_back(picojson::value(obj));
		}
		picojson::value ret(tree);
		return ret.serialize();
	});
	w.bind("getSchemes", [](const std::string &arg) -> std::string {
		(void)arg;
		picojson::array schemes;
		for (const auto &bucket : engine.schemes.getTable()) {
			for (const auto &scheme : bucket) {
				picojson::object obj;
				obj["name"] = picojson::value(std::string(scheme.name));
				obj["pattern"] = picojson::value(std::string(wstring_to_utf8(scheme.pattern)));
				schemes.push_back(picojson::value(obj));
			}
		}
		picojson::value ret(schemes);
		return ret.serialize();
	});
	w.bind("generateWord", [](const std::string &arg) -> std::string {
		picojson::array args = parse_json_args(arg);
		std::string root = args[0].get<std::string>();
		std::string scheme = args[1].get<std::string>();
		std::wstring res = engine.generateWord(utf8_to_wstring(root), scheme, true);
		std::string word = wstring_to_utf8(res);
		picojson::value ret(word);
		return ret.serialize();
	});
	w.bind("removeScheme", [](const std::string &arg) -> std::string {
		picojson::array args = parse_json_args(arg);
		std::string name = args[0].get<std::string>();
		engine.schemes.remove(name);
		return "";
	});
	w.bind("addScheme", [](const std::string &arg) -> std::string {
		picojson::array args = parse_json_args(arg);
		std::string name = args[0].get<std::string>();
		std::string pattern = args[1].get<std::string>();
		engine.addScheme({name, utf8_to_wstring(pattern)});
		return "";
	});
}
