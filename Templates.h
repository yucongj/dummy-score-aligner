/*
  Yucong Jiang, July 2021
*/

#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <map>
#include <vector>

typedef std::vector<float> Template; // for an individual note, or for a musical event
typedef std::map<int, Template> NoteTemplates; // key is midi

struct CreateNoteTemplates {
    static const NoteTemplates& getNoteTemplates(float sampleRate, int blockSize);
};

/*
class NoteTemplates {
public:
    static const int LOW_MIDI = 21;
    static const int HIGH_MIDI = 108;
    static void initializeNoteTemplates(int sampleRate, int blockSize);
    static std::map<int, Template>& getNoteTemplates();
private:
    static std::map<int, Template> m_noteTemplates; // key is midi
    static bool initialized = false;
};
*/

#endif
