#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <tracktion_engine/tracktion_engine.h>
#include "SplitListBoxModel.h"
#include "PluginTreeGroup.h"
#include "MidiCommandManager.h"
class SplitListView
        : public juce::Component,
          public MidiCommandManager::Listener
{
public:

    enum ColourIds
    {
        leftSelectedBackgroundColourId = 0x1003281,
        rightSelectedBackgroundColourId = 0x1003282
    };

    SplitListView(tracktion_engine::AudioTrack* t, PluginTreeGroup& pluginGroup, MidiCommandManager& mcm);
    ~SplitListView();

    void paint(juce::Graphics&) override;
    void resized() override;

    void lookAndFeelChanged() override;

    void encoder1Increased() override;
    void encoder1Decreased() override;
    void encoder2Increased() override;
    void encoder2Decreased() override;
    void encoder2ButtonReleased() override;


private:

    tracktion_engine::AudioTrack* track;
    MidiCommandManager& midiCommandManager;
    PluginTreeGroup& pluginTreeGroup;
    juce::ListBox leftListBox;
    std::unique_ptr<SplitListBoxModel> leftListModel;
    juce::ListBox rightListBox;
    std::unique_ptr<SplitListBoxModel> rightListModel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SplitListView)
};

