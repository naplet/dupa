#include"SimpleJson.h"
#include <sstream>
#include <iomanip>

namespace nets{
    JsonValue::JsonValue(){
        TheCase = 0;
    }

    JsonValue::~JsonValue() {

    }

    JsonValue::JsonValue(int value){
        TheCase = 1;
        this->IntX = value;
    }

    JsonValue::JsonValue(double value){
        TheCase = 2;
        this->DoubleX = value;
    }

    JsonValue::JsonValue(const std::string value){
        TheCase = 3;
        this->StringX = value;
    }

    JsonValue::JsonValue(bool value){
        TheCase = 4;
        this->BoolX = value;
    }

    JsonValue::JsonValue(std::vector<JsonValue> values){
        TheCase = 5;
        this->Array = values;
    }

    JsonValue::JsonValue(std::map<std::string, JsonValue> map){
        TheCase = 6;
        this->Map = map;
    }

    int JsonValue::GetTheCase() const {
        return TheCase;
    }

    int JsonValue::GetIntX() const {
        return IntX;
    }

    double JsonValue::GetDoubleX() const {
        return DoubleX;
    }

    const std::string &JsonValue::GetStringX() const {
        return StringX;
    }

    bool JsonValue::GetBoolX() const {
        return BoolX;
    }

    const std::vector<JsonValue> &JsonValue::GetArray() const {
        return Array;
    }

    const std::map<std::string, JsonValue> &JsonValue::GetMap() const {
        return Map;
    }

    std::string JsonValue::ToString() const{
        if(GetTheCase() == 1) return std::to_string(GetIntX());
        else if(GetTheCase() == 2) {
            std::string Tmp =  std::to_string(GetDoubleX());
            for (int i = Tmp.length() -1 ; i > 0 ; --i) if(Tmp[i] != '0') return Tmp.substr(0,i+1);
        }
        else if(GetTheCase() == 3) {
            std::string Tmp = "";
            std::string str = GetStringX();
            for (int i = 0; i < str.length(); ++i) {
                if(str[i] == '"' || str[i] == '\\') Tmp += R"(\)";
                Tmp += str[i];
            }
            return "\"" + Tmp + "\"";
        }
        else if(GetTheCase() == 4) {
            if (GetBoolX() == false) {
                return "false";
            }
            else if (GetBoolX() == true){
                return "true";
            }
            else
            {
                return "";
            }
        }
        else if(GetTheCase() == 5){
            std::string Tmp = "[";
            for(auto i : GetArray()) Tmp += i.ToString()+ ", ";
            Tmp = Tmp.substr(0,Tmp.length()-2) + "]";
            return Tmp;
        }
        else if(GetTheCase() == 6){
            std::string Tmp = "{";
            for(auto i : GetMap()) {
                Tmp += R"(")";
                for (auto j : i.first){
                    if(j == '"' || j== '\\') Tmp += R"(\)";
                    Tmp += j;
                }
                Tmp += R"(": )" + i.second.ToString() + R"(, )";
            }
            Tmp = Tmp.substr(0,Tmp.length()-2) + "}";
            return Tmp;
        }
    }

    std::experimental::optional<JsonValue> JsonValue::ValueByName(const std::string &name) const{
        return GetMap().find("a")->second;

    }







}