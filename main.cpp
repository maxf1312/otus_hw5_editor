#include <iostream>
// #include <map>
// #include <string>

#include "vers.h"
#include "editor.h"
#include "utils.h"

using namespace std::literals::string_literals;

int main(int, char **)
{
	constexpr const char *const doc_file_nm = "./test_doc.txt";
	using namespace otus_hw5;
	bool stop{};
	do
	{
		try
		{
			auto &editor = the_editor();
			print_prompt(std::cout);
			char cmd{};
			std::cin >> cmd;
			if (!std::cin)
				break;

			switch (std::toupper(cmd))
			{
			default:
				break;
			case 'A': // A - добавить фигуру в документ
			{
				editor.curr_doc()->add_shape(editor.create_shape(IShape::ShapeTypes::Point));
				break;
			}

			case 'N': // N - новый документ
			{
				auto &doc = editor.curr_doc();
				doc->as_subject().set_changed(true);
				doc->as_subject().notify_all();
				break;
			}

			case 'R': // R - загрузить документ
			{
				auto doc_stg = editor.create_docstg(IEditor::DocStorageTypes::File,
													IEditor::IOBase_t::in | IEditor::IOBase_t::binary,
													doc_file_nm);
				editor.import_doc_from(editor.curr_doc(), doc_stg, editor.create_docserializer(IEditor::DocFormatTypes::Text));
				break;
			}

			case 'S': // S - сохранить документ
			{
				auto doc_stg = editor.create_docstg(IEditor::DocStorageTypes::File,
													IEditor::IOBase_t::out | IEditor::IOBase_t::binary | IEditor::IOBase_t::trunc,
													doc_file_nm);
				editor.export_doc_to(editor.curr_doc(), doc_stg, editor.create_docserializer(IEditor::DocFormatTypes::Text));
				break;
			}

			case 'D': // D - удалить фигуру из документа
				if (size_t N = editor.curr_doc()->shapes().count())
					editor.curr_doc()->shapes().remove(N - 1);
				break;

			case 'M': // M - передвинуть фигуру
				break;

			case 'Q': // Q - Выход
				stop = true;
				break;
			}
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}

	} while (!stop && std::cin);
	return 0;
}
