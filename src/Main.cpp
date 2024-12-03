#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>
#include <regex>
#include <numeric>

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

    // Join all lines into a single string
    std::string input_string = std::accumulate(lines.begin(), lines.end(), std::string(""));

    // In each line we must identify the pattern mul(X,Y) and sum the mltiplication to the result
    // Ex: xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5)) -> 2*4 + 5*5 + 11*8 + 8*5

    // std::regex pattern(R"(mul\((\d+),(\d+)\))");
    // std::smatch matches;
    // int result = 0;

    // for (const auto& line : lines) {
    //     std::string::const_iterator searchStart(line.cbegin());
    //     while (std::regex_search(searchStart, line.cend(), matches, pattern)) {
    //         int x = std::stoi(matches[1].str());
    //         int y = std::stoi(matches[2].str());
    //         result += x * y;
    //         searchStart = matches.suffix().first;
    //     }
    // }

    // std::cout << "Result: " << result << std::endl;

    // Part two
    // std::string input = "xmul(2,4)&mul[3,7]!^do()mul(8,4)do()mul(5,3)don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))";

    // Expression régulière pour capturer avant le premier "do()" ou "don't()"
    std::regex before_keyword_regex(R"(^(.*?)\b(do\(\)|don't\(\)))");
    // Expression régulière pour capturer chaque segment après un "do()"
    std::regex between_do_regex(R"(do\(\)(.*?)(?=do\(\)|don't\(\)|$))");

    // // Partie avant le premier "do()" ou "don't()"
    // std::smatch match;
    // if (std::regex_search(input, match, before_keyword_regex)) {
    //     std::cout << "Avant do() ou don't():\n" << match[1] << "\n";
    // }

    // // Capturer chaque segment après un "do()"
    // auto it = std::sregex_iterator(input.begin(), input.end(), between_do_regex);
    // auto end = std::sregex_iterator();

    // std::cout << "Entre do() et don't() ou jusqu'à la fin:\n";
    // for (; it != end; ++it) {
    //     std::string segment = (*it)[1].str(); // Capturer le groupe (.*?)
    //     std::cout << segment << "\n";
    // }

    std::vector<std::string> substrings;
    // for (const auto& line : lines) {
        // Partie avant le premier "do()" ou "don't()"
        std::smatch match;
        if (std::regex_search(input_string, match, before_keyword_regex)) {
            substrings.push_back(match[1]);
        }

        // Capturer chaque segment après un "do()"
        auto it = std::sregex_iterator(input_string.begin(), input_string.end(), between_do_regex);
        auto end = std::sregex_iterator();

        for (; it != end; ++it) {
            std::string segment = (*it)[1].str(); // Capturer le groupe (.*?)
            substrings.push_back(segment);
        }
    // }

    // Print all substrings
    // for (const auto& substring : substrings) {
    //     std::cout << substring << std::endl;
    // }

    // Result
    int result = 0;
    std::regex pattern(R"(mul\((\d+),(\d+)\))");
    std::smatch matches;

    for (const auto& substring : substrings) {
        std::string::const_iterator searchStart(substring.cbegin());
        while (std::regex_search(searchStart, substring.cend(), matches, pattern)) {
            int x = std::stoi(matches[1].str());
            int y = std::stoi(matches[2].str());
            result += x * y;
            searchStart = matches.suffix().first;
        }
    }

    std::cout << "Result: " << result << std::endl;

    return (0);
}
