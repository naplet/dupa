
#ifndef JIMP_EXERCISES_SIMPLEJSON_H
#define JIMP_EXERCISES_SIMPLEJSON_H

#include <experimental/optional>
#include <string>
#include <vector>
#include <map>

namespace nets {
    class JsonValue {
    public:

        JsonValue();

        JsonValue(int value);

        JsonValue(double value);

        JsonValue(const std::string value);

        JsonValue(bool value);

        JsonValue(std::vector<JsonValue> values);

        JsonValue(std::map<std::string, JsonValue> map);

        ~JsonValue();

        std::experimental::optional<JsonValue> ValueByName(const std::string &name) const;

        std::string ToString() const;

        int GetTheCase() const;

        int GetIntX() const;

        double GetDoubleX() const;

        const std::string &GetStringX() const;

        bool GetBoolX() const;

        const std::vector<JsonValue> &GetArray() const;


        const std::map<std::string, JsonValue> &GetMap() const;


    private:
        int TheCase;
        int IntX;
        double DoubleX;
        std::string StringX;
        bool BoolX;
        std::vector<JsonValue> Array;
        std::map<std::string, JsonValue> Map;
    };
}

#endif //JIMP_EXERCISES_SIMPLEJSON_H