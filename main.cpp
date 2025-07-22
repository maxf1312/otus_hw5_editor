#include <iostream>
//#include <map>
//#include <string>

#include "vers.h"
#include "editor.h"
#include "utils.h"

using namespace std::literals::string_literals;

/*
           << '\t' << "" << endl
           << '\t' << "" << endl
           << '\t' << "" << endl
           << '\t' << "A - добавить фигуру в документ" << endl
           << '\t' << "" << endl
           << '\t' << "" << endl */
int main(int, char **) 
{
	using namespace otus_hw5;
	try
	{
		auto& editor = the_editor();
		bool stop{};
		do{
			print_prompt(std::cout);
			char cmd{};
			std::cin >> cmd;
			if( !std::cin ) break;

			switch ( std::toupper(cmd) )
			{
			default:
				break;
			case 'A': // A - добавить фигуру в документ
				break;
			case 'N': // N - новый документ
			{
				auto& doc = editor.create_new_doc(the_config());
				auto& view = editor.create_new_view(the_config());
				doc->add_view(view);
				doc->as_subject().set_changed(true);
				doc->as_subject().notify_all();
				break;
			}

			case 'R': // R - загрузить документ
				break;
			case 'S': // S - сохранить документ
				break;
			case 'D': // D - удалить фигуру из документа
				break;
			case 'M': // M - передвинуть фигуру
				break;
			case 'Q': // Q - Выход
				stop = true;	
				break;
			}

		} while (!stop && std::cin);
	}	
	catch(const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
