// WatcherTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _GLIBCXX_USE_NANOSLEEP

#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "watcher.h"
#include "include/rpc/client.h"
#include "timerengine.h"

using namespace std::string_literals;

int main()
{
	//rpc::client client("127.0.0.1", 8080);
	std::string alda_read_path = "";


	//std::string watch_path = "C:\\Users\\thorf\\source\\repos\\WatcherTest\\WatcherTest\\test\\test.txt";
	std::string watch_path = "C:\\Users\\thorf\\source\\repos\\WatcherTest\\WatcherTest\\InputFiles\\synthexample.syn";

	//bool join1 = false;
	//bool join2 = false; 

	watcher watch = watcher(watch_path);
	//timerengine timer;

	std::thread watch_thread(&watcher::start, watch);
	//std::thread timer_thread(&timerengine::run, timer);



	//if (watch_thread.joinable()) {
	watch_thread.join();
	//	join1 = true;
	//}
	//else if (timer_thread.joinable()) {
	//	timer_thread.join();
	//	join2 = true;
	//}

	//Timing and RPC send 
	//int bpm = 120;
	//int period = 60 / bpm;

	//	
	//while (true) {
	//	if (watch.changed) {
	//		client.call("foo");
	//	}
	//	std::this_thread::sleep_for(std::chrono::seconds(period));
	//}
}


