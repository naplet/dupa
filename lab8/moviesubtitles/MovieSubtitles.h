//
// Created by naplet on 2.05.18.
//

#ifndef JIMP_EXERCISES_MOVIESUBTITLES_H
#define JIMP_EXERCISES_MOVIESUBTITLES_H

#include <regex>
#include <fstream>
#include <string>
#include <vector>
#include <strstream>

using std::string;
using std::smatch;
using std::regex;
using std::vector;
using std::strstream;

namespace moviesubs {
    class MovieSubtitles {
    public:
        virtual void
        ShiftAllSubtitlesBy(int offset_in_micro_seconds, int frame_per_second, std::istream *in, std::ostream *out) = 0;

        ~MovieSubtitles() = default;
    };

    class MicroDvdSubtitles : public MovieSubtitles {
    public:
        void ShiftAllSubtitlesBy(int offset_in_micro_seconds, int frame_per_second, std::istream *in,
                                 std::ostream *out) override;
    };

    class SubRipSubtitles : public MovieSubtitles {
    public:
        void ShiftAllSubtitlesBy(int offset_in_micro_seconds, int frame_per_second, std::istream *in,
                                 std::ostream *out) override;

    private:
        string AddShift(int offset, const string &time);
        void ValidateSubRip(const string &sub, regex pattern, int offset, int previousFrame);
        bool IsEndGreater(const string &start, const string &end);
    };


    class SubtitlesException : public std::invalid_argument {
    public:
        SubtitlesException(int lineNumber, const string &line);
        int LineAt() const;
    private:
        string prepare(int number);
        int lineNumber_;
        string msg;
    };

    class NegativeFrameAfterShift : public SubtitlesException {
    public:
        NegativeFrameAfterShift(int lineNumber, const string &line);
    };

    class SubtitleEndBeforeStart : public SubtitlesException {
    public:
        SubtitleEndBeforeStart(int lineNumber, const string &line);
    };

    class InvalidSubtitleLineFormat : public SubtitlesException {
    public:
        InvalidSubtitleLineFormat(int lineNumber, const string &line);
    };

    class OutOfOrderFrames : public SubtitlesException {
    public:
        OutOfOrderFrames(int lineNumber, const string &line);
    };

    class MissingTimeSpecification : public SubtitlesException {
    public:
        MissingTimeSpecification(int lineNumber, const string &line);

    };
}

#endif //JIMP_EXERCISES_MOVIESUBTITLES_H
