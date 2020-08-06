#pragma once
#include <tracktion_engine/tracktion_engine.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include "TrackPluginsListView.h"
#include "SplitListView.h"
#include "PluginTreeGroup.h"
#include "PluginView.h"

class CurrentTrackView
    : public juce::TabbedComponent,
      public juce::ApplicationCommandTarget
{

public:
    explicit CurrentTrackView(tracktion_engine::AudioTrack* t, juce::ApplicationCommandManager& cm);

    void paint(juce::Graphics&) override;
    void resized() override;

    ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands(juce::Array<juce::CommandID>& commands) override;
    void getCommandInfo (juce::CommandID commandID, juce::ApplicationCommandInfo& result) override;
    bool perform (const InvocationInfo &info) override;

    void showPlugin();

private:
    tracktion_engine::AudioTrack* track;
    juce::ApplicationCommandManager& commandManager;

    PluginTreeGroup instrumentsPluginTreeGroup;
    PluginTreeGroup effectsPluginTreeGroup;

    std::unique_ptr<SplitListView> instrumentsListView;
    std::unique_ptr<SplitListView> effectsListView;
    std::unique_ptr<TrackPluginsListView> trackPluginsListView;
    std::unique_ptr<PluginView> pluginView;

    juce::String instrumentsListTabName = "INSTRUMENTS";
    juce::String effectsListTabName = "EFFECTS";
    juce::String trackPluginsListTabName = "TRACK_PLUGINS";
    juce::String pluginViewTabName = "PLUGIN";

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CurrentTrackView);

};
