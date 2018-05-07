#include "MovieSubtitles.h"


namespace moviesubs {
    void CheckLineMicroDVD(const string &line, regex pattern, int LineIndex, int Fps, int PreviousFrameStartTime){
        smatch matches;
        if (!std::regex_match(line, matches, pattern)) throw InvalidSubtitleLineFormat(LineIndex,line);
        if (std::atoi(matches[1].str().c_str()) < PreviousFrameStartTime) throw OutOfOrderFrames(LineIndex, line);
        if (std::atoi(matches[1].str().c_str()) > std::atoi(matches[2].str().c_str())) throw SubtitleEndBeforeStart(LineIndex, line);
        if (std::atoi(matches[1].str().c_str()) + Fps < 0) throw NegativeFrameAfterShift(LineIndex,line);
    }

    void MicroDvdSubtitles::ShiftAllSubtitlesBy(int offset_in_micro_seconds, int frame_per_second, std::istream *in, std::ostream *out) {
    
        if(frame_per_second < 0) throw std::invalid_argument("Negative fps")
        int Fps = (offset_in_micro_seconds*frame_per_second)/1000
        regex pattern {R"(\{(\d+)\}\{(\d+)\}(.+))"};
        int LineIndex = 1;
        int start = -1;
        while (!in->eof()) {
            string buffor;
            smatch matches;
            std::getline(*in,buffor);
            if(buffor == "") break;
            CheckLineMicroDVD(buffor, pattern, LineIndex, Fps, start);
            std::regex_match(buffor, matches, pattern);
            start = std::atoi(matches[1].str().c_str());
            *out << "{" << std::atoi(matches[1].str().c_str()) + Fps << "}{" <<
                 std::atoi(matches[2].str().c_str()) + Fps << "}" << matches[3].str() << "\n";
            LineIndex++;
        }


    }

    bool SubRipSubtitles::IsEndGreater(const string &start, const string &end) {
        if(std::atoi(end.substr(0,2).c_str()) < std::atoi(start.substr(0,2).c_str())) return false;
        else if (std::atoi(end.substr(0,2).c_str()) == std::atoi(start.substr(0,2).c_str())){
            if (std::atoi(end.substr(3,2).c_str()) < std::atoi(start.substr(3,2).c_str())) return false;
            else if (std::atoi(end.substr(3,2).c_str()) == std::atoi(start.substr(3,2).c_str())){
               if (std::atoi(end.substr(6,2).c_str()) < std::atoi(start.substr(6,2).c_str())) return false;
               else if (std::atoi(end.substr(6,2).c_str()) == std::atoi(start.substr(6,2).c_str())){
                   if (std::atoi(end.substr(9,3).c_str()) < std::atoi(start.substr(9,3).c_str())) return false;
               }
            }
        }
        return true;
    }

    void SubRipSubtitles::ValidateSubRip(const string &sub, regex pattern, int offset, int previousFrame){
        smatch matches;
        if(!std::regex_match(sub, matches ,pattern)) throw InvalidSubtitleLineFormat(1, sub);
        if(previousFrame + 1 != std::atoi(matches[1].str().c_str())) throw OutOfOrderFrames(1, matches[1].str());
        if(!IsEndGreater(matches[2].str(), matches[3].str())) throw SubtitleEndBeforeStart(2, matches[2].str() + " --> " + matches[3].str());
        if(AddShift(offset, matches[2].str())[0] == '-') throw NegativeFrameAfterShift(1, sub);
    }

    void SubRipSubtitles::ShiftAllSubtitlesBy(int offset_in_micro_seconds, int frame_per_second, std::istream *in,
                                              std::ostream *out) {

        if(frame_per_second < 0) throw std::invalid_argument("Negative fps");
        regex pattern {R"((\d+)\n(\d{2}\:\d{2}\:\d{2},\d{3}) --> (\d{2}\:\d{2}\:\d{2},\d{3})\n((?:.+\n*)+))"};
        regex pattern2 {R"(\n\n)"};
        smatch matches1;
        string entireFile;
        string line;
        int previousFrame = 0;
        while (!in->eof()){
            std::getline(*in, line);
            entireFile.append(line + "\n");
        }
        while (std::regex_search(entireFile, matches1, pattern2)){
            smatch matches2;
            string sub = matches1.prefix().str();
            ValidateSubRip(sub, pattern, offset_in_micro_seconds, previousFrame);
            std::regex_match(sub , matches2, pattern);
            *out<<matches2[1].str()<<"\n"<<AddShift(offset_in_micro_seconds, matches2[2].str())<<" --> "<<AddShift(offset_in_micro_seconds, matches2[3].str())<<"\n"<<matches2[4].str()<<"\n\n";
            entireFile = matches1.suffix().str();
            previousFrame++;
        }

    }

    string SubRipSubtitles::AddShift(int offset, const string &time) {
        bool negative = false;
        int hours = std::atoi(time.substr(0,2).c_str());
        int minutes = std::atoi(time.substr(3,2).c_str());
        int seconds = std::atoi(time.substr(6,2).c_str());
        int mili = std::atoi(time.substr(9,3).c_str());
        mili += offset;
        while (mili >= 1000) {
            mili -= 1000;
            seconds += 1;
            while (seconds >=60){
                seconds -=60;
                minutes += 1;
                while (minutes >=60){
                    minutes -=60;
                    hours += 1;
                }
            }
        }
        while (mili <0) {
            mili += 1000;
            seconds -= 1;
            while (seconds < 0){
                seconds +=60;
                minutes -= 1;
                while (minutes < 0){
                    minutes +=60;
                    hours -= 1;
                }
                if(hours < 0) negative = true;
            }
        }
        string result;
        if (negative) result = "-";
        vector <int> times {hours, minutes, seconds};
        for (auto i : times){
            if (i<10) result.append("0" + std::to_string(i) + ":");
            else result.append(std::to_string(i) + ":");
        }
        if (mili < 10) result = result.substr(0,result.size() - 1) + ",00" + std::to_string(mili);
        else if (mili < 100) result = result.substr(0,result.size() - 1) + ",0" + std::to_string(mili);
        else result = result.substr(0,result.size() - 1) + "," + std::to_string(mili);
        return result;

    }


    string SubtitlesException::prepare(int number) {
        return " " +  std::to_string(number) + ": ";
    }

    SubtitlesException::SubtitlesException(int lineNumber, const string &line) : std::invalid_argument("At line" + prepare(lineNumber) + line) {
        lineNumber_ = lineNumber;
    }

    int SubtitlesException::LineAt() const {
        return lineNumber_;
    }

    NegativeFrameAfterShift::NegativeFrameAfterShift(int lineNumber, const string &line) : SubtitlesException(lineNumber, line) {}
    InvalidSubtitleLineFormat::InvalidSubtitleLineFormat(int lineNumber, const string &line) : SubtitlesException(lineNumber, line) {}
    OutOfOrderFrames::OutOfOrderFrames(int lineNumber, const string &line) : SubtitlesException(lineNumber, line) {}
    SubtitleEndBeforeStart::SubtitleEndBeforeStart(int lineNumber, const string &line) : SubtitlesException(lineNumber, line) {}
    MissingTimeSpecification::MissingTimeSpecification(int lineNumber, const string &line) : SubtitlesException(lineNumber, line) {}
}
