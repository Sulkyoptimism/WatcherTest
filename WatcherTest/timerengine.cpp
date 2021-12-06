#include "timerengine.h"


void timerengine::setup(std::string addr, int port)
{
	l_addr = addr;
	l_port = port;
}

void timerengine::set_bpm(int bpm)
{
	this->bpm_set = true;
	this->bpm = bpm;
	this->beat_period = (double)60 / (double)this->bpm;
	this->quart_period = beat_period / (double)4;
	this->q_period_milli = quart_period * 1000;
}

void timerengine::add_notes(std::map<int, std::vector<std::pair<std::string, int>>> notes)
{
	/*for (int i = 0; i < notes.size(); i++)
	{
		std::vector<std::pair<int, int>> note_list;

		for (int j = 0; j < notes[i].size(); j++)
		{

		}
		
	}
*/



	notes_per_increment = notes;
	
}

void timerengine::load_from_json()
{
	std::string path = ".\\OutputFiles\\Aldaout.json";
	std::ifstream jsonf(path);
	json json_data;
	jsonf >> json_data;

	int max_note_count = 0;
	int def_count = 0;
	set_bpm(json_data.at("tempo"));

	std::vector<part_def> definitions;
	for (int i = 0; i < 8; i++)
	{
		try
		{
			std::string name = "name" + std::to_string(i);

			if (json_data.at(name) != NULL) {
				part_def new_part;
				new_part.name = json_data.at(name);
				json notes_list = json_data.at(new_part.name + " notes");
				for (int j = 0; j < 16; j++)
				{
					if (j > max_note_count) {
						max_note_count = j;
					}
					int note = -1;
					try
					{
						note = notes_list.at(std::to_string(j));
						new_part.notes.push_back(note);
					}
					catch (const std::exception&)
					{
						break;
					}

				}
				definitions.push_back(new_part);
				def_count++;
			}
		}
		catch (const std::exception&)
		{

		}
		
	}

	std::map<int, std::vector<std::pair<std::string, int>>> notes_map;


	for (int i = 0; i < def_count; i++)
	{
		int offset =  max_note_count/ definitions.at(i).notes.size();
		for (int j = 0; j < max_note_count;)
		{
			std::pair<std::string, int> input_pair = { definitions[i].name, definitions[i].notes[j/offset]};
			notes_map[j].push_back(input_pair);
			j += offset;
		}
		
	}

	add_notes(notes_map);
}

void timerengine::run(){
	rpc::client client(l_addr, l_port);
	while (!quit) {
		//for that increment eg 1/16th beat
		std::vector<std::pair<std::string, int>> temp_list = notes_per_increment[note_counter];
		for (int i = 0; i < temp_list.size(); i++){
			printf("rpc call made\n");
			client.call("addnotes", temp_list.size(), temp_list.at(i));
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(q_period_milli));
		note_counter++;
		note_counter = note_counter % 8; //loop the counter continously for 16* 1/16th beats
	}
}



