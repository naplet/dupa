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

//////////////////////////////Excpetions////////////////////////////////////////
//////////MicroDvd/////////////////
    class NegativeFrameAfterShift : public invalid_argument {
    public:

        NegativeFrameAfterShift();

        ~NegativeFrameAfterShift() = default;
    };
   /* class SubtitleEndBeforeStart : public exception{
    private:
        int line_;
        string message_;
    public:
        int LineAt() const;
        const char* what() const throw() override ;
        SubtitleEndBeforeStart();
        SubtitleEndBeforeStart(int line, string message);
        ~SubtitleEndBeforeStart() = default;
    };*/
    class SubtitleEndBeforeStart {
    private:
        int line_;
        string message_;
    public:
        int LineAt() const;
        string what() const;
        SubtitleEndBeforeStart();
        SubtitleEndBeforeStart(int line, string message);
        ~SubtitleEndBeforeStart() = default;
    };
    class InvalidSubtitleLineFormat {
    public:
        InvalidSubtitleLineFormat();
        InvalidSubtitleLineFormat(int a);
        ~InvalidSubtitleLineFormat() = default;
    };
    class OutOfOrderFrames {
    public:
        OutOfOrderFrames();
        ~OutOfOrderFrames() = default;
    };
    class MissingTimeSpecification{};
}


#endif //JIMP_EXERCISES_MOVIESUBTITLES_H
