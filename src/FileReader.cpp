#include "FileReader.hpp"

MullItOver::FileReader::FileReader(const std::string &fileName)
{
    input.open(fileName);
    if (!input.is_open())
    {
        throw std::runtime_error("Error: could not open file " + fileName);
    }
}

std::string MullItOver::FileReader::readAll()
{
    std::string line;
    std::string content;

    while (std::getline(input, line))
    {
        content += line;
    }

    return (content);
}
