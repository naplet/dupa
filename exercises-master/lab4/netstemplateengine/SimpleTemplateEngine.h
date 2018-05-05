
#ifndef JIMP_EXERCISES_SIMPLETEMPLATEENGINE_H
#define JIMP_EXERCISES_SIMPLETEMPLATEENGINE_H
#include <string>
#include <unordered_map>
#include <regex>
#include <iostream>
namespace nets {
    class View{
    public:
        View();
        View(std::string InputString);
        ~View();
        std::string Render(const std::unordered_map <std::string, std::string> &model) const;
        std::string GetString() const;
    private:
        std::string InputString;
    };
}
#endif //JIMP_EXERCISES_SIMPLETEMPLATEENGINE_H
