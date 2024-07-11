/*
  Yucong Jiang, June 2021
*/


#include "DummyAudioToScoreAligner.h"
#include "Templates.h"
#include "Paths.h"

#include <filesystem>

using namespace std;

DummyAudioToScoreAligner::DummyAudioToScoreAligner(float inputSampleRate, int hopSize,
int startEvent, int endEvent, int startFrame, int endFrame) :
     m_inputSampleRate{inputSampleRate} , m_hopSize{hopSize}, m_startEvent{startEvent}, 
     m_endEvent{endEvent}, m_startFrame{startFrame}, m_endFrame{endFrame}
{
}

DummyAudioToScoreAligner::~DummyAudioToScoreAligner()
{
}

bool DummyAudioToScoreAligner::loadAScore(string scoreName, int blockSize)
{
    cerr << "In loadAScore: scoreName is -> " << scoreName << '\n';

    auto scores = Paths::getScores();

    if (scores.find(scoreName) == scores.end()) {
        cerr << "Score not found: " << scoreName << '\n';
        return false;
    }

    filesystem::path targetPath = scores[scoreName];

    // Paths::getScores() has already verified that these exist
    string scorePath = targetPath.string() + "/" + scoreName + ".solo";
    string scoreMeterPath = targetPath.string() + "/" + scoreName + ".meter";

    bool success = m_score.initialize(scorePath);
    if (success)    success = m_score.readMeter(scoreMeterPath);

    NoteTemplates t =
        CreateNoteTemplates::getNoteTemplates(m_inputSampleRate, blockSize);
    m_score.setEventTemplates(t);

    return success;
}


DummyAudioToScoreAligner::AlignmentResults DummyAudioToScoreAligner::align()
{
    AlignmentResults results;

    // Do the alignment work here!

    // This is fake alignment output, for testing this dummy aligner:
    for (int i = m_startEvent; i <= m_endEvent; i++) {
        results.push_back(1 + i * 10);
    }

    return results;
}

float DummyAudioToScoreAligner::getSampleRate() const
{
    return m_inputSampleRate;
}

float DummyAudioToScoreAligner::getHopSize() const
{
    return m_hopSize;
}

Score DummyAudioToScoreAligner::getScore() const
{
    return m_score;
}

void DummyAudioToScoreAligner::setAlignmentConstraints(int se, int ee, int sf, int ef)
{
    m_startEvent = se;
    m_endEvent = ee;
    m_startFrame = sf;
    m_endFrame = ef;
}

int DummyAudioToScoreAligner::getStartEvent() const
{
    return m_startEvent;
}

int DummyAudioToScoreAligner::getEndEvent() const
{
    return m_endEvent;
}

int DummyAudioToScoreAligner::getStartFrame() const
{
    return m_startFrame;
}

int DummyAudioToScoreAligner::getEndFrame() const
{
    return m_endFrame;
}
