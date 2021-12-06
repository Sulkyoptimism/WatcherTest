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

	//std::string watch_path = "C:\\Users\\thorf\\source\\repos\\WatcherTest\\WatcherTest\\test\\test.txt";
	std::string syn_watch_path = ".\\InputFiles\\synthexample.syn";
	std::string alda_watch_path = ".\\InputFiles\\aldaexample.alda";

	watcher syn_watch = watcher(syn_watch_path);
	watcher alda_watch = watcher(alda_watch_path);
	timerengine t;
	timerengine* timer = &t;

	timer->setup("127.0.0.1", 8080);
	timer->set_bpm(120);

	//
	//std::map<int, std::vector<std::pair<std::string, int>>> notes_map;

	//std::vector<std::pair<int, int>> temp_notes1;
	//std::vector<std::pair<int, int>> temp_notes2;
	//std::vector<std::pair<int, int>> temp_notes3;
	//std::vector<std::pair<int, int>> temp_notes4;
	//

	////pair {synthid, note}
	//std::pair<int, int> p1 = { 0, 38 };
	//std::pair<int, int> p2 = { 0, 42 };
	//std::pair<int, int> p3 = { 0, 50 };
	//std::pair<int, int> p4 = { 0, 46 };

	//temp_notes1.push_back(p1);
	//temp_notes2.push_back(p2);
	//temp_notes3.push_back(p3);
	//temp_notes4.push_back(p4);

	//std::pair<int, int> dud;
	//dud.first = -1;
	//dud.second = -1;
	//std::vector<std::pair<int, int>> dud_list;
	//dud_list.push_back(dud);

	//notes_map[0] = temp_notes1;
	//notes_map[1] = dud_list;
	//notes_map[2] = dud_list;
	//notes_map[3] = dud_list;
	//notes_map[4] = temp_notes2;
	//notes_map[5] = dud_list;
	//notes_map[6] = dud_list;
	//notes_map[7] = dud_list;
	//notes_map[8] = temp_notes3;
	//notes_map[9] = dud_list;
	//notes_map[10] = dud_list;
	//notes_map[11] = dud_list;
	//notes_map[12] = temp_notes4;
	//notes_map[13] = dud_list;
	//notes_map[14] = dud_list;
	//notes_map[15] = dud_list;



	//timer.add_notes(notes_map);

	std::thread watch_thread1(&watcher::start, syn_watch);
	//std::thread watch_thread2(&watcher::start, alda_watch);
	bool alda_done = false;
	std::thread watch_thread2 = alda_watch.thread_process(&alda_done);


	std::thread timer_thread(&timerengine::run, timer);

	
	while (true)
	{
		if (alda_done == true) {
			timer->load_from_json();
			alda_done =false;
		}
	}


	watch_thread1.join();
	watch_thread2.join();
	timer_thread.join();

}


