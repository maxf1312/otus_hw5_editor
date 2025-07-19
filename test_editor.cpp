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

    doc->subscribe(view);

    view = editor.create_new_view(the_config());
    EXPECT_EQ( editor.views().count(), 2 );

    doc->add_view(view);

    doc->set_changed(true);
    doc->notify_all();
    //doc->unsubscribe(view);
}
