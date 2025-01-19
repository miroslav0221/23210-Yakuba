#ifndef DATASOURCE_H
#define DATASOURCE_H
#include <iostream>
#include <fstream>
#include "WavHeader.h"

class DataSource {
private:
      std::string config;
      std::string output;
      std::vector<std::unique_ptr<std::ifstream>> streams_;
      std::vector<short int> samples_sec;
      std::vector<int> size_audio_data;
      std::vector<int> count_processed_sec;
      WavHeader header_;
      int count_samples;
public:
      DataSource();

      int process_run(int argc, char * argv[]);

      std::vector<short int> reading_samples(int index_file);

      void read_wav_header(int index_file);

      std::string get_config();

      int& get_processed_sec(const int index);

      int get_size_audio(const int index) const;

      std::string get_nameout();

      std::vector<int short> & get_samples_sec();

      int get_count_samples() const;

      WavHeader get_header() const;
};


#endif