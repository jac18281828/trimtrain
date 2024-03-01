#include <iostream>
#include <cstdlib>

#include "trimtrain.h"

int main(int argc, char *argv[])
{
    const auto expected_args = trimtrain::parse_args(argc, argv);
    if (!expected_args.has_value())
    {
        std::cerr << expected_args.error() << std::endl;
        return EXIT_FAILURE;
    }

    auto parser = trimtrain::TrimmerParser(expected_args.value().separator);
    constexpr auto buffer_size = 1024;

    while (!std::cin.eof())
    {
        const char c = std::cin.get();
        parser.push(c);

        if (parser.size() > buffer_size)
        {
            while (parser.size() > 1)
            {
                const auto oc = parser.pop();
                if (oc.has_value())
                {
                    std::cout << oc.value();
                }
            }
        }
    }

    while (!parser.empty())
    {
        const auto oc = parser.pop();
        if (oc.has_value())
        {
            std::cout << oc.value();
        }
    }

    return EXIT_SUCCESS;
}