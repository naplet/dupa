#ifndef JIMP_EXERCISES_MOVIESUBTITLES_H
#define JIMP_EXERCISES_MOVIESUBTITLES_H

#include <regex>
#include <string>
#include <stdexcept>
#include <iostream>

namespace moviesubs {

    class MovieSubtitles{
    public:
        virtual void ShiftAllSubtitlesBy(int delay, int framerate,
                                 std::stringstream* in, std::stringstream* out) =0;
    };

    class MicroDvdSubtitles:public MovieSubtitles{
    public:
        void ShiftAllSubtitlesBy(int delay, int framerate,
                                 std::stringstream* in, std::stringstream* out) override ;
    };

    class SubRipSubtitles :public MovieSubtitles{
        void ShiftAllSubtitlesBy(int delay, int framerate,
                                 std::stringstream* in, std::stringstream* out) override ;
    };


    //Errors

    class SubtitleException : public std::invalid_argument{
    public:
        SubtitleException(const std::string &line_content, int line_number);
        int LineAt() const;
        const char* what () const noexcept override;
        std::string message_;
        int line_number_;
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

#endif //JIMP_EXERCISES_MOVIESUBTITLES_H
