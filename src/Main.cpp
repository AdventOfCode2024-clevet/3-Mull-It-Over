#include <iostream>

#include "ArgumentParser.hpp"
#include "FileReader.hpp"
#include "Multiplicator.hpp"

int main(int argc, char* argv[]) {
    try {
        MullItOver::ArgumentParser parser(argc, argv);

        MullItOver::FileReader reader(parser.getInputFile());
        auto input = reader.readAll();

        int result = 0;
        switch (parser.getPart()) {
            case 1:
                result = MullItOver::Multiplicator::calculatePartOne(input);
                std::cout << "Result (part 1): " << result << std::endl;
                break;
            case 2:
                result = MullItOver::Multiplicator::calculatePartTwo(input);
                std::cout << "Result (part 2): " << result << std::endl;
                break;
            default:
                throw std::runtime_error("Error: part must be 1 or 2");
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return (1);
    }

    return (0);
}
