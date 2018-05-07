//
// Created by bobo on 29.04.18.
//

#include <sstream>
#include <iostream>
#include <vector>
#include <cstring>
#include "MovieSubtitles.h"
namespace moviesubs{

void moviesubs::MicroDvdSubtitles::ShiftAllSubtitlesBy(int delay, int framerate,
                                                        std::stringstream* in, std::stringstream* out) {

    if (framerate < 0){
        throw std::invalid_argument("Negative framerate");
    }

    int shift_by=(delay*framerate)/1000;

    std::regex subtitles_regex(R"(\{(-?\d+)\}\{(-?\d+)\}(.+))");
    int line_index=1;

    char line_buffer[1000];

    while(in->getline(line_buffer, 1000)) {
        std::cmatch line;
        if (std::regex_match(line_buffer, sub_line, subtitles_regex)){
            int start_frame = std::stoi(line[1])+shift_by;
            int end_frame = std::stoi(line[2])+shift_by;
            if (start_frame>end_frame){
                throw(SubtitleEndBeforeStart(line[0], line_index));
            }
            if (start_frame < 0){
                throw(NegativeFrameAfterShift(line[0], line_index));
            }
            (*out)<<"{"<<start_frame<<"}{"<<end_frame<<"}"<<line[3]<<"\n";
        } else{
            throw(InvalidSubtitleLineFormat(std::string(line_buffer), line_index));
        }
        ++line_index;
    }
}


moviesubs::SubtitleException::SubtitleException(const std::string &line_content, int line_number): std::invalid_argument{"SubtitleException"}{
    std::stringstream out_stream;
    line_number_=line_number;
    out_stream<<"At line "<<line_number_<<": "<<line_content;
    message_=out_stream.str();
}

int moviesubs::SubtitleException::LineAt() const {
    return line_number_;
}

const char *moviesubs::SubtitleException::what() const noexcept {
    return message_.c_str();
}

moviesubs::NegativeFrameAfterShift::NegativeFrameAfterShift(const std::string &line_content, int line_number)
        : SubtitleException(line_content, line_number) {

}

moviesubs::SubtitleEndBeforeStart::SubtitleEndBeforeStart(const std::string &line_content, int line_number)
        : SubtitleException(line_content, line_number) {

}

moviesubs::InvalidSubtitleLineFormat::InvalidSubtitleLineFormat(const std::string &line_content, int line_number)
        : SubtitleException(line_content, line_number) {

}

moviesubs::OutOfOrderFrames::OutOfOrderFrames(const std::string &line_content, int line_number) : SubtitleException(
        line_content, line_number) {

}
