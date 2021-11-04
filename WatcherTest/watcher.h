#pragma once
//#define _GLIBCXX_USE_NANOSLEEP

#include <string>
#include <locale>
#include <codecvt>
#include <iostream>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <chrono>
#include "include/FileWatch.hpp"
#include "include/rpc/client.h"



class watcher
{
public:
	bool changed = false;
	std::string saved_path = "";


	watcher(std::string path);
	std::wstring ConvertUtf8ToWide(const std::string& str);
	void start();
	void restart();
	void exit();


private:
	void run();
	bool quit = false;


};

