#include <iostream>
#include "DataSource.h"
#include "WavHeader.h"
#include <fstream>
DataSource::DataSource() : count_samples(0){}
void help_() {
    std::cout << "1. mix index start_sec" << std::endl
        << "2. mute start_sec end_sec" << std::endl
        << "3. vol sec_start sec_end coefficient" << std::endl;

}
int DataSource::process_run(int argc, char *argv[]) {
    if (argc < 5) {
        std::cout << "Передайте файлы" << std::endl;
        return -1;
    }
    int k = 1;
    if (static_cast<std::string>(argv[1]) == "-h") {
        help_();
        k++;
    }
    if(static_cast<std::string>(argv[k]) != "-c") {
        std::cout << "Некорректные ключи" << std::endl;
        return -1;
    }
    k++;
    config = static_cast<std::string>(argv[k]);
    k++;
    output = static_cast<std::string>(argv[k]);
    k++;
    std::vector<int> buffer(argc, 0);
    size_audio_data = buffer;
    int index = k;
    std::vector<int> count_processed_sec_(argc - index);
    std::fill(count_processed_sec_.begin(), count_processed_sec_.end(), 0);
    count_processed_sec = count_processed_sec_;
    while(index < argc) {
        auto input_ = std::make_unique<std::ifstream>(argv[index], std::ios::binary);
        if(!input_->is_open()) {
            throw std::runtime_error("Не удалось открыть WAV файл");
        }
        streams_.push_back(std::move(input_));
        read_wav_header(index - k);
        index++;
    }
    return 0;
}

std::vector<short int> DataSource::reading_samples(int index_file) {
    auto& file = streams_[index_file];
    std::vector<short int> samples;
    file->seekg(sizeof(WavHeader) + count_processed_sec[index_file] *
        count_samples*sizeof(short int), std::ios::beg);

    if (samples.size() < count_samples) {
        samples.resize(count_samples);
    }

    file->read(reinterpret_cast<char*>(samples.data()),
        count_samples*sizeof(short int));
    count_processed_sec[index_file]++;
    if (!index_file) {
        samples_sec = samples; // ???
    }

    return samples;

}

void DataSource::read_wav_header(int index_file) {
    WavHeader header;
    auto& file = streams_[index_file];
    if (!file->is_open()) {
        throw std::runtime_error("Не удалось открыть WAV файл");
    }
    file->read(reinterpret_cast<char*>(&header), sizeof(WavHeader));
    if (!index_file) {
        header_ = header;
    }
    count_samples = header.sampleRate;
    size_audio_data[index_file] = header.chunkSize/(sizeof(short int) * count_samples); // в секундах
}

std::string DataSource::get_config() {
    return config;
}


int& DataSource::get_processed_sec(const int index) {
    return count_processed_sec[index];
}

int DataSource::get_size_audio(const int index) const {
    return size_audio_data[index];
}

std::vector<short> & DataSource::get_samples_sec() {
    return samples_sec;
}

std::string DataSource::get_nameout() {
    return output;
}

int DataSource::get_count_samples() const {
    return count_samples;
}

WavHeader DataSource::get_header() const {
    return header_;
}


