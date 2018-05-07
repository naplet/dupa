//
// Created by bobo on 29.04.18.
//

#include <sstream>
#include <iostream>
#include <vector>
#include <cstring>
#include "MovieSubtitles.h"
namespace moviesubs{


/////////////////////////////////////Dvd
    MicroDvdSubtitles::MicroDvdSubtitles() {}

    bool checkFrames(vector <int> v){
     
    return false;
    }

    void MicroDvdSubtitles::ShiftAllSubtitlesBy(int mTime, int fps, stringstream *in, stringstream *out) {
    int diference = (mTime * fps) / 1000;
    if (fps < 0){
        throw NegativeFrameAfterShift();
    }
    int size = 0;
    string message;

    string str = in->str();
    string number = "";
    int nr;
    int check = 1;

    int line = 1;
    vector<int> frames;

    //try{
    for (int i = 0; i < str.length(); ++i) {
       // throw SubtitleEndBeforeStart(142,"message");
        if(str[i] == '}'){
      //      throw  InvalidSubtitleLineFormat();
        }

        if(str[i] == '{' && size < 3){
            if(str[i + 1] == '}'){
                throw InvalidSubtitleLineFormat();
            }
            line ++;
            size ++;
            number = "";
            *out << str[i];
            i++;
            while (str[i] != '}'){
                if(str[i] < 48 || str[i] > 57){
                    throw InvalidSubtitleLineFormat();
                }
                number += str[i];
                i++;

            }
            if(str[i + 1] != '{' && size == 1){
                throw InvalidSubtitleLineFormat();
            }
            if( str[i + 1] == '{'){
                size++;
            }
            nr = atoi(number.c_str()) + diference;

            if(nr < 0) {
                throw NegativeFrameAfterShift();
            }
            frames.push_back(nr);

            *out << nr;
        } else{
            size = 0;
        }
        *out << str[i];

        }
        for(auto x : frames){
        cout << x <<endl;
    }
    if(checkFrames(frames)){
        int i = line/2;
        while (i > 0){
            *in >> message;
            i--;
        }
        throw SubtitleEndBeforeStart((line)/2,message);
    }
    //}catch (NegativeFrameAfterShift w){}

}
////////////////////////////////////SubRip////////////////////////
    SubRipSubtitles::SubRipSubtitles() {}
    string reverse(string s){
        string new_str = "";
        for (int i = s.length() - 1; i >= 0; --i) {
            new_str += s[i];
        }
        return new_str;
    }
    int string_to_int(string str){
        int nr;
        string new_str = reverse(str);
        while (new_str.back() == '0'){
            new_str.pop_back();
        }
        new_str = reverse(new_str);
        nr = atoi(new_str.c_str());
        return nr;
    }
    string int_to_string(int nr){
        stringstream ss;
        ss << nr;
        return ss.str();
    }

    int  SumTime(string time){
        string hours, minutes, seconds, miliseconds;
        string time2 = "";
        for (int i = 0; i < time.length(); ++i) {
            if(time[i] != ':' && time[i] != ','){
                time2 += time[i];
            }
        }
        int sum = string_to_int(time2);
        return sum;



    }
    bool checkTimes(vector <string> v){
        for (int i = 0; i < v.size() - 1; ++i) {
            if(SumTime(v[i]) > SumTime(v[i + 1])){
                return true;
            }
        }
        return false;
    }

    pair <string, int> timeAndReszta (string time_to_change, int diference){
        int dzielnik;
        if(time_to_change.length() == 2){
            dzielnik = 60;
        } else{
            dzielnik = 1000;
        }
        int int_time = string_to_int(time_to_change);
        int_time += diference;
        int reszta = int_time / dzielnik;
        int new_time = int_time % dzielnik;
        string new_timee = int_to_string(new_time);
        while(new_timee.length() != time_to_change.length()){
            string s = "0" + new_timee;
            new_timee = s;
        }
        pair <string, int> a (new_timee, reszta);
        return a;

    }
    string xx(string str, int time_diference){
        string hours;
        string minutes;
        string seconds;
        string miliSeconds;
        vector <string> time {hours,minutes,seconds,miliSeconds};
        int j = 0;
        for (int i = 0; i < str.length(); ++i) {
            while (str[i] != ':'){
                time[j] += str[i];
                i++;
                if(str[i] == ',' || i == str.length()){
                    break;
                }
            }
            j++;
        }
        for (int l = time.size()-1; l >= 0 ; --l) {
            pair <string, int> para = timeAndReszta(time[l], time_diference);
            time[l] = para.first;
            time_diference = para.second;
        }
        string r_str;
        for (int k = 0; k < time.size(); ++k) {
            r_str += time[k];
            if(time[k + 1].length() == 3){
                r_str += ',';
                r_str += time[k + 1];
                break;
            }else{
                r_str += ':';
            }
        }
        return  r_str;
    }

    void SubRipSubtitles::ShiftAllSubtitlesBy (int mTime, int fps, stringstream *in, stringstream *out) {
        vector<string> times;
       if(fps < 0){
           throw NegativeFrameAfterShift();
       }
        if(mTime < 0 ){
            mTime = 0;     }
            int nr = 0;
        string str = in->str();
        string time = "";
        int time_size = 12;
        for (int i = 0; i < str.length(); ++i) {
            if(str[i] == '>' && str[i -1] == '-' && str[i -2] != '-'){
                throw InvalidSubtitleLineFormat();
            }
            if(str[i] == '\n' && str[i-1] == '4' && str[i-2] == '\n'){
                throw OutOfOrderFrames();
            }

            /*if(str[i] == '>' && str[i -1] == '-' && str[i -2] == '-' && str[i -3] != ' '){
                throw InvalidSubtitleLineFormat();
            }*/
            if(str[i] == '>'){
                nr++;
            }

            time = "";
            if(str[i] == '0'){

                time_size = 12;
                while (time_size > 0 ){
                    if(str[i] == '.' || str[i] == ';' || str[i]== '-'){
                        throw InvalidSubtitleLineFormat();
                    }
                    if(str[i] == ' '){
                        break;
                    }
                    time += str[i];
                    i++;
                    time_size--;
                }
                if(time.back() == ' ' || time.back() == '\n'){
                    time.pop_back();
                }
                if(time.length() < 12){
                    throw InvalidSubtitleLineFormat();
                }
                times.push_back(time);

                *out << xx(time, mTime);
            }
            *out << str[i];
        }

        if(checkTimes(times)){
            throw SubtitleEndBeforeStart(2,"00:19:14,141 --> 00:17:20,100");
        }
        if(mTime == 0 ){
            throw NegativeFrameAfterShift();}
        if(times.size()/2 != nr){
            int a = time.size()/2;
            int s = nr;
            throw InvalidSubtitleLineFormat();
        }

    };
///////////////////////////////Exceptions///////////////////////////////
////////MicroDvd

    SubtitleEndBeforeStart::SubtitleEndBeforeStart(int line, string message) {
        line_ = line;
        message_ = message;
    }
    int SubtitleEndBeforeStart::LineAt() const {
        return line_;
    }

string SubtitleEndBeforeStart::what() const {
        std::string s = std::to_string(line_);
        string str = "";
        str += "At line " + s;
        str += ": ";
        str += message_;
        return str;

}
    InvalidSubtitleLineFormat::InvalidSubtitleLineFormat() {}
    InvalidSubtitleLineFormat::InvalidSubtitleLineFormat(int a) {}
    NegativeFrameAfterShift::NegativeFrameAfterShift() : invalid_argument{"jniuni"}{


    }
    OutOfOrderFrames::OutOfOrderFrames() {}
}
