#include <gtest/gtest.h>
#include <sstream>
#include <list>
#include <tuple>
#ifndef __PRETTY_FUNCTION__
#include "pretty.h"
#endif
#include "editor.h"


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

using namespace std::literals::string_literals;
using namespace otus_hw5;

TEST(test_editor, test_create)
{
    auto& editor = the_editor();
    EXPECT_EQ( editor.docs().count(), 0 );
    EXPECT_EQ( editor.views().count(), 0 );
    
    auto doc = editor.create_new_doc(the_config());
    EXPECT_EQ( editor.docs().count(), 1 );

    auto view = editor.create_new_view(the_config());
    EXPECT_EQ( editor.views().count(), 1 );

    editor.docs().remove(0);
    EXPECT_EQ( editor.docs().count(), 0 );

    editor.views().remove(0);
    EXPECT_EQ( editor.views().count(), 0 );
}

TEST(test_editor, test_doc_view)
{
    auto& editor = the_editor();
    EXPECT_EQ( editor.docs().count(), 0 );
    EXPECT_EQ( editor.views().count(), 0 );
    
    auto doc = editor.create_new_doc(the_config());
    EXPECT_EQ( editor.docs().count(), 1 );

    auto view = editor.create_new_view(the_config());
    EXPECT_EQ( editor.views().count(), 1 );

    doc->as_subject().subscribe(view);

    view = editor.create_new_view(the_config());
    EXPECT_EQ( editor.views().count(), 2 );

    doc->add_view(view);

    doc->as_subject().set_changed(true);
    doc->as_subject().notify_all();
    doc->as_subject().unsubscribe(view);

    editor.views().remove_all();
    EXPECT_EQ( editor.views().count(), 0 );    

    editor.docs().remove_all();
    EXPECT_EQ( editor.docs().count(), 0 );
}

TEST(test_editor, test_doc_shapes)
{
    auto& editor = the_editor();
    EXPECT_EQ( editor.docs().count(), 0 );
    EXPECT_EQ( editor.views().count(), 0 );
    
    auto doc = editor.create_new_doc(the_config());
    EXPECT_EQ( editor.docs().count(), 1 );

    auto view = editor.create_new_view(the_config());
    EXPECT_EQ( editor.views().count(), 1 );

    doc->as_subject().subscribe(view);

    auto shp = editor.create_shape(IEditor::ShapeTypes::Point);
    doc->add_shape(std::move(shp));
    doc->add_shape( editor.create_shape(IEditor::ShapeTypes::Line) );
    EXPECT_EQ( doc->shapes().count(), 2 );


    view = editor.create_new_view(the_config());
    EXPECT_EQ( editor.views().count(), 2 );

    doc->add_view(view);

    doc->add_shape( editor.create_shape(IEditor::ShapeTypes::Square) );
    doc->add_shape( editor.create_shape(IEditor::ShapeTypes::Rectangle) );
    doc->add_shape( editor.create_shape(IEditor::ShapeTypes::Circle) );
    doc->add_shape( editor.create_shape(IEditor::ShapeTypes::Ellipse) );
  
    doc->as_subject().set_changed(true);
    doc->as_subject().notify_all();
    editor.views().remove_all();
    EXPECT_EQ( editor.views().count(), 0 );    

    editor.docs().remove_all();
    EXPECT_EQ( editor.docs().count(), 0 );
}

TEST(test_editor, test_doc_stg)
{
    auto& editor = the_editor();
    EXPECT_EQ( editor.docs().count(), 0 );
    EXPECT_EQ( editor.views().count(), 0 );
    
    auto console_stg = editor.create_docstg(IEditor::DocStorageTypes::Console);
    auto file_stg = editor.create_docstg(IEditor::DocStorageTypes::File, 
                                         IDocStorage::IOBase_t::in|IDocStorage::IOBase_t::out|
                                         IDocStorage::IOBase_t::binary|IDocStorage::IOBase_t::trunc,
                                         "./doc_file.txt");
    file_stg->outputstream() << "Test" << std::endl;
    EXPECT_TRUE(file_stg->outputstream());
    std::string s;
    file_stg->inputstream().seekg(0) >> s;
    EXPECT_EQ(s, "Test");
}

TEST(test_editor, test_doc_export)
{
    auto& editor = the_editor();
    EXPECT_EQ( editor.docs().count(), 0 );
    EXPECT_EQ( editor.views().count(), 0 );
    
    auto doc = editor.create_new_doc(the_config());
    EXPECT_EQ( editor.docs().count(), 1 );

    auto view = editor.create_new_view(the_config());
    EXPECT_EQ( editor.views().count(), 1 );
    doc->add_view(view);

    doc->add_shape( editor.create_shape(IEditor::ShapeTypes::Point) )->color(0x00ffee80).center(0, 10);
    doc->add_shape( editor.create_shape(IEditor::ShapeTypes::Line) )->color(0x00ffe081).center(10, 10).line_width(2);
    doc->add_shape( editor.create_shape(IEditor::ShapeTypes::Square) )->color(0x000f0e82).center(20, 10).line_width(3);
    doc->add_shape( editor.create_shape(IEditor::ShapeTypes::Rectangle) )->color(0x001fee83).center(20, 20).line_width(4);
    doc->add_shape( editor.create_shape(IEditor::ShapeTypes::Circle) )->color(0x00f1ef84).center(20, 30).line_width(7);
    doc->add_shape( editor.create_shape(IEditor::ShapeTypes::Ellipse) )->color(0x00ef1e85).center(10, 50).line_width(10);

    EXPECT_EQ( doc->shapes().count(), 6 );

    auto console_stg = editor.create_docstg(IEditor::DocStorageTypes::Console);
    auto file_stg = editor.create_docstg(IEditor::DocStorageTypes::File, 
                                         IDocStorage::IOBase_t::in|IDocStorage::IOBase_t::out|
                                         IDocStorage::IOBase_t::binary|IDocStorage::IOBase_t::trunc,
                                         "./doc_file.txt");

    auto text_serializer = editor.create_docserializer(IEditor::DocFormatTypes::Text);

    editor.export_doc_to(doc, file_stg, text_serializer);
    editor.views().remove_all();
    EXPECT_EQ( editor.views().count(), 0 );    

    editor.docs().remove_all();
    EXPECT_EQ( editor.docs().count(), 0 );    
}

TEST(test_editor, test_doc_import)
{
    auto& editor = the_editor();
    EXPECT_EQ( editor.docs().count(), 0 );
    EXPECT_EQ( editor.views().count(), 0 );
    
    auto doc = editor.create_new_doc(the_config());
    EXPECT_EQ( editor.docs().count(), 1 );

    auto view = editor.create_new_view(the_config());
    EXPECT_EQ( editor.views().count(), 1 );
    doc->add_view(view);

    doc->add_shape( editor.create_shape(IEditor::ShapeTypes::Point) );
    doc->add_shape( editor.create_shape(IEditor::ShapeTypes::Line) );
    doc->add_shape( editor.create_shape(IEditor::ShapeTypes::Square) );
    doc->add_shape( editor.create_shape(IEditor::ShapeTypes::Rectangle) );
    doc->add_shape( editor.create_shape(IEditor::ShapeTypes::Circle) );

    EXPECT_EQ( doc->shapes().count(), 5 );

    auto console_stg = editor.create_docstg(IEditor::DocStorageTypes::Console);
    auto file_stg = editor.create_docstg(IEditor::DocStorageTypes::File, 
                                         IDocStorage::IOBase_t::in|IDocStorage::IOBase_t::out|
                                         IDocStorage::IOBase_t::binary,
                                         "./doc_file.txt");

    auto text_serializer = editor.create_docserializer(IEditor::DocFormatTypes::Text);
    editor.import_doc_from(doc, file_stg, text_serializer);
    EXPECT_EQ( doc->shapes().count(), 6 );

    doc->export_to(console_stg, text_serializer);

    editor.views().remove_all();
    EXPECT_EQ( editor.views().count(), 0 );    

    editor.docs().remove_all();
    EXPECT_EQ( editor.docs().count(), 0 );    
}
