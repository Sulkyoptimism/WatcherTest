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

void timerengine::add_notes(std::map<int, std::vector<std::pair<int, int>>> notes)
{
	/*for (int i = 0; i < notes.size(); i++)
	{
		std::vector<std::pair<int, int>> note_list;

		for (int j = 0; j < notes[i].size(); j++)
		{

		}
		
	}
*/



	this->notes_per_increment = notes;
	
	note_counter = 0; 
}

void timerengine::run()
{
	rpc::client client(l_addr, l_port);

	while (!quit) {
		//for that increment eg 1/16th beat
		std::vector<std::pair<int, int>> temp_list = notes_per_increment[note_counter];
		for (int i = 0; i < temp_list.size(); i++)
		{
			client.call("addnotes", temp_list.size(), temp_list.at(i));
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(q_period_milli));
		note_counter++;
		note_counter = note_counter % 16;
	}
}



