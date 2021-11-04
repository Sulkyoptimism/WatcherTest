#include "timerengine.h"

void timerengine::setup(std::string addr, int port)
{
	l_addr = addr;
	l_port = port;
}

void timerengine::set_bpm(int bpm)
{
	this->bpm = bpm;
	this->period = 60 / this->bpm;
}

void timerengine::add_notes(std::vector<int> notes)
{
	for (int i = 0; i < notes.size(); i++) {
		this->notes.push_back(notes.at(i));
	}
	note_count = 0; 
}

void timerengine::run()
{
	while (true) {
		if (notes.size() != 0) {
			pulse();
		}
		std::this_thread::sleep_for(std::chrono::seconds(period));
	}
}

void timerengine::pulse()
{
	rpc::client client(l_addr, l_port);
	client.call("assign", notes.at(note_count));
	note_count++;
}
