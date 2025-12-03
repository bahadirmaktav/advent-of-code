#include <iostream>
#include <string>
#include <cstdint>
#include <fstream>
#include <cmath>

#include "utils.hpp"

uint64_t GetMaxValue(const std::string& val, const size_t& dlen) {
    uint64_t res = 0;
    int lftm_ind = 0; // last selected left most index 
    for (int i = dlen; i > 0; --i) {
        int max_num = -1;
        int lftm_ind_tmp = lftm_ind;
        for (int k = val.size() - i; k >= lftm_ind; --k) {
            if (val[k] - 48 >= max_num) {
                max_num = val[k] - 48;
                lftm_ind_tmp = k;
            }
        }
        lftm_ind = lftm_ind_tmp + 1;
        res += (uint64_t)std::pow(10, i - 1) * max_num;
    }
    return res;
}


int main(int, char**) {
    std::ifstream file("que3_inputs.txt");
    std::string line{};
    constexpr size_t digit_length{12};
    std::vector<std::string> results;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            results.emplace_back(std::to_string(GetMaxValue(line, digit_length)));
        }
    } else {
        std::cout << "File not opened!\n";
    }

    // Print the sum
    std::cout << HighDigitSum(results) << std::endl;

    return 1;
}