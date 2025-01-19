#include <iostream>
#include "DataWriter.h"
#include <fstream>

DataWriter::DataWriter() : count_sec(0) {}


void DataWriter::init_stream(const std::string name_out_file) {
    out_ = std::make_unique<std::ofstream>(name_out_file, std::ios::binary);
}

void DataWriter::write_header(WavHeader & header) {
    if (!out_->is_open()) {
        throw std::runtime_error("Не удалось открыть файл для записи");
    }
    out_->write(reinterpret_cast<char*>(&header), sizeof(WavHeader));
}

void DataWriter::write_sample(std::vector<short int> samples_sec, int count_samples) {
    out_->write(reinterpret_cast<char*>(samples_sec.data()), sizeof(short int)*count_samples);
}



