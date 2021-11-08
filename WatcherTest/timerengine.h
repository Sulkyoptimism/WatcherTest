#pragma once
#include "include/rpc/client.h"

class timerengine
{
public:
	//Timing and RPC send 
	std::string l_addr = "127.0.0.1";
	int l_port = 8080;

	std::vector<int> notes;
	int note_max_num = 0;
	int note_counter = 0;

	int bpm = 60;
	double beat_period = 60 / bpm;
	double quart_period = beat_period / 4;
	int q_period_milli = quart_period * 1000;

	void setup(std::string addr, int port);	
	void set_bpm(int bpm);
	void add_notes(std::vector<int> notes);
	void run();

};

