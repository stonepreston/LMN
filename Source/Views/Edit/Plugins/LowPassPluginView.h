#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <app_view_models/app_view_models.h>
#include <app_services/app_services.h>
#include "LabeledKnob.h"
#include "AppLookAndFeel.h"

class LowPassPluginView
    : public juce::Component,
      public app_services::MidiCommandManager::Listener,
      public app_view_models::LowPassPluginViewModel::Listener
{

public:

    LowPassPluginView(tracktion_engine::LowPassPlugin* p, app_services::MidiCommandManager& mcm);

    ~LowPassPluginView();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void encoder1Increased() override;
    void encoder1Decreased() override;

    void encoder2Increased() override;
    void encoder2Decreased() override;

    void parametersChanged() override;

private:

    tracktion_engine::LowPassPlugin* plugin;
    app_view_models::LowPassPluginViewModel viewModel;
    app_services::MidiCommandManager& midiCommandManager;

    juce::Label titleLabel;
    juce::Label modeLabel;
    LabeledKnob frequencyKnob;

    juce::OwnedArray<LabeledKnob> knobs;

    AppLookAndFeel appLookAndFeel;

    juce::Grid grid;
    void gridSetup();


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LowPassPluginView)


};


