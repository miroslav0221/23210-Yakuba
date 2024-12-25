#ifndef CSVPARSER_H
#define CSVPARSER_H
#include <tuple_printer.h>
#include <fstream>
#include <limits>
#include <tuple>
#include <iostream>


template<typename... Args>
class CSVParser {
private:

  std::ifstream& stream_;
  size_t current_line;
  size_t skip_lines_;

  void skip_lines() {
    for(size_t i = 0; i < skip_lines_; i++) {
      if(!stream_.ignore(std::numeric_limits<std::streamsize>::max(), '\n')) {
        throw std::exception();
      }
    }
  }


  public:
  class Iterator {

  private:
    bool is_ended;
    CSVParser& parser;
    std::shared_ptr<std::tuple<Args...>> tuple;
  public:

    Iterator(CSVParser& parser, const bool end) : is_ended(end), parser(parser) {
        if(end) {
            tuple = nullptr;
        }
        else {
            put_in_tuple();
        }
    }

    std::tuple<Args...>& operator*() {
      return *tuple;
    }

    Iterator operator++() {
      Iterator tmp = *this;
      put_in_tuple();
      return tmp;
    }

    bool operator==(const Iterator& other) {
      return tuple == other.tuple;
    }
    bool operator!=(const Iterator& other) {
      return tuple != other.tuple;
    }



    private:

    std::string read_row() {
      std::string row;
      std::getline(parser.stream_, row);
      ++parser.current_line;
      return row;
    }

    std::vector<std::string> get_data(const std::string& row) {
      std::vector<std::string> data;
      std::string elem;
      for(const char& symbol : row) {
        if(symbol == EOF) {
          is_ended = true;
          break;
        }
        if(symbol == '\n') {
          break;
        }

        if(symbol == ';' or symbol == ',') {
          data.push_back(elem);
          elem.clear();
          continue;
        }
        elem.push_back(symbol);
      }
      if(!elem.empty()) {
        data.push_back(elem);
      }
      return data;
    }

    void put_in_tuple() {
      const std::string row = read_row();
      if(row.empty()) {
        tuple = nullptr;
        is_ended = true;
      }
      else {
        try {
          auto tmp = create_tuple<Args...>(get_data(row));
          tuple = std::make_shared<std::tuple<Args...>>(tmp);
        }
        catch (const std::invalid_argument& error) {
          std::ostringstream error_mes;
          error_mes << error.what() << ", line:" << parser.current_line;
          throw std::runtime_error(error_mes.str());
        }
      }
    }
  };

  explicit CSVParser(std::ifstream& stream, const size_t skip_lines = 0) : stream_(stream),
  current_line(0), skip_lines_(skip_lines) {
    if(!stream.is_open()) {
      throw std::ifstream::failure("no input file");
    }
  }

  Iterator begin() {
    skip_lines();
    return Iterator(*this, false);
  }

  Iterator end() {
    return Iterator(*this, true);
  }

};


#endif
