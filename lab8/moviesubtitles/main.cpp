
#include <sstream>
#include <iostream>
#include <memory>
#include <vector>
#include "MovieSubtitles.h"


using namespace moviesubs;
class myexception: public exception
{
    virtual const char* what() const throw()
    {
        return "My exception happened";
    }
} myex;

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
int main(){
    string s = "00:05:54,555";

   // cout << xx(s, 2000000);


   stringstream ss{"1\n00:00:10,345 --> 00:00:12,678\nTEXT\n\n2\n00:19:14,141 --> 00:21:20,100\nTT\n"};
   string str = ss.str();
   string time = "";
   int time_size = 12;
    for (int i = 0; i < str.length(); ++i) {
        time = "";
        if(str[i] == '0'){
            time_size = 12;
            while (time_size > 0 ){
                time += str[i];
                i++;
                time_size--;
            }
            cout << xx(time, -11400);
        }
        cout << str[i];
    }

}
