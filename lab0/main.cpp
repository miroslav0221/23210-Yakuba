#include <iostream>
#include <string>
#include <list>
#include <map>
#include <fstream>
#include <clocale>

struct word_info {
    std::string word_;
    size_t count = 0;
};

class Parser {
public:
    void reading_file(std::string name_in) {
        std::fstream fs;
        fs.open(name_in);
        std::string buffer, word;
        if (fs.is_open()) {
            while (std::getline(fs, buffer)) {
                for (auto it = buffer.begin(); it != buffer.end(); it++) {
                    if (isdigit(*it) || isalpha(*it)) {
                        word.push_back(*it); //
                    }
                    else {
                        auto ret = dict_word.insert(std::pair<std::string, int>(word, 1));
                        if (!ret.second) {
                            ret.first->second++;
                        }
                        count_words++;
                        word.clear();
                    }
                }
            }
        }
        else {
            return;
        }

    }


    void process_map() {
        for (auto it = dict_word.begin(); it != dict_word.end(); it++) {
            word_info word;
            word.word_ = it->first;
            word.count = it->second;
            list_word.insert(list_word.begin(), word);
        }
        list_word.sort([](const word_info &first_object_list, const word_info &second_object_list) {
            return first_object_list.count < second_object_list.count;
        });
    }

    void write_file(std::string name_out) {
        setlocale(LC_ALL, "");
        std::fstream out;
        out.open(name_out);
        if (out.is_open()) {
            out << "Word" << ';' << "Frequency" << ';' << "Percent" << std::endl;
            for (auto it = list_word.begin(); it != list_word.end(); it++) {
                out << it->word_ << ';' << it->count << ';' << 100. * double(it->count) / double(count_words)
                    << std::fixed << "%" << std::endl;
            }
        } else {
            return;
        }
    }
private:
    std::map<std::string, int> dict_word;
    std::list<word_info> list_word;
    int count_words = 0;
};


int main (int argc, char* argv[])
{
    std::string name_in = argv[1];
    std::string name_out = argv[2];
    Parser parser;
    parser.reading_file(name_in);
    parser.process_map();
    parser.write_file(name_out);
    return 0;

}