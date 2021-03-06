#pragma once
#include <gmock/gmock.h>
#include <app_view_models/app_view_models.h>

class MockTrackViewModelListener : public app_view_models::TrackViewModel::Listener
{
public:

    MOCK_METHOD(void, clipsChanged, (const juce::Array<tracktion_engine::Clip*>& clips), (override));
    MOCK_METHOD(void, clipPositionsChanged, (const juce::Array<tracktion_engine::Clip*>& clips), (override));
    MOCK_METHOD(void, transportChanged, (), (override));

};