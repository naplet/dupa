#ifndef JIMP_EXERCISES_MOVIESUBTITLES_H
#define JIMP_EXERCISES_MOVIESUBTITLES_H

#include <string>

using namespace std;
namespace moviesubs{
class MovieSubtitles{
public:
    virtual void ShiftAllSubtitlesBy (int mTime, int fps, stringstream *in, stringstream *out) = 0;
    ~MovieSubtitles() = default;

};

class MicroDvdSubtitles : public MovieSubtitles{
public:
    MicroDvdSubtitles();
    void ShiftAllSubtitlesBy (int mTime, int fps, stringstream *in, stringstream *out) override ;


};

class SubRipSubtitles : public MovieSubtitles{
public:
    SubRipSubtitles();
    void ShiftAllSubtitlesBy (int mTime, int fps, stringstream *in, stringstream *out) override ;
};

 class SubtitlesException : public std::invalid_argument {
    public:
        SubtitlesException(size_t lineNumber, const std::string &line);

        size_t LineAt() const;

    private:
        size_t m_line_number;
        std::string msg;
    };

    class NegativeFrameAfterShift : public SubtitlesException {
    public:
        NegativeFrameAfterShift(size_t lineNumber, const std::string &line);
    };

    class SubtitleEndBeforeStart : public SubtitlesException {
    public:
        SubtitleEndBeforeStart(size_t lineNumber, const std::string &line);
    };

    class InvalidSubtitleLineFormat : public SubtitlesException {
    public:
        InvalidSubtitleLineFormat(size_t lineNumber, const std::string &line);
    };

    class OutOfOrderFrames : public SubtitlesException {
    public:
        OutOfOrderFrames(size_t lineNumber, const std::string &line);
    };

    class MissingTimeSpecification : public SubtitlesException {
    public:
        MissingTimeSpecification(size_t lineNumber, const std::string &line);

    };
}
