namespace app_models
{

    juce::ValueTree StateBuilder::createThemes() {

        ThemeReader themeReader;
        return themeReader.getThemes();

    }

    juce::ValueTree StateBuilder::createInitialStateTree() {

        juce::ValueTree state(IDs::APP_STATE);
        state.addChild(createThemes(), -1, nullptr);
        return state;

    }

}


