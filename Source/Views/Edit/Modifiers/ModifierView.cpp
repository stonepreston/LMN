#include "ModifierView.h"
#include <app_navigation/app_navigation.h>

ModifierView::ModifierView(tracktion_engine::Modifier* mod, app_services::MidiCommandManager& mcm)
        : viewModel(std::make_unique<app_view_models::ModifierViewModel>(mod)),
          midiCommandManager(mcm)
{

    init();

}

ModifierView::ModifierView(tracktion_engine::LFOModifier* mod, app_services::MidiCommandManager& mcm)
        : viewModel(std::unique_ptr<app_view_models::ModifierViewModel>(std::make_unique<app_view_models::LFOModifierViewModel>(mod))),
          midiCommandManager(mcm)
{

    init();

}


void ModifierView::init()
{

    titleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .1, juce::Font::plain));
    titleLabel.setText(viewModel->getModifierName(), juce::dontSendNotification );
    titleLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(titleLabel);

    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    int numCols = 4;
    int numRows = 2;

    for (int i = 0; i < numRows; i++)
    {

        grid1.templateRows.add(Track(Fr(1)));
        grid2.templateRows.add(Track(Fr(1)));

    }


    for (int j = 0; j < numCols; j++)
    {

        grid1.templateColumns.add(Track(Fr(1)));
        grid2.templateColumns.add(Track(Fr(1)));

    }


    for (int i = 0; i < viewModel->getNumberOfParameters(); i++)
    {

        knobs.add(new LabeledKnob());
        knobs[i]->getLabel().setText(viewModel->getParameterName(i), juce::dontSendNotification);
        knobs[i]->getSlider().setRange(viewModel->getParameterRange(i), viewModel->getParameterInterval(i));

        if (i == 0 || i == 8)
        {

            knobs[i]->getSlider().setColour(juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour1);
            knobs[i]->getSlider().setColour(juce::Slider::thumbColourId, appLookAndFeel.colour1);

        }

        if (i == 1 || i == 9)
        {

            knobs[i]->getSlider().setColour(juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour2);
            knobs[i]->getSlider().setColour(juce::Slider::thumbColourId, appLookAndFeel.colour2);

        }

        if (i == 2 || i == 10)
        {

            knobs[i]->getSlider().setColour(juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour3);
            knobs[i]->getSlider().setColour(juce::Slider::thumbColourId, appLookAndFeel.colour3);

        }

        if (i == 3 || i == 11)
        {

            knobs[i]->getSlider().setColour(juce::Slider::rotarySliderFillColourId, appLookAndFeel.colour4);
            knobs[i]->getSlider().setColour(juce::Slider::thumbColourId, appLookAndFeel.colour4);

        }

        if (i < 8)
        {

            grid1.items.add(juce::GridItem(knobs[i]));
            addAndMakeVisible(knobs[i]);

        }
        else
        {
            grid2.items.add(juce::GridItem(knobs[i]));
            addChildComponent(knobs[i]);

        }

    }

    // now we need to fill out the remaining disabled knobs
    for (int i = viewModel->getNumberOfParameters(); i < 16; i++)
    {

        knobs.add(new LabeledKnob());
        knobs[i]->getLabel().setText("", juce::dontSendNotification);
        knobs[i]->getSlider().setEnabled(false);
        knobs[i]->getSlider().setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::grey);
        knobs[i]->getSlider().setColour(juce::Slider::thumbColourId, juce::Colours::grey);

        if (i < 8)
        {

            grid1.items.add(juce::GridItem(knobs[i]));
            addAndMakeVisible(knobs[i]);
        }
        else
        {

            grid2.items.add(juce::GridItem(knobs[i]));
            addChildComponent(knobs[i]);

        }

    }

    midiCommandManager.addListener(this);
    viewModel->addListener(this);

}


ModifierView::~ModifierView()
{

    midiCommandManager.removeListener(this);
    viewModel->removeListener(this);

}

void ModifierView::paint(juce::Graphics& g)
{

}

void ModifierView::resized()
{

    titleLabel.setFont(juce::Font(juce::Font::getDefaultMonospacedFontName(), getHeight() * .1, juce::Font::plain));
    titleLabel.setBounds(0, getHeight() * .1, getWidth(), getHeight() * .1);

    gridSetup();

}


void ModifierView::gridSetup()
{


    int widthPadding = getWidth() * .05;
    int heightPadding = getHeight() * .05;

    grid1.setGap(juce::Grid::Px(heightPadding));
    grid2.setGap(juce::Grid::Px(heightPadding));

    int startX = widthPadding;
    int startY = titleLabel.getY() + titleLabel.getHeight() + (heightPadding);
    int width = getWidth() - (2 * widthPadding);
    int height = (getHeight() - startY) - (heightPadding);

    juce::Rectangle<int> bounds(startX, startY, width, height);
    grid1.performLayout(bounds);
    grid2.performLayout(bounds);


}

void ModifierView::shiftButtonPressed()
{

    if (viewModel->getNumberOfParameters() > 8)
    {

        for (int i = 0; i < knobs.size(); i++)
        {

            if (i < 8)
                knobs[i]->setVisible(false);
            else
                knobs[i]->setVisible(true);

        }

    }

}

void ModifierView::shiftButtonReleased()
{

    if (viewModel->getNumberOfParameters() > 8)
    {
        for (int i = 0; i < knobs.size(); i++) {

            if (i < 8)
                knobs[i]->setVisible(true);
            else
                knobs[i]->setVisible(false);

        }

    }

}

void ModifierView::encoder1Increased()
{

    if (!midiCommandManager.isShiftDown)
        viewModel->setParameterValue(0, viewModel->getParameterValue(0) + viewModel->getParameterInterval(0));
    else
        viewModel->setParameterValue(8, viewModel->getParameterValue(8) + viewModel->getParameterInterval(8));

}

void ModifierView::encoder1Decreased()
{

    if (!midiCommandManager.isShiftDown)
        viewModel->setParameterValue(0, viewModel->getParameterValue(0) - viewModel->getParameterInterval(0));
    else
        viewModel->setParameterValue(8, viewModel->getParameterValue(8) - viewModel->getParameterInterval(8));

}

void ModifierView::encoder2Increased()
{

    if (!midiCommandManager.isShiftDown)
        viewModel->setParameterValue(1, viewModel->getParameterValue(1) + viewModel->getParameterInterval(1));
    else
        viewModel->setParameterValue(9, viewModel->getParameterValue(9) + viewModel->getParameterInterval(9));

}

void ModifierView::encoder2Decreased()
{

    if (!midiCommandManager.isShiftDown)
        viewModel->setParameterValue(1, viewModel->getParameterValue(1) - viewModel->getParameterInterval(1));
    else
        viewModel->setParameterValue(9, viewModel->getParameterValue(9) - viewModel->getParameterInterval(9));

}

void ModifierView::encoder3Increased()
{

    if (!midiCommandManager.isShiftDown)
        viewModel->setParameterValue(2, viewModel->getParameterValue(2) + viewModel->getParameterInterval(2));
    else
        viewModel->setParameterValue(10, viewModel->getParameterValue(10) + viewModel->getParameterInterval(10));

}

void ModifierView::encoder3Decreased()
{

    if (!midiCommandManager.isShiftDown)
        viewModel->setParameterValue(2, viewModel->getParameterValue(2) - viewModel->getParameterInterval(2));
    else
        viewModel->setParameterValue(10, viewModel->getParameterValue(10) - viewModel->getParameterInterval(10));

}

void ModifierView::encoder4Increased()
{

    if (!midiCommandManager.isShiftDown)
        viewModel->setParameterValue(3, viewModel->getParameterValue(3) + viewModel->getParameterInterval(3));
    else
        viewModel->setParameterValue(11, viewModel->getParameterValue(11) + viewModel->getParameterInterval(11));

}

void ModifierView::encoder4Decreased()
{

    if (!midiCommandManager.isShiftDown)
        viewModel->setParameterValue(3, viewModel->getParameterValue(3) - viewModel->getParameterInterval(3));
    else
        viewModel->setParameterValue(11, viewModel->getParameterValue(11) - viewModel->getParameterInterval(11));

}

void ModifierView::parametersChanged()
{

    for (int i = 0; i < viewModel->getNumberOfParameters(); i++)
    {

        knobs[i]->getSlider().setValue(viewModel->getParameterValue(i), juce::dontSendNotification);

    }

}

