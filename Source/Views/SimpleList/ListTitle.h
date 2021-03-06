#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <fontaudio/fontaudio.h>
#include "FontData.h"
#include "LabelColour1LookAndFeel.h"

class ListTitle
    : public juce::Component
{

public:

    enum class IconType
    {

        FONT_AUDIO = 0,
        FONT_AWESOME = 1,
        NONE = 2

    };

    ListTitle(const juce::String& titleString, IconType type, const juce::String& iconString);
    ~ListTitle();

    void paint(juce::Graphics& g) override;
    void resized() override;



private:

    SharedResourcePointer<fontaudio::IconHelper> sharedFontAudio;

    Typeface::Ptr fontAwesomeTypeface = juce::Typeface::createSystemTypefaceFor(FontData::FontAwesome5FreeSolid900_otf, FontData::FontAwesome5FreeSolid900_otfSize);
    juce::Font fontAwesomeFont = juce::Font(fontAwesomeTypeface);

    juce::String title;
    IconType iconType;
    juce::String icon;
    juce::Label titleLabel;
    juce::Label iconLabel;

    LabelColour1LookAndFeel labelColour1LookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ListTitle)

};



