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
