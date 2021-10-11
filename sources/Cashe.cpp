// Copyright 2021 Daria <photodoshfy@gmail.com>

#include <Cashe.hpp>
#include <algorithm>
#include <iostream>

using namespace std;

Cashe::Cashe() {
    for (size_t i= 1.0 / 2 * casheSize[0]; i < 3.0 / 2 * casheSize[2]; i*=2)
        bufsize.push_back(i);
    bufsize.push_back(3.0 / 2 * casheSize[2]);
}
void Cashe::print_experiments(const Cashe& c, std::ostream& os) {
    os << "investigation:\n"
       << "\ttravel_order: " << c.traverse << "\n"
       << "\texperiments:\n";
    for (size_t i= 0; i < c.bufsize.size(); ++i) {
        os << "\t- experiment: \n"
           << "\t\tnumber: " << i+1 << "\n"
           << "\t\tinput_data:\n"
           << "\t\t\tbuffer_size: " << c.bufsize[i] / 1024 << " Kb\n"
           << "\t\tresults:\n"
           << "\t\t\tduration: " << c.traverse_time[i] << " ms\n";
    }
}
void Cashe::Cdirect() {
    int k;
    traverse= "direct";
    if (!traverse_time.empty())
        traverse_time.clear();
    for (const size_t& i : bufsize) {
        int* arr= new int[i/4];
        for (size_t j= 0; j < i/4; j += 16)
            k= arr[j];
        clock_t start= clock();
        for (size_t n= 0; n < 1000; n++) {
            for (size_t j= 0; j < i/4; j += 16)
                k= arr[j];
        }
        clock_t end= clock();
        traverse_time.push_back(static_cast <double> (end-start) / CLOCKS_PER_SEC * 1000);
        delete[] arr;
        k++;
    }
}
void Cashe::Creverse() {
    int k;
    traverse= "reverse";
    if (!traverse_time.empty())
        traverse_time.clear();
    for (const size_t& i : bufsize) {
        int* arr= new int[i/4];
        for (size_t j= i/4; j > 0; j -= 16)
            k= arr[j - 1];
        clock_t start= clock();
        for (size_t n= 0; n < 1000; n++) {
            for (size_t j= i/4; j > 0; j -= 16)
                k= arr[j - 1];
        }
        clock_t end= clock();
        traverse_time.push_back(static_cast <double> (end - start) / CLOCKS_PER_SEC * 1000);
        delete[] arr;
        k++;
    }
}
void Cashe::Crandom() {
    int k;
    traverse= "random";
    if (!traverse_time.empty())
        traverse_time.clear();
    for (const size_t& i : bufsize) {
        std::vector<size_t> rand_values;
        int* arr= new int[i/4];
        for (size_t j= 0; j < i/4; j += 16) {
            k= arr[j];
            rand_values.push_back(j);
        }
        random_shuffle(rand_values.begin(), rand_values.end());
        clock_t start = clock();
        for (size_t n= 0; n < 1000; n++) {
            for (const auto& index : rand_values)
                k= arr[index];
        }
        clock_t end= clock();
        traverse_time.push_back(static_cast <double> (end - start) / CLOCKS_PER_SEC * 1000);
        delete[] arr;
        k++;
    }
}