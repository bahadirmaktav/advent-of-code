
#include <iostream>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cstdint>
#include <numeric>

// Part 1 validity check
bool CheckValidity1(const std::string& tag) {
    size_t len = tag.size();
    if (len % 2 != 0)
        return true;
    size_t half_len = len / 2;
    if (tag.substr(0, half_len) == tag.substr(half_len, half_len))
        return false;
    return true;
}

// Part 2 validity check
bool CheckValidity2(const std::string& tag) {
    size_t len = tag.size();
    for (size_t wlen = 1; wlen < len; ++wlen) {
        size_t index = wlen;
        while (index <= len - wlen) {
            if (tag.substr(index, wlen) != tag.substr(index - wlen, wlen))
                break;
            index += wlen;
            if (index == len)
                return false;
        }
    }
    return true;
}

int main(int, char**){
    std::vector<std::array<std::string, 2>> tag_ranges {
        {"492410748", "492568208"},
        {"246", "390"},
        {"49", "90"},
        {"16", "33"},
        {"142410", "276301"},
        {"54304", "107961"},
        {"12792", "24543"},
        {"3434259704", "3434457648"},
        {"848156", "886303"},
        {"152", "223"},
        {"1303", "1870"},
        {"8400386", "8519049"},
        {"89742532", "89811632"},
        {"535853", "567216"},
        {"6608885", "6724046"},
        {"1985013826", "1985207678"},
        {"585591", "731454"},
        {"1", "13"},
        {"12067202", "12233567"},
        {"6533", "10235"},
        {"6259999", "6321337"},
        {"908315", "972306"},
        {"831", "1296"},
        {"406", "824"},
        {"769293", "785465"},
        {"3862", "5652"},
        {"26439", "45395"},
        {"95", "136"},
        {"747698990", "747770821"},
        {"984992", "1022864"},
        {"34", "47"},
        {"360832", "469125"},
        {"277865", "333851"},
        {"2281", "3344"},
        {"2841977", "2953689"},
        {"29330524", "29523460"},
    };

    // Get invalid results
    std::vector<std::string> results;
    for (const auto& tag_range : tag_ranges) {
        for (uint64_t tag = std::stoull(tag_range[0]); tag <= std::stoull(tag_range[1]); ++tag) {
            if (!CheckValidity2(std::to_string(tag))) {
                results.emplace_back(std::to_string(tag));
            }
        }
    }

    // Sum numbers can be higher than 64 bit
    std::string rev_ans{};
    uint64_t sum = 0;
    for (size_t i = 0; i < 20; ++i) {
        for (const auto& res : results) {
            if (i < res.size()) {
                std::string numstr{res[res.size() - i - 1]};
                sum += std::stoull(numstr);
            }
        }
        rev_ans += std::to_string(sum % 10);
        sum /= 10;
    }

    // Print reverse sum
    for (size_t i = rev_ans.size(); i > 0; --i) {
        std::cout << rev_ans[i - 1];
    }

    return 1;
}
