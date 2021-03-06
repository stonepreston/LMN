#pragma once
#include <tracktion_engine/tracktion_engine.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <app_services/app_services.h>
#include <app_view_models/app_view_models.h>
#include <app_navigation/app_navigation.h>
#include "TracksView.h"
#include "TempoSettingsView.h"
#include "MixerView.h"
#include "SettingsView.h"
#include "OctaveDisplayComponent.h"
#include "MasterGainDisplay.h"

class EditTabBarView
    : public juce::TabbedComponent,
      public app_services::MidiCommandManager::Listener,
      public app_view_models::ItemListState::Listener,
      juce::Timer
{
public:
    EditTabBarView(tracktion_engine::Edit& e, app_services::MidiCommandManager& mcm);
    ~EditTabBarView();
    void paint(juce::Graphics&) override;
    void resized() override;

    void tracksButtonReleased() override;
    void tempoSettingsButtonReleased() override;
    void mixerButtonReleased() override;
    void settingsButtonReleased() override;
    void pluginsButtonReleased() override;
    void modifiersButtonReleased() override;
    void sequencersButtonReleased() override;
    void octaveChanged(int newOctave) override;
    void encoder9Increased() override;
    void encoder9Decreased() override;

    // Used to reset the modifiers list when ever a plugin gets deleted
    void resetModifiersTab();

    // ItemListState listener methods
    void selectedIndexChanged(int newIndex) override;

private:
    tracktion_engine::Edit& edit;
    app_services::MidiCommandManager& midiCommandManager;
    juce::String tracksTabName = "TRACKS";
    juce::String tempoSettingsTabName = "TEMPO_SETTINGS";
    juce::String mixerTabName = "MIXER";
    juce::String pluginsTabName = "PLUGINS";
    juce::String modifiersTabName = "MODIFIERS";
    juce::String sequencersTabName = "SEQUENCERS";
    juce::String settingsTabName = "SETTINGS";

    OctaveDisplayComponent octaveDisplayComponent;
    MasterGainDisplay masterGainDisplay;

    void timerCallback() override;



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EditTabBarView)
};

