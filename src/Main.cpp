#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>
#include <regex>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input>" << std::endl;
        return (1);
    }

    // We need to read the input file
    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cerr << "Error: could not open file " << argv[1] << std::endl;
        return (1);
    }

    // Read the input file
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(input, line)) {
        lines.push_back(line);
    }

    // In each line we must identify the pattern mul(X,Y) and sum the mltiplication to the result
    // Ex: xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5)) -> 2*4 + 5*5 + 11*8 + 8*5

    std::regex pattern(R"(mul\((\d+),(\d+)\))");
    std::smatch matches;
    int result = 0;

    for (const auto& line : lines) {
        std::string::const_iterator searchStart(line.cbegin());
        while (std::regex_search(searchStart, line.cend(), matches, pattern)) {
            int x = std::stoi(matches[1].str());
            int y = std::stoi(matches[2].str());
            result += x * y;
            searchStart = matches.suffix().first;
        }
    }

    std::cout << "Result: " << result << std::endl;

    return (0);
}
