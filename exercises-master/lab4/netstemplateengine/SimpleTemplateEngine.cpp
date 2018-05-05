
#include "SimpleTemplateEngine.h"
namespace nets{
    View::View(std::string InputString) {
        this->InputString=InputString;
    }
    View::View() {}
    View::~View() {}
    std::string View::GetString() const {
        return this->InputString;
    }
    std::string View::Render(const std::unordered_map<std::string, std::string> &model) const {
        std::string actual_text = GetString();
        bool found_next = false;

        std::regex my_regex(R"(\{\{(\w*)\}\})");
        std::smatch my_matches;
        regex_search(actual_text, my_matches, my_regex);
        std::size_t key_index = my_matches.size()-1;

        for(size_t i=0; i<my_matches.size(); i++) {
            std::size_t index = actual_text.find(my_matches[i]);
            while(index != std::string::npos) {

                auto it = model.find(my_matches[key_index]);
                if (it != model.end()) {
                    std::string founded_key = it->first; // to jest klucz2
                    std::string founded_value = it->second; // to jest efg
                    actual_text.replace(index, my_matches[i].length(), founded_value);

                } else {
                    actual_text.replace(index, my_matches[i].length(), "");
                }
                found_next = regex_search(actual_text, my_matches, my_regex);

                if(found_next){
                    index = actual_text.find(my_matches[i]);
                    key_index = my_matches.size()-1;
                }
                else break;
            }
        }
        return actual_text;
    }

}
