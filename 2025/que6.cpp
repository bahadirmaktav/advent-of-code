#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdint>
#include <sstream>
#include <numeric>

uint64_t SolvePart1() {
    // Get numbers
    std::vector<std::vector<uint64_t>> nums; 
    std::ifstream input_file_nums("que6_inputs_nums.txt");
    std::string line{};
    if (input_file_nums.is_open()) {
        while (std::getline(input_file_nums, line)) {
            std::vector<uint64_t> tmp_vec;
            std::string num_str{};
            std::stringstream line_sstr{line};
            while (line_sstr >> num_str) {
                tmp_vec.emplace_back(std::stoull(num_str));
            }
            nums.emplace_back(tmp_vec);
        }
    } else {
        std::cout << "File could not be opened!\n";
    }
    input_file_nums.close();

    // Get operations
    std::vector<std::string> ops;
    std::ifstream input_file_ops("que6_inputs_ops.txt");
    if (input_file_ops.is_open()) {
        while (std::getline(input_file_ops, line)) {
            std::string op_str{};
            std::stringstream line_sstr{line};
            while (line_sstr >> op_str) {
                ops.emplace_back(op_str);
            }
        }
    } else {
        std::cout << "File could not be opened!\n";
    }
    input_file_ops.close();

    // Brute Force - Part 1
    std::vector<uint64_t> results = nums[0];
    for (size_t i = 1; i < nums.size(); ++i) {
        for (size_t j = 0; j < nums[0].size(); ++j) {
            if (ops[j] == "+") {
                results[j] += nums[i][j];
            } else if (ops[j] == "*") {
                results[j] *= nums[i][j];
            } else {
                std::cout << "Operation " << ops[j] << " is not defined!" << std::endl;
            }
        }
    }

    // Return the sum
    return std::accumulate(results.begin(), results.end(), uint64_t(0));
}

uint64_t SolvePart2() {
    // Get numbers as text
    std::vector<std::string> lines;
    std::ifstream input_file_nums("que6_inputs_nums.txt");
    std::string line{};
    if (input_file_nums.is_open()) {
        while (std::getline(input_file_nums, line)) {
            lines.emplace_back(line);
        }
    } else {
        std::cout << "File could not be opened!\n";
    }
    input_file_nums.close();

    // Get number groups as integers
    std::vector<std::vector<uint64_t>> num_grps;
    std::vector<uint64_t> num_grp;
    for (size_t j = 0; j < lines[0].size(); ++j) {
        std::string num_str{};
        for (size_t i = 0; i < lines.size(); ++i) {
            if (lines[i][j] != ' ') {
                num_str += lines[i][j];
            }
        }
        if (!num_str.empty()) {
            num_grp.emplace_back(std::stoull(num_str));
        } else {
            num_grps.emplace_back(num_grp);
            num_grp.clear();
        }
    }
    if (!num_grp.empty())
        num_grps.emplace_back(num_grp);

    // Get operations
    std::vector<std::string> ops;
    std::ifstream input_file_ops("que6_inputs_ops.txt");
    if (input_file_ops.is_open()) {
        while (std::getline(input_file_ops, line)) {
            std::string op_str{};
            std::stringstream line_sstr{line};
            while (line_sstr >> op_str) {
                ops.emplace_back(op_str);
            }
        }
    } else {
        std::cout << "File could not be opened!\n";
    }
    input_file_ops.close();

    // Brute Force - Part 2
    std::vector<uint64_t> results;
    for (size_t i = 0; i < num_grps.size(); ++i) {
        uint64_t res_tmp{num_grps[i][0]};
        for (size_t j = 1; j < num_grps[i].size(); ++j) {
            if (ops[i] == "+") {
                res_tmp += num_grps[i][j];
            } else if (ops[i] == "*") {
                res_tmp *= num_grps[i][j];
            } else {
                std::cout << "Operation " << ops[i] << " is not defined!" << std::endl;
            }
        }
        results.emplace_back(res_tmp);
    }

    // Return the sum
    return std::accumulate(results.begin(), results.end(), uint64_t(0));
}

int main() {
    std::cout << "Answer Part 1 : " << SolvePart1() << std::endl;
    std::cout << "Answer Part 2 : " << SolvePart2() << std::endl;

    return 0;
}