#include <app_models/app_models.h>
#include <gtest/gtest.h>

namespace AppModelsTests {

    TEST(StateBuilderTest, createInitialStateTree)
    {

        juce::ValueTree stateTree = app_models::StateBuilder::createInitialStateTree();
        EXPECT_EQ(stateTree.isValid(), true);
        EXPECT_EQ(stateTree.getType(), app_models::IDs::APP_STATE);
        EXPECT_EQ(stateTree.getNumChildren(), 1);
        EXPECT_EQ(stateTree.getChild(0).isValid(), true);
        EXPECT_EQ(stateTree.getChild(0).getType(), app_models::IDs::THEMES);

    }

}