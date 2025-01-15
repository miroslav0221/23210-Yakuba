#ifndef DATAWRITER_H
#define DATAWRITER_H
#include <iostream>
#include "WavHeader.h"

class DataWriter {
private:
    std::unique_ptr<std::ofstream> out_;
    int count_sec;
public:
    DataWriter();
    void init_stream(const std::string name_out_file);
    void write_sample(std::vector<short int> samples_sec, int count_samples);
    void write_header(WavHeader & header);
};


#endif
