#include "glitchinclude.h"

namespace glitchmedia
{
	stringstream execution_log;

	struct c_string_compare
	{
	    bool operator()(string a,string b) const 
	    {
	    	//cout << "wow" << a << endl << b << endl;
	    	//cout << a.length() << endl;
	    	//cout << b.length() << endl;
	    	//cout << (a.compare(b) == 0) << endl;

	        return !((a.compare(b) == 0) ? true : false);
	    }
	};

	std::map<string, corrupter_func_type, c_string_compare> file_extention_to_function_map;

	std::map<string, specific_FILENAME_corruption__ *, c_string_compare> func_map_obj_ptrs;

	parameters::parameters(int agression_var, int wild_card_seed_var, int frequency_var, int chunk_size_var): corruption_agression(agression_var), corruption_wild_card_seed(wild_card_seed_var), corruption_frequency(frequency_var), corruption_chunk_size(chunk_size_var){}

	parameters_image::parameters_image(int agression_var, int wild_card_seed_var, int frequency_var, int chunk_size_var): parameters(agression_var, wild_card_seed_var, frequency_var, chunk_size_var){}

	parameters_audio::parameters_audio(int agression_var, int wild_card_seed_var, int frequency_var, int chunk_size_var): parameters(agression_var, wild_card_seed_var, frequency_var, chunk_size_var){}

	parameters_video::parameters_video(int agression_var, int wild_card_seed_var, int frequency_var, int chunk_size_var): parameters(agression_var, wild_card_seed_var, frequency_var, chunk_size_var){}

	bool corrupt_image(char * dir_string, string new_name_string, parameters * params);

	bool corrupt_audio(char * dir_string, string new_name_string, parameters * params);

	bool corrupt_video(char * dir_string, string new_name_string, parameters * params);

	bool corrupt_image(char * dir_string, string new_name_string, int agression_var, int wild_card_seed_var, int frequency_var, int chunk_size_var, int c_type_var)
	{

		if(!(correct_input_value(agression_var) && correct_input_value(wild_card_seed_var) && correct_input_value(frequency_var) && correct_input_value(chunk_size_var) && correct_input_value(c_type_var)))
		{
			to_execution_log_stream("FATAL ERROR: Ending corruption");
			return false;
		}
		//return false;
		parameters_image* params = new parameters_image(agression_var, wild_card_seed_var, frequency_var, chunk_size_var);
		string file_type_str_ptr = get_type_of_file(dir_string);
		cout << file_type_str_ptr;
		corrupter_func_type func_ptr_to_use;
		if(file_type_str_ptr.empty())
		{
			to_execution_log_stream("FATAL ERROR: Ending corruption");
			return false;
		}
		FILE * file_from = open_file(dir_string);
		if(file_from == NULL)
		{
			to_execution_log_stream("FATAL ERROR: Ending corruption");
			return false;
		}
		cout << "got file from";
		FILE * file_to = create_dupe_file(dir_string, new_name_string, file_type_str_ptr);
		cout << file_to;
		if(file_to == NULL)
		{
			to_execution_log_stream("FATAL ERROR: Ending corruption");
			return false;
		}
		cout << "got file to";
		specific_JPEG_corruption JPEG_corruption_funcs (file_extention_to_function_map, func_map_obj_ptrs);
		cout << "made obj";
		//cout << file_extention_to_function_map.key_type << endl;
		cout << file_extention_to_function_map.size() << endl;
		//cout << file_type_str_ptr << endl;
		//return false;
		cout<< "fsdih";
		cout<< file_extention_to_function_map["PNG"]<<endl;
		//cout << file_type_str_ptr << endl;
		//return false;
		//func_ptr_to_use = ret_type_corrupt_func(file_type_str_ptr, file_extention_to_function_map);

		func_ptr_to_use = file_extention_to_function_map["JPG"];
		cout << func_ptr_to_use << endl;
		cout << "got func ptr";
		if(func_ptr_to_use == NULL)
		{
			to_execution_log_stream("FATAL ERROR: Ending corruption");
			return false;
		}
		cout << "corrupting";
		if(func_map_obj_ptrs["JPG"] == NULL)
		{
			to_execution_log_stream("FATAL ERROR: Ending corruption");
			return false;
		}
		//JPEG_corruption_funcs.corrupt_byte_string_FILENAME(file_from, file_to, &params);
		(func_map_obj_ptrs[file_type_str_ptr]->* func_ptr_to_use)(file_from, file_to, params);
		//delete[] file_type_str_ptr;\
		delete params;
		//free(new_name);

		return true;
	}

	bool corrupt_audio(char * dir_string, string new_name_string, int agression_var, int wild_card_seed_var, int frequency_var, int chunk_size_var, int c_type_var);

	bool corrupt_video(char * dir_string, string new_name_string, int agression_var, int wild_card_seed_var, int frequency_var, int chunk_size_var, int c_type_var);

	corrupter_func_type ret_type_corrupt_func(string file_type_string, map<string, corrupter_func_type, c_string_compare> & map_to_check)
	{
		if(map_to_check.find(file_type_string) != map_to_check.end())
			return map_to_check[file_type_string];
		else
			to_execution_log_stream("FAILURE: File type is not supported\nTry to convert the file to one of current compatable file types\n");
			return NULL;
	}

	bool correct_input_value(int & input_val)
	{
		input_val = abs(input_val);
		if(!(input_val > 0))
		{
			to_execution_log_stream("FAILURE: 0 is not a valid input.");
			return false;
		}
		return true;
	}

	string get_type_of_file(char * dir_string)
	{
		//cout << strlen(dir_string)<<endl;
		char current_char_scan = 0;
		//char * file_type =  new char [strlen(dir_string)]();
		string file_type;
		//char * file_type;
		bool dot_bool = false;
		int extention_length = 0;
		//cout<<extention_length<<endl;
		
		for(unsigned int index = (strlen(dir_string) - 1); index > 0; --index)
		{
			current_char_scan = dir_string[index];
			if(current_char_scan == '\\')
			{
				break;
			}
			if(current_char_scan == '.')
			{
				dot_bool = !dot_bool;
				break;
			}
			++extention_length;
			//file_type[strlen(dir_string) - (index)] = current_char_scan;
		}
		//cout << extention_length;
		if(!dot_bool)
		{
			to_execution_log_stream("FAILURE: File path @ : ");
			to_execution_log_stream(dir_string);
			to_execution_log_stream(" lacks file type.\nAdd a file extention to your file path.");
			//delete file_type;
			return NULL;
		}
		//for(unsigned int index_1 = 0; index_1 < (extention_length); ++index_1)
		//{
		//	file_type[index_1] = dir_string[(strlen(dir_string) - (extention_length)) + index_1];	
		//}
		file_type = string(dir_string).substr(strlen(dir_string) - (extention_length), extention_length);
		//file_type = new char[(strlen(dir_string) - (extention_length - 2))];
		//strcpy(file_type, file_type_whole);
		//cout << file_type;
		return file_type;
	}
	
	void corrupt_byte(uint8_t & byte_to_corrupt, parameters * params)
	{
		//byte_to_corrupt = 01;
		//cout<<params->corruption_wild_card_seed<<endl;
		byte_to_corrupt *= ((params->corruption_wild_card_seed) * (params->corruption_agression));
	}

	uint8_t corrupt_byte_singular(uint8_t byte_to_corrupt, parameters * params)
	{
		byte_to_corrupt *= ((params->corruption_wild_card_seed) * (params->corruption_agression));
		return byte_to_corrupt;
	}

	void corrupt_bytes(uint8_t * byte_chunk_to_corrupt, unsigned int current_chunk_size, parameters * params)
	{
		for(unsigned int index = 0; index < current_chunk_size; ++index)
		{
			corrupt_byte(byte_chunk_to_corrupt[index], params);
		}
	}

	FILE * create_dupe_file(char * dir_string, string new_name, string file_ext)
	{
		for(unsigned int index = 0; index < (new_name.length()); ++index)
		{
			//cout<<"dfs";
			if(new_name[index] == '.')
			{
				new_name[index] = '_';
			}
		}
		new_name = new_name.append(file_ext.insert(0,"."));
		cout << new_name;
		FILE * file_to_create = fopen(new_name.c_str(), "wb");
		cout << file_to_create;
		return file_to_create;
	}

	FILE * open_file(char * dir_string)
	{
		FILE * file_to_open = fopen(dir_string, "rb");
		if(file_to_open == NULL)
		{
			to_execution_log_stream("FAILURE: Failed to open file @ directory:");
			to_execution_log_stream(dir_string);
			to_execution_log_stream("\n Check to make sure file exists and check your file path \n");
		}
		return file_to_open;
	}

	void to_execution_log_stream(char * to_stream_string)
	{
		execution_log << to_stream_string;
		cout << to_stream_string;
	}

	void to_execution_log_stream(string to_stream_string)
	{
		execution_log << to_stream_string;
		cout << to_stream_string;
	}

	/*void to_execution_log_stream(int to_stream_string)
	{
		execution_log << to_stream_string;
		cout << to_stream_string;
	}*/

	int get_place(FILE * from_file, int place_in_file)
	{
		fseek(from_file, place_in_file, SEEK_SET);
		int byte_val = fgetc(from_file);
		fseek(from_file, place_in_file, SEEK_SET);
		return byte_val;
	}
	void put_place(FILE * to_file, int place_in_file, int input_val)
	{
		fseek(to_file, place_in_file, SEEK_SET);
		fputc(input_val, to_file);
		fseek(to_file, place_in_file, SEEK_SET);
	}

	specific_FILENAME_corruption__::specific_FILENAME_corruption__(){}

	specific_JPEG_corruption::specific_JPEG_corruption(map<string, corrupter_func_type, c_string_compare> & func_map_to_append, map<string, specific_FILENAME_corruption__ *, c_string_compare> & obj_map_to_append)
	{
		corrupter_func_type this_corrupt_func = (corrupter_func_type)&specific_JPEG_corruption::corrupt_byte_string_FILENAME;
		func_map_to_append.insert(std::pair<string, corrupter_func_type>("JPG", this_corrupt_func));
		obj_map_to_append.insert(std::pair<string, specific_FILENAME_corruption__ *>("JPG", this));
	}

	void specific_JPEG_corruption::corrupt_byte_string_FILENAME(FILE * file_from, FILE * file_to, parameters * params)
	{
		fseek(file_from, 0, SEEK_END);
		int file_size = ftell(file_from);
		fseek(file_from, 0, SEEK_SET);
		uint8_t * byte_chunk = new uint8_t [params->corruption_chunk_size]();
		uint8_t marker_byte_list[] = {219,216,192,194,196,221,208,209,210,211,212,213,214,215,254,217,224,225,226,227,228,229,230,231,232,233};
		unsigned int file_byte_index = 0;
		unsigned int current_chunk_size = 0;
		bool hit_next_marker = false;
		while((file_byte_index < file_size))
		{
			if((get_place(file_from, file_byte_index) == 255))
			{
				//cout<<"fsdiuhf;lsdajf"<<endl;
				for(unsigned int index_3 = 0; index_3 < sizeof marker_byte_list; ++index_3)
				{
					//cout << "test_3";
					if((uint8_t)(get_place(file_from, file_byte_index + 1)) == (marker_byte_list[index_3]))
					{
						cout << " " << hex << (unsigned int)marker_byte_list[index_3];
						//cout << "fsdlifh";
						//hit_next_marker = true;
						//--current_chunk_size;
						//--file_byte_index;
						//break;
					}
					//get_place(file_from, file_byte_index);
				}
			}
			++file_byte_index;
		}

		/*
		fseek(file_from, 0, SEEK_END);
		int file_size = ftell(file_from);
		fseek(file_from, 0, SEEK_SET);
		uint8_t marker_byte_list[] = {219,216,192,194,196,221,208.209,210,211,212,213,214,215,254,217,224,225,226,227,228,229,230,231,232,233};
		unsigned int file_byte_index = 0;
		bool hit_next_marker = false;
		while((file_byte_index < file_size))
		{
			cout << "t0";
			put_place(file_to, file_byte_index, get_place(file_from, file_byte_index));
			if(get_place(file_from, file_byte_index + 1) == 218)
			{
				for(unsigned int index_5 = 0; index_5 < 22; ++index_5)
				{
					for(unsigned int index_5 = 0; index_5 < 22; ++index_5)
					{
						put_place(file_to, file_byte_index, get_place(file_from, file_byte_index));
						++file_byte_index;
					}
					while(!hit_next_marker)
					{
						cout <<  "t1";
						for(unsigned int index = 0; index < params->corruption_chunk_size; ++index)
						{
							if((get_place(file_from, file_byte_index) == 255))
							{
								for(unsigned int index_3 = 0; index_3 < sizeof marker_byte_list; ++index_3)
								{
									if((uint8_t)(get_place(file_from, file_byte_index + 1)) == (marker_byte_list[index_3]))
									{
										hit_next_marker = true;
										break;
									}
								}
							}
							if(hit_next_marker){break;}
							put_place(file_to, file_byte_index, corrupt_byte_singular(get_place(file_from, file_byte_index), params));
							++file_byte_index;
						}
						if(hit_next_marker){break;}
						for(unsigned int index_2 = 0; index_2 < params->corruption_frequency; ++index_2)
						{
							if((get_place(file_from, file_byte_index) == 255))
							{
								for(unsigned int index_3 = 0; index_3 < sizeof marker_byte_list; ++index_3)
								{
									if((uint8_t)(get_place(file_from, file_byte_index + 1)) == (marker_byte_list[index_3]))
									{
										hit_next_marker = true;
										break;
									}
								}
							}
							if(hit_next_marker){break;}
							put_place(file_to, file_byte_index, get_place(file_from, file_byte_index));
							++file_byte_index;
						}
						if(hit_next_marker){break;}
					}
					hit_next_marker = false;
				}
			}
			++file_byte_index;
		}
		*/
		
		//cout << "test_6";
		/*fseek(file_from, 0, SEEK_END);
		int file_size = ftell(file_from);
		//cout<< "size " << file_size;
		fseek(file_from, 0, SEEK_SET);
		uint8_t * byte_chunk = new uint8_t [params->corruption_chunk_size]();
		uint8_t marker_byte_list[] = {219,216,192,194,196,221,208,209,210,211,212,213,214,215,254,217,224,225,226,227,228,229,230,231,232,233};
		unsigned int file_byte_index = 0;
		unsigned int current_chunk_size = 0;
		bool hit_next_marker = false;
		//while((fgetc(file_from) != EOF) && (!hit_next_marker))
		while((file_byte_index < file_size))
		{
			
			//cout << " test_1 ";
			//cout << file_byte_index<<" ";
			//cout << fgetc(file_from);
			if((get_place(file_from, file_byte_index) == 255))
			{
				//cout<<"fsdiuhf;lsdajf"<<endl;
				for(unsigned int index_3 = 0; index_3 < sizeof marker_byte_list; ++index_3)
				{
					//cout << "test_3";
					if((uint8_t)(get_place(file_from, file_byte_index + 1)) == (marker_byte_list[index_3]))
					{
						cout << " " << hex << (unsigned int)marker_byte_list[index_3];
						//cout << "fsdlifh";
						//hit_next_marker = true;
						//--current_chunk_size;
						//--file_byte_index;
						//break;
					}
					get_place(file_from, file_byte_index);
				}
			}
			put_place(file_to, file_byte_index, get_place(file_from, file_byte_index));
			if((get_place(file_from, file_byte_index) == 255))
			{
				if(get_place(file_from, file_byte_index + 1) == 218)
				{
					//cout << " da";
					
					cout << " " << 218;*/
					/*for(unsigned int index_5 = 0; index_5 < 22; ++index_5)
					{
						put_place(file_to, file_byte_index, get_place(file_from, file_byte_index));
						++file_byte_index;
					}
					while(!hit_next_marker)
					{
						//cout << "test_2 " << endl;
						//cout << file_byte_index<<" ";
						//cout << get_place(file_from, file_byte_index);
						current_chunk_size = 0;
						for(unsigned int index = 0; index < params->corruption_chunk_size; ++index)
						{
							//cout << "test_3" << endl;
							//cout << file_byte_index << endl;
							//if((fgetc(file_from) == EOF)){break;}
							if((get_place(file_from, file_byte_index) == 255))
							{
								//cout<<"fsdiuhf;lsdajf"<<endl;
								for(unsigned int index_3 = 0; index_3 < sizeof marker_byte_list; ++index_3)
								{
									//cout << "test_3";
									if((uint8_t)(get_place(file_from, file_byte_index + 1)) == (marker_byte_list[index_3]))
									{
										//cout << "fsdlifh";
										cout << " " << hex << (unsigned int)marker_byte_list[index_3];
										hit_next_marker = true;
										--current_chunk_size;
										--file_byte_index;
										break;
									}
									get_place(file_from, file_byte_index);
								}
							}
							if(hit_next_marker){break;}
							byte_chunk[index] = get_place(file_from, file_byte_index);
							++current_chunk_size;
							++file_byte_index;
						}
						//cout<<current_chunk_size<<endl;
						corrupt_bytes(byte_chunk, current_chunk_size, params);
						for(unsigned int index_1 = 0; index_1 < (current_chunk_size); ++index_1)
						{
							//cout << "test_4" << endl;
							//cout << index_1 << endl;
							put_place(file_to, ((file_byte_index - current_chunk_size) + (index_1)) , byte_chunk[index_1]);
						}
						if(hit_next_marker){break;}
						//++file_byte_index;
						for(unsigned int index_2 = 0; index_2 < params->corruption_frequency; ++index_2)
						{
							//cout << "test_5" << endl;
							//cout << file_byte_index << endl;
							put_place(file_to, file_byte_index, get_place(file_from, file_byte_index));
							if((get_place(file_from, file_byte_index) == 255))
							{
								//cout<<"fsdiuhf;lsdajf"<<endl;
								for(unsigned int index_3 = 0; index_3 < sizeof marker_byte_list; ++index_3)
								{
									//cout << "test_3";
									if((uint8_t)(get_place(file_from, file_byte_index + 1)) == (marker_byte_list[index_3]))
									{
										//cout << "fsdlifh";
										cout << " " << hex << (unsigned int)marker_byte_list[index_3];
										hit_next_marker = true;
										break;
									}
									get_place(file_from, file_byte_index);
								}
							}
							if(hit_next_marker){break;}
							++file_byte_index;
						}
						if(hit_next_marker){break;}
					}*/
				/*}
			}
			hit_next_marker = false;
			++file_byte_index;

		}
		cout << "end of file";
		cout << hit_next_marker;
		*/
	}

	specific_PNG_corruption::specific_PNG_corruption(map<string, corrupter_func_type, c_string_compare> & func_map_to_append, map<string, specific_FILENAME_corruption__ *, c_string_compare> obj_map_to_append)
	{
		corrupter_func_type this_corrupt_func = (corrupter_func_type)&specific_PNG_corruption::corrupt_byte_string_FILENAME;
		func_map_to_append.insert(std::pair<string, corrupter_func_type>("PNG", this_corrupt_func));
		obj_map_to_append.insert(std::pair<string, specific_FILENAME_corruption__ *>("PNG", this));
	}

	void specific_PNG_corruption::corrupt_byte_string_FILENAME(FILE * file_from, FILE * file_to, parameters * params){}

	specific_MP3_corruption::specific_MP3_corruption(map<string, corrupter_func_type, c_string_compare> & func_map_to_append, map<string, specific_FILENAME_corruption__ *, c_string_compare> obj_map_to_append)
	{
		corrupter_func_type this_corrupt_func = (corrupter_func_type)&specific_MP3_corruption::corrupt_byte_string_FILENAME;
		func_map_to_append.insert(std::pair<string, corrupter_func_type>("MP3", this_corrupt_func));
		obj_map_to_append.insert(std::pair<string, specific_FILENAME_corruption__ *>("MP3", this));
	}

	void specific_MP3_corruption::corrupt_byte_string_FILENAME(FILE * file_from, FILE * file_to, parameters * params){}

}