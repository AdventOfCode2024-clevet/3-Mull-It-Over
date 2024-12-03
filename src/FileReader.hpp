#pragma once

#ifndef FILEREADER_HPP
    #define FILEREADER_HPP

    #include <fstream>
    #include <string>

    namespace MullItOver
    {
        class FileReader
        {
            public:
                explicit FileReader(const std::string &fileName);
                ~FileReader() = default;

                std::string readAll();

            private:
                std::ifstream input;
        };
    }

#endif /* FILEREADER_HPP */
