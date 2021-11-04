#pragma once
#include "include/rpc/client.h"

class timerengine
{
public:
	//Timing and RPC send 
	std::string l_addr = "127.0.0.1";
	int l_port = 8080;

	std::vector<int> notes;
	int note_count = 0;

	int bpm = 60;
	int period = 60 / bpm;

	void setup(std::string addr, int port);	
	void set_bpm(int bpm);
	void add_notes(std::vector<int> notes);
	void run();
	void pulse();

};

