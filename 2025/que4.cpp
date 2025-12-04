#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <queue>
#include <cstdint>
#include <fstream>

struct Cell {
    std::vector<Cell*> adjs;
    bool is_roll = false;
    bool will_removed = false;
    std::string char_to_print{};
};

constexpr uint8_t MAX_ROLL_TO_REMOVE = 4;

int main(int, char**) {
    // Get input to 2D vector
    std::ifstream file("que4_inputs.txt");
    std::string line{};
    std::vector<std::vector<Cell*>> input_cells;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::vector<Cell*> tmp_row_vec;
            for (const auto c : line) {
                Cell* tmp_cell = new Cell();
                if (c == '@')
                    tmp_cell->is_roll = true;
                tmp_row_vec.emplace_back(tmp_cell);
            }
            input_cells.emplace_back(tmp_row_vec);
        }
    } else {
        std::cout << "File not opened!\n";
    }

    // Set adjacents
    size_t row_len = input_cells.size();
    size_t col_len = input_cells[0].size();
    for (int i = 0; i < row_len; ++i) {
        for (int j = 0; j < col_len; ++j) {
            input_cells[i][j]->char_to_print = input_cells[i][j]->is_roll ? "@" : ".";
            Cell* tmp_cell = input_cells[i][j];
            if (i > 0) tmp_cell->adjs.push_back(input_cells[i - 1][j]);
            if (i > 0 && j + 1 < col_len) tmp_cell->adjs.push_back(input_cells[i - 1][j + 1]);
            if (j + 1 < col_len) tmp_cell->adjs.push_back(input_cells[i][j + 1]);
            if (i + 1 < row_len && j + 1 < col_len) tmp_cell->adjs.push_back(input_cells[i + 1][j + 1]);
            if (i + 1 < row_len) tmp_cell->adjs.push_back(input_cells[i + 1][j]);
            if (i + 1 < row_len && j > 0) tmp_cell->adjs.push_back(input_cells[i + 1][j - 1]);
            if (j > 0) tmp_cell->adjs.push_back(input_cells[i][j - 1]);
            if (i > 0 && j > 0) tmp_cell->adjs.push_back(input_cells[i - 1][j - 1]);
        }
    }

    // Brute force
    uint64_t ans{0};
    uint64_t old_ans{1};
    while(old_ans != ans) {
        old_ans = ans;
        // Find movable rolls
        for (int i = 0; i < row_len; ++i) {
            for (int j = 0; j < col_len; ++j) {
                if (!input_cells[i][j]->is_roll)
                    continue;
                uint8_t adj_roll_count{};
                for (auto adj : input_cells[i][j]->adjs) {
                    if (adj->is_roll) {
                        adj_roll_count++;
                    }
                }
                if (adj_roll_count < MAX_ROLL_TO_REMOVE) {
                    ans++;
                    input_cells[i][j]->will_removed = true;
                    input_cells[i][j]->char_to_print = "x";
                }
            }
        }
        // Remove found rolls
        for (int i = 0; i < row_len; ++i) {
            for (int j = 0; j < col_len; ++j) {
                if (input_cells[i][j]->will_removed) {
                    input_cells[i][j]->is_roll = false;
                    input_cells[i][j]->will_removed = false;
                }
            }
        }
    }

    // Print the answer
    std::ofstream test_file("que4_answer.txt");
    for (const auto& block : input_cells) {
        for (const auto& cell : block) {
            test_file << cell->char_to_print;
        }
        test_file << "\n";
    }
    test_file.close();

    std::cout << "Answer : " << ans << std::endl;

    return 1;
}