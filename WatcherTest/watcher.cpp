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
void watcher::start()
{
	bool t =false;
	bool* temp = &t;
	run(temp);

}
void watcher::restart() {
	changed = false;
	start();
}
void watcher::exit()
{
	quit = true;
}


std::thread watcher::thread_process(bool* alda_bool) {
	return std::thread([=] {run(alda_bool); });
}

void watcher::run(bool* alda_bool)
{
	while (!quit) {
		std::wstring wide = ConvertUtf8ToWide(saved_path);
		std::wcout << wide << L"\n";
		filewatch::FileWatch<std::wstring> watch(
			wide,
			[this](const std::wstring& path, const filewatch::Event change_type) {
				std::wcout << path << L"\n";
				changed = true;
			});
		while (!changed){}
		//start java process
		//parse languages into json 
		if (changed) {
			if (saved_path.substr(saved_path.find_last_of(".") + 1) == "syn") {
				printf("change occured, editing files to reflect\n");
				std::string path_to_parser = ".\\AntlrSynthParser\\bin\\AntlrSynthGrammarProd.bat";
				output_path = ".\\Synth\\Synthout.json";
				std::string process = path_to_parser + " " + saved_path + " " + output_path;
				system(process.c_str());


				//hot reload rpc call
				rpc::client client("127.0.0.1", 8080);
				client.call("reload");
				printf("RPC reload call sent\n");
			}
			else if (saved_path.substr(saved_path.find_last_of(".") + 1) == "alda") {
				//alda parser java
				printf("change occured, editing files to reflect\n");
				std::string path_to_parser = ".\\AntlrAldaParser\\bin\\AntlrAldaProduction.bat";
				output_path = ".\\OutputFiles\\Aldaout.json";
				std::string process = path_to_parser + " " + saved_path + " " + output_path;
				system(process.c_str());

				*alda_bool = true;
			}

		}
		changed = false;
		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
	return;
}

