#include "TracksViewModel.h"

namespace app_view_models {

    TracksViewModel::TracksViewModel(tracktion_engine::Edit& e)
            : edit(e),
              state(edit.state.getOrCreateChildWithName(IDs::TRACKS_VIEW_STATE, nullptr))
    {

        jassert(state.hasType(app_view_models::IDs::TRACKS_VIEW_STATE));

        std::function<int(int)> selectedIndexConstrainer = [this](int param) {

            // selected index cannot be less than -1
            // -1 means nothing is selected
            // greater than -1 means something is selected
            // it also cannot be greater than the number of tracks
            if (param < -1)
                return -1;
            else if (param >= tracktion_engine::getAudioTracks(edit).size())
                return tracktion_engine::getAudioTracks(edit).size() - 1;
            else
                return param;

        };

        selectedTrackIndex.setConstrainer(selectedIndexConstrainer);
        selectedTrackIndex.referTo(state, app_view_models::IDs::selectedTrackIndex, nullptr, tracktion_engine::getAudioTracks(edit).size() - 1);

        // we want to subscribe to changes to the main edit value tree
        // this is so we can be notified when tracks are added to the edit
        // as well as when the EDIT_VIEW_STATE child tree changes
        edit.state.addListener(this);

        updateTrackNames();

    }

    TracksViewModel::~TracksViewModel() {

        edit.state.removeListener(this);

    }

    juce::Array<juce::String> TracksViewModel::getTrackNames() {

        return trackNames;

    }

    int TracksViewModel::getSelectedTrackIndex() {

        return selectedTrackIndex.get();

    }

    void TracksViewModel::setSelectedTrackIndex(int newIndex)
    {


        selectedTrackIndex.setValue(newIndex, nullptr);

    }

    tracktion_engine::Track *TracksViewModel::getSelectedTrack() {

        return tracktion_engine::getAudioTracks(edit).getUnchecked(selectedTrackIndex.get());

    }


    void TracksViewModel::updateTrackNames() {

        trackNames.clear();
        for (auto track : tracktion_engine::getAudioTracks(edit)) {
            trackNames.add(track->getName());
        }

    }

    void TracksViewModel::handleAsyncUpdate()
    {

        if (compareAndReset(shouldUpdateSelectedIndex))
        {

            listeners.call([this](Listener &l) { l.selectedTrackIndexChanged(getSelectedTrackIndex()); });
        }

        if (compareAndReset(shouldUpdateTracks))
        {
            // tracks changed
            // need to ensure selected index is not beyond the current number of tracks
            if (getSelectedTrackIndex() >= tracktion_engine::getAudioTracks(edit).size())
            {

                setSelectedTrackIndex(tracktion_engine::getAudioTracks(edit).size() - 1);

            }

            updateTrackNames();
            listeners.call([this](Listener &l) { l.tracksChanged(); });

        }
    }

    void TracksViewModel::valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property)
    {

        if (treeWhosePropertyHasChanged == edit.state.getChildWithName(app_view_models::IDs::TRACKS_VIEW_STATE))
        {

            markAndUpdate(shouldUpdateSelectedIndex);

        }


    }

    void TracksViewModel::valueTreeChildAdded(juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenAdded)
    {

        if (tracktion_engine::TrackList::isTrack(childWhichHasBeenAdded))
            markAndUpdate(shouldUpdateTracks);


    }

    void TracksViewModel::valueTreeChildRemoved(juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved)
    {

        if (tracktion_engine::TrackList::isTrack(childWhichHasBeenRemoved))
        {

            markAndUpdate(shouldUpdateTracks);
        }



    }

    void TracksViewModel::addListener(Listener *l)
    {

        listeners.add(l);

    }

    void TracksViewModel::removeListener(Listener *l)
    {

        listeners.remove(l);
    }

}

