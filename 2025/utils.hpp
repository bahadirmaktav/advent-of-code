#include <string>
#include <vector>
#include <cstdint>

#define MAX_DIGIT_LENGTH 20

std::string HighDigitSum(const std::vector<std::string>& values) {
    // Sum numbers can be higher than 64 bit
    std::string rev_ans{};
    uint64_t sum{};
    for (size_t i = 0; i < MAX_DIGIT_LENGTH; ++i) {
        for (const auto& res : values) {
            if (i < res.size()) {
                std::string numstr{res[res.size() - i - 1]};
                sum += std::stoull(numstr);
            }
        }
        rev_ans += std::to_string(sum % 10);
        sum /= 10;
    }
    
    // Get correct result by reversing the reversed answer
    std::string ans{};
    for (size_t i = rev_ans.size(); i > 0; --i) {
        ans += rev_ans[i - 1];
    }

    return ans;
}