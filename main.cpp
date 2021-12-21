// ~~ Task ~~
// There is a matrix filled with water. There are mines in some random places.
// Ship must move from left down corner (start point) to right up corner (end
// point). Ship can move only up and right with 1/2 probability for each
// direction. When ship moves to cell with mine - it is destroyed. Use Monte
// Carlo method to get probability of ship successfully reaching end point.

#include <array>
#include <cstdio>
#include <iostream>
#include <random>

constexpr int sea_size = 20;
using Matrix = std::array<std::array<char, sea_size>, sea_size>;
std::mt19937 generator;
std::random_device seed;

void fillMatrix(Matrix& sea, const char fill_symbol) {
    for (int i = 0; i != sea.size(); ++i) {
        for (int j = 0; j != sea.size(); ++j) {
            sea[i][j] = fill_symbol;
        }
    }
}

void generateRandomElements(Matrix& sea, const char element_symbol,
                            const int elements_count) {
    generator.seed(seed());
    std::uniform_int_distribution<int> dist(0, sea.size() - 1);

    int x = 0;
    int y = 0;
    for (int i = 0; i != elements_count; ++i) {
        x = dist(generator);
        y = dist(generator);
        while (sea[x][y] == element_symbol) {
            x = dist(generator);
            y = dist(generator);
        }

        sea[x][y] = element_symbol;
    }
}

bool movementTill(Matrix& sea, const char destination_symbol,
                  const char failure_symbol) {
    generator.seed(seed());
    std::bernoulli_distribution ber_dist;

    int x = 0;
    int y = 0;
    constexpr int movement_limit = 50000;
    for (int i = 0; i < movement_limit; ++i) {
        if (sea[x][y] == failure_symbol) return false;
        if (sea[x][y] == destination_symbol) return true;

        if (x == sea.size() - 1) {
            ++y;
            continue;
        }
        if (y == sea.size() - 1) {
            ++x;
            continue;
        }

        if (ber_dist(generator)) {
            ++x;
        } else {
            ++y;
        }
    }

    return false;
}

int main() {
    Matrix sea;

    constexpr int tests = 100000;
    int successes = 0;
    for (int i = 0; i != tests; ++i) {
        constexpr char water_symbol = '~';
        fillMatrix(sea, water_symbol);

        constexpr char mine_symbol = '*';
        constexpr int mines_count = 6;
        generateRandomElements(sea, mine_symbol, mines_count);

        constexpr char end_symbol = 'E';
        sea[sea.size() - 1][sea.size() - 1] = end_symbol;

        if (movementTill(sea, end_symbol, mine_symbol)) ++successes;
    }

    const float success_probability =
        (static_cast<float>(successes) / tests) * 100;

    std::cout << "Number of tests: " << tests << std::endl;
    std::cout << "Number of successes: " << successes << std::endl;
    std::cout << "Probability of ship reaching the end: " << success_probability
              << "%" << std::endl;

    // Keep console window open until you press any key.
    std::getchar();
}
