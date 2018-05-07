//
// Created by bobo on 29.04.18.
//

#ifndef JIMP_EXERCISES_MOVIESUBTITLES_H
#define JIMP_EXERCISES_MOVIESUBTITLES_H

#include <string>

using namespace std;
namespace moviesubs{
class MovieSubtitles{
public:
    virtual void ShiftAllSubtitlesBy (int offset_in_micro_seconds, int frame_per_second, stringstream *in, stringstream *out) = 0;
    ~MovieSubtitles() = default;

};

class MicroDvdSubtitles : public MovieSubtitles{
public:
    MicroDvdSubtitles();
    void ShiftAllSubtitlesBy (int offset_in_micro_seconds, int frame_per_second, stringstream *in, stringstream *out) override ;


};

class SubRipSubtitles : public MovieSubtitles{
public:
    SubRipSubtitles();
    void ShiftAllSubtitlesBy (int offset_in_micro_seconds, int frame_per_second, stringstream *in, stringstream *out) override ;
};

class SubtitleException : public std::invalid_argument{
    public:
        SubtitleException(const std::string &line_content, int line_number);
        int LineAt() const;
        const char* what () const noexcept override;
        /*std::string message_;
        int line_number_;*/
    };

    class NegativeFrameAfterShift:public SubtitleException{
    public:
        NegativeFrameAfterShift(const std::string &line_content, int line_number);
    };
    class SubtitleEndBeforeStart:public SubtitleException{
    public:
        SubtitleEndBeforeStart(const std::string &line_content, int line_number);
    };
    class InvalidSubtitleLineFormat:public SubtitleException{
    public:
        InvalidSubtitleLineFormat(const std::string &line_content, int line_number);
    };
    class OutOfOrderFrames:public SubtitleException{
    public:
        OutOfOrderFrames(const std::string &line_content, int line_number);
    };

    class MissingTimeSpecification:public InvalidSubtitleLineFormat{
        MissingTimeSpecification(const std::string &line_content, int line_number);
    };
}

#endif
