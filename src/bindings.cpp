#include <bindings.hpp>
#include <webview/webview.h>
#include <picojson.h>

void registerBindings(webview::webview &w) {
	// bound functions take a JSON string as arg and should return JSON as return value
	w.bind("hi", [&](const std::string &arg) -> std::string {
		picojson::value v;
		std::string err = picojson::parse(v, arg);
		if (!err.empty()) {
			std::cerr << err << std::endl;
			return "";
		}

		picojson::array args = v.get<picojson::array>();
		std::cout << "ma5rout ya " << args[0].get<std::string>() << std::endl;
		return "";
	});
}
