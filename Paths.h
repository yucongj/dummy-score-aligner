
#ifndef PIANO_ALIGNER_PATHS_H
#define PIANO_ALIGNER_PATHS_H

#include <filesystem>
#include <vector>
#include <map>
#include <string>

class Paths
{
public:
    /**
     * Return a list of directories to be searched for scores.
     *
     * If the environment variable PIANO_ALIGNER_SCORE_PATH is set,
     * its contents will be treated as a semicolon-separated (on
     * Windows) or colon-separated (elsewhere) list of directories and
     * will be returned here. Otherwise the single entry
     * $HOME/Documents/PianoPrecision/Scores will be used.
     *
     * Return an empty vector if the environment variable is set but
     * cannot be used for some reason, or if $HOME is not set.  Note
     * that this function does not check that the directories exist.
     */
    static std::vector<std::filesystem::path> getScoreDirectories();

    /**
     * Return a list of scores found in the score directories. Each
     * score is also a directory, containing (at least) .solo and
     * .meter files. The returned value maps from score name to score
     * directory.
     *
     * This function only returns scores whose directories exist and
     * contain appropriately-named .solo and .meter files.
     *
     * If more than one of the score directories contains a score with
     * a given name, the first one found takes priority.
     */
    static std::map<std::string, std::filesystem::path> getScores();
};

#endif
