#include "timerengine.h"

void timerengine::setup(std::string addr, int port)
{
	l_addr = addr;
	l_port = port;
}

void timerengine::set_bpm(int bpm)
{
	this->bpm = bpm;
	this->beat_period = (double)60 / (double)this->bpm;
	this->quart_period = beat_period / (double)4;
	this->q_period_milli = quart_period * 1000;
}

void timerengine::add_notes(std::vector<int> notes)
{
	for (int i = 0; i < notes.size(); i++) {
		this->notes.push_back(notes.at(i));
		note_max_num++;
	}
	note_counter = 0; 
}

void timerengine::run()
{
	rpc::client client(l_addr, l_port);

	while (true) {
		if (notes.size() != 0) {
			client.call("addnotes", notes.at(note_counter));
			note_counter++;
			note_counter = note_counter % note_max_num;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(q_period_milli));
	}
}



