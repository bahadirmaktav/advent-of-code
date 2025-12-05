#include <iostream>
#include <string>
#include <cstdint>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_set>
#include <algorithm>

uint64_t SolvePart1(const std::vector<std::pair<uint64_t, uint64_t>>& ranges, const std::vector<uint64_t>& nums) {
    // Brute Force
    uint64_t answer{};
    for (const auto& num : nums) {
        for (const auto& [min, max] : ranges) {
            if (min <= num && max >= num) {
                answer++;
                break;
            }
        }
    }
    return answer;
}

// Pass by value used here, because ranges vector will be sorted inside the function.
uint64_t SolvePart2(std::vector<std::pair<uint64_t, uint64_t>> ranges) {
    // Algorithm
    std::sort(ranges.begin(), ranges.end());
    std::vector<std::pair<uint64_t, uint64_t>> merged_ranges;
    uint64_t min_tmp = ranges[0].first;
    uint64_t max_tmp = ranges[0].second;
    for (size_t i = 1; i < ranges.size(); ++i) {
        if (ranges[i].first > max_tmp) {
            merged_ranges.emplace_back(std::make_pair(min_tmp, max_tmp));
            min_tmp = ranges[i].first;
            max_tmp = ranges[i].second;
            continue;
        } else if (ranges[i].second > max_tmp) {
            max_tmp = ranges[i].second;
        }
    }
    merged_ranges.emplace_back(std::make_pair(min_tmp, max_tmp));

    uint64_t answer{};
    for (const auto& [min, max] : merged_ranges) {
        answer += (max - min + 1);
    }
    return answer;
}


int main() {
    // Get input ranges
    std::vector<std::pair<uint64_t, uint64_t>> ranges;
    std::ifstream input_ranges_file("que5_inputs_ranges.txt");
    std::string line{};
    if (input_ranges_file.is_open()) {
        while (std::getline(input_ranges_file, line)) {
            std::stringstream line_ss{line};
            std::string range_str{};
            std::pair<uint64_t, uint64_t> range_pair{};
            if (std::getline(line_ss, range_str, '-'))
                range_pair.first = std::stoull(range_str);
            if (std::getline(line_ss, range_str, '-'))
                range_pair.second = std::stoull(range_str);
            ranges.emplace_back(range_pair);
        }
    } else {
        std::cout << "File could not be opened!\n";
    }
    input_ranges_file.close();

    // Get input nums
    std::vector<uint64_t> nums;
    std::ifstream input_nums_file("que5_inputs_nums.txt");
    if (input_nums_file.is_open()) {
        while (std::getline(input_nums_file, line)) {
            nums.emplace_back(std::stoull(line));
        }
    } else {
        std::cout << "File could not be opened!\n";
    }
    input_nums_file.close();

    // Calculate and print answers
    std::cout << "Answer Part 1 : " << SolvePart1(ranges, nums) << std::endl;
    std::cout << "Answer Part 2 : " << SolvePart2(ranges) << std::endl;

    return 0;
}