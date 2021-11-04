#include "watcher.h"

using namespace std::string_literals;


watcher::watcher(std::string str_path)
{
	saved_path = str_path;
}
std::wstring watcher::ConvertUtf8ToWide(const std::string& str)
{
	int count = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), NULL, 0);
	std::wstring wstr(count, 0);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), &wstr[0], count);
	return wstr;
}
void watcher::restart() {
	changed = false;
	start();
}
void watcher::exit()
{
	quit = true;
}
void watcher::start()
{
	run();

}

void watcher::run()
{
	while (!quit) {


		std::wstring wide = ConvertUtf8ToWide(saved_path);
		std::wcout << wide << L"\n";

		filewatch::FileWatch<std::wstring> watch(
			wide,
			[this](const std::wstring& path, const filewatch::Event change_type) {
				std::wcout << path << L"\n";
				changed = true;
			}
		);

		while (!changed){}

		//start java process
		//parse languages into json 
		if (changed) {
			printf("change occured, editing files to reflect");
			std::string path_to_parser = ".\\AntlrSynthGrammar\\bin\\AntlrSynthGrammar.bat";
			std::string path_to_output = "C:\\Users\\thorf\\source\\repos\\SDL2_synth\\SDL2_synth\\new_params.json";
			std::string process = path_to_parser + " " + saved_path + " " + path_to_output;
			system(process.c_str());

			rpc::client client("127.0.0.1", 8080);
			client.call("reload");
			printf("RPC reload call sent");
		}
		changed = false;
		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
	return;
}

