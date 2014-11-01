#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <sstream>
#include <map>
#include <utility>
#if defined(_WIN32)
#include <conio.h>
#else
#include <curses.h>
#endif
#include <string.h>
#include <stdlib.h>
#include <cmath>
#include <iomanip>

#define SYS_DIR_SLASH "\\"

using namespace std;
namespace glitchmedia
{
	struct c_string_compare;

	extern stringstream execution_log;


	class parameters
	{
	public:
		int corruption_agression;
		int corruption_wild_card_seed;
		int corruption_frequency;
		int corruption_chunk_size;
		int corruption_c_type;
	protected:
		parameters(int agression_var, int wild_card_seed_var, int frequency_var,int chunk_size_var);
	};

	class parameters_image: public parameters
	{
	public:
		parameters_image(int agression_var, int wild_card_seed_var, int frequency_var,int chunk_size_var);
	};

	class parameters_audio: public parameters
	{
	public:
		parameters_audio(int agression_var, int wild_card_seed_var, int frequency_var,int chunk_size_var);
	};

	class parameters_video: public parameters
	{
	public:
		parameters_video(int agression_var, int wild_card_seed_var, int frequency_var,int chunk_size_var);
	};

	///////////////////////////////////////////
	//										 //
	//   CORRUPTION USAGE FUNCTION CLASSES   //
	//										 //
	//										 //
	//	  FOR USE IN MAIN CORRUPTION FUNCS   //
	//										 //
	///////////////////////////////////////////
	//DEPTH DESCRIPTION: These are the default available types of files corruptable with this program. 
	//The OO structuring makes things easier to impliment a system with DLLs with more functions for corrupting.

	class specific_FILENAME_corruption__
	{	
	protected:
		char * file_label;
		virtual void corrupt_byte_string_FILENAME(FILE * file_from, FILE * file_to, parameters * params) = 0;
		specific_FILENAME_corruption__();				//MNEED: may need
	};

	class specific_JPEG_corruption: public specific_FILENAME_corruption__
	{
	public:
		virtual void corrupt_byte_string_FILENAME(FILE * file_from, FILE * file_to, parameters * params);
		specific_JPEG_corruption(map<string, void (specific_FILENAME_corruption__::* )(FILE *, FILE *, parameters *), c_string_compare> & map_to_append, map<string, specific_FILENAME_corruption__ *, c_string_compare> & obj_map_to_append);
	};

	class specific_PNG_corruption: public specific_FILENAME_corruption__
	{
	public:
		virtual void corrupt_byte_string_FILENAME(FILE * file_from, FILE * file_to, parameters * params);
		specific_PNG_corruption(map<string, void (specific_FILENAME_corruption__::* )(FILE *, FILE *, parameters *), c_string_compare> & map_to_append, map<string, specific_FILENAME_corruption__ *, c_string_compare> obj_map_to_append);
	};

	class specific_MP3_corruption: public specific_FILENAME_corruption__
	{
	public:
		virtual void corrupt_byte_string_FILENAME(FILE * file_from, FILE * file_to, parameters * params);
		specific_MP3_corruption(map<string, void (specific_FILENAME_corruption__::* )(FILE *, FILE *, parameters *), c_string_compare> & map_to_append, map<string, specific_FILENAME_corruption__ *, c_string_compare> obj_map_to_append);
	};

	typedef void (specific_FILENAME_corruption__::* corrupter_func_type)(FILE *, FILE *, parameters *);

	extern std::map<string, corrupter_func_type, c_string_compare> file_extention_to_function_map;

	extern std::map<string, specific_FILENAME_corruption__ *, c_string_compare> func_map_obj_ptrs;

	///////////////////////////////////////////
	//										 //
	//		   MAIN USAGE FUNCTIONS          //
	//										 //
	//										 //
	//	    FOR YOUR CONVENIENT USE c:       //
	//										 //
	///////////////////////////////////////////

	bool corrupt_image(char * dir_string, string new_name_string, parameters * params);

	bool corrupt_audio(char * dir_string, string new_name_string, parameters * params);

	bool corrupt_video(char * dir_string, string new_name_string, parameters * params);


	//TODO: add overloaded versions of functions below with parameters as arguements
	bool corrupt_image(char * dir_string, string new_name_string, int agression_var, int wild_card_seed_var, int frequency_var, int chunk_size_var, int c_type_var);

	bool corrupt_audio(char * dir_string, string new_name_string, int agression_var, int wild_card_seed_var, int frequency_var, int chunk_size_var, int c_type_var);

	bool corrupt_video(char * dir_string, string new_name_string, int agression_var, int wild_card_seed_var, int frequency_var, int chunk_size_var, int c_type_var);



	/*
	MNEED: may need
	class corruption_usage_functions
	{
	public:
		void corrupt_byte(uint8_t & byte_to_corrupt, parameters * params);
		FILE * create_dupe_file(char * dir_string);
		MNEED: may be needed
		//void corrupt_byte_string_JPEG(FILE * file_from, FILE * file_to, parameters * params);
		//void corrupt_byte_string_PNG(FILE * file_from, FILE * file_to, parameters * params);
		//void corrupt_byte_string_MP3(FILE * file_from, FILE * file_to, parameters * params);
		FILE * open_file(char * dir_string);



	};
	COMMENT: I originally felt like treating the user like an idiot and making the only accessable functions the ones to corrupt the images.
	 But then I realized... you're an adult. Don't use these functions like an idiot.
	*/

	///////////////////////////////////////////
	//										 //
	//		 CORRUPTION USAGE FUNCTIONS      //
	//										 //
	//										 //
	//	  FOR USE IN MAIN CORRUPTION FUNCS   //
	//										 //
	///////////////////////////////////////////

	bool correct_input_value(int & input_val);

	string get_type_of_file(char * dir_string);

	corrupter_func_type ret_type_corrupt_func(string file_extention_string, map<string, corrupter_func_type, c_string_compare> & map_to_check);

	void corrupt_byte(uint8_t & byte_to_corrupt, parameters * params);

	void corrupt_bytes(uint8_t ** byte_chunk_to_corrupt, parameters * params);

	FILE * create_dupe_file(char * dir_string, string new_name, string file_ext);

	FILE * open_file(char * dir_string);

	int get_place(FILE * from_file, int place_in_file);

	void put_place(FILE * from_file, int place_in_file, int input_val);

	///////////////////////////////////////////
	//										 //
	// DLL FILE COMPATABILITY IMPLIMENTATION //
	//										 //
	//										 //
	//ADDS FUNCTIONS FOR CORRUPTING FROM DLLS//
	//										 //
	///////////////////////////////////////////
	//TODO: add DLL functionality function
	//USER NOTICE: If you see this notice with no update below, this functionality has not been implimented.

	void map_append_dll_functions(map<string, corrupter_func_type, c_string_compare> & map_to_append);

	void to_execution_log_stream(char * to_stream_string);

	void to_execution_log_stream(string to_stream_string);

	//void to_execution_log_stream(int * to_stream_string);


}