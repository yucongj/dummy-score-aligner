
#include "Paths.h"

#include <iostream>

using std::vector;
using std::filesystem::path;
using std::filesystem::directory_iterator;
using std::string;
using std::map;
using std::cerr;
using std::endl;

static vector<path> splitPath(string str)
{
#ifdef _WIN32
#define PATH_SEPARATOR ';'
#else
#define PATH_SEPARATOR ':'
#endif

    vector<path> pp;
    path p;
    string::size_type index = 0, newindex = 0;
    while ((newindex = str.find(PATH_SEPARATOR, index)) < str.size()) {
	p = path(str.substr(index, newindex - index));
        pp.push_back(p);
	index = newindex + 1;
    }
    p = path(str.substr(index));
    pp.push_back(p);
    return pp;
}

vector<path>
Paths::getScoreDirectories()
{
    vector<path> pp;
    auto envPath = getenv("PIANO_ALIGNER_SCORE_PATH");
    if (envPath) {
        pp = splitPath(string(envPath));
    } else {
        auto home = getenv("HOME");
        if (!home) return {};
        pp.push_back(path(string(home) + "/Documents/PianoPrecision/Scores"));
    }
    return pp;
}

map<string, path>
Paths::getScores()
{
    auto dirs = getScoreDirectories();
    int dirsThatExist = 0;
    map<string, path> scores;

    for (auto dir : dirs) {

        if (!exists(dir)) continue;
        ++dirsThatExist;

        for (auto entry : directory_iterator(dir)) {

            path candidate = entry.path();
            string name(candidate.filename().string());
            if (name.size() == 0 || name[0] == '.' ||
                scores.find(name) != scores.end()) {
                continue;
            }

            path scoreFile(candidate.string() + "/" + name + ".solo");
            if (!exists(scoreFile)) {
                cerr << "WARNING: Candidate score folder "
                     << candidate << " lacks " << name << ".solo file"
                     << endl;
                continue;
            }

            path meterFile(candidate.string() + "/" + name + ".meter");
            if (!exists(meterFile)) {
                cerr << "WARNING: Candidate score folder "
                     << candidate << " lacks " << name << ".meter file"
                     << endl;
                continue;
            }

            cerr << "Found valid-looking score folder: " << candidate << endl;
            scores[name] = candidate;
        }
    }

    if (dirsThatExist == 0) {
        cerr << "WARNING: None of the specified score folders exists!" << endl;
        cerr << "Folders are:" << endl;
        for (auto dir : dirs) {
            cerr << dir << endl;
        }
    }
    
    return scores;
}



