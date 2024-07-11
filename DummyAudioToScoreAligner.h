#ifndef DUMMY_AUDIO_TO_SCORE_ALIGNER_H
#define DUMMY_AUDIO_TO_SCORE_ALIGNER_H


#include "Score.h"
#include "vamp-sdk/Plugin.h"

#include <vector>


class DummyAudioToScoreAligner
{
public:
    DummyAudioToScoreAligner(float inputSampleRate, int hopSize,
     int m_startEvent, int m_endEvent, int m_startFrame, int m_endFrame);
    ~DummyAudioToScoreAligner();

    typedef std::vector<int> AlignmentResults;

    bool loadAScore(std::string scoreName, int blockSize);
    AlignmentResults align();
    float getSampleRate() const;
    float getHopSize() const;
    Score getScore() const;
    void setAlignmentConstraints(int se, int ee, int sf, int ef);
    int getStartEvent() const;
    int getEndEvent() const;
    int getStartFrame() const;
    int getEndFrame() const;

private:
    float m_inputSampleRate;
    int m_hopSize;
    Score m_score;
    int m_startEvent;
    int m_endEvent;
    int m_startFrame;
    int m_endFrame;
};

#endif
