#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <tracktion_engine/tracktion_engine.h>
#include "AppLookAndFeel.h"

class LevelMeterComponent
    : public juce::Component,
      public juce::Timer
{

public:

    explicit LevelMeterComponent(tracktion_engine::LevelMeasurer& lm);
    ~LevelMeterComponent();

    void paint(juce::Graphics& g) override;

    void timerCallback();


private:

    // set the range of the meter in dB
    const double RANGEMAXdB{ 3.0 };//+3dB
    const double RANGEMINdB{ -30.0 };//-30dB

    double currentLeveldB{ 0.0 };
    double prevLeveldB{ 0.0 };

    tracktion_engine::LevelMeasurer& levelMeasurer;
    tracktion_engine::LevelMeasurer::Client levelClient;

    AppLookAndFeel appLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LevelMeterComponent)

};



