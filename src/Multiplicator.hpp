#pragma once

#ifndef MULTIPLICATOR_HPP
    #define MULTIPLICATOR_HPP

    #include <regex>

    namespace MullItOver
    {
        class Multiplicator
        {
            public:
                static int calculatePartOne(const std::string &input)
                {
                    return (sumSubStrings(input));
                }

                static int calculatePartTwo(const std::string &input)
                {
                    std::regex before_keyword_regex(R"(^(.*?)\b(do\(\)|don't\(\)))");
                    std::regex between_do_regex(R"(do\(\)(.*?)(?=do\(\)|don't\(\)|$))");

                    std::smatch matches;
                    std::string result;
                    std::string::const_iterator searchStart(input.cbegin());
                    if (std::regex_search(searchStart, input.cend(), matches, before_keyword_regex)) {
                        result += matches[1].str();
                        searchStart = matches.suffix().first;
                    }

                    while (std::regex_search(searchStart, input.cend(), matches, between_do_regex)) {
                        result += matches[1].str();
                        searchStart = matches.suffix().first;
                    }

                    return (sumSubStrings(result));
                }

            private:
                static int sumSubStrings(const std::string &input)
                {
                    std::regex pattern(R"(mul\((\d+),(\d+)\))");
                    std::smatch matches;
                    int result = 0;

                    std::string::const_iterator searchStart(input.cbegin());
                    while (std::regex_search(searchStart, input.cend(), matches, pattern)) {
                        int x = std::stoi(matches[1].str());
                        int y = std::stoi(matches[2].str());
                        result += x * y;
                        searchStart = matches.suffix().first;
                    }

                    return (result);
                }
        };
    }

#endif /* MULTIPLICATOR_HPP */
