#include <iostream>
#include <string>
#include <MorphEngine.hpp>
#include <utils.hpp>
#include <webview/webview.h>
#include <filesystem>
#include <bindings.hpp>

MorphEngine engine;

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE /*hInst*/, HINSTANCE /*hPrevInst*/,
                   LPSTR /*lpCmdLine*/, int /*nCmdShow*/) {
#else
int main() {
#endif
	try {
		std::filesystem::path schemes = std::filesystem::path(DATA_DIR) / "schemes.txt";
		engine.loadSchemesFromFile(schemes);
		webview::webview w(true, nullptr);
		w.set_title("Arabic Morphological Engine");
		w.set_size(800, 600, WEBVIEW_HINT_NONE);
		registerBindings(w);

		std::filesystem::path index = std::filesystem::path(ASSETS_DIR) / "index.html";
		std::string url = file_url_for(index);
		w.navigate(url);
		w.run();
	} catch (const webview::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}
