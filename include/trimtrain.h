#pragma once

#include <iostream>
#include <expected>
#include <optional>
#include <string>
#include <queue>

namespace trimtrain
{
    struct Args
    {
        char separator;
    };

    class TrimmerParser
    {
    private:
        const char separator;
        bool is_white = false;
        std::queue<char> buffer;

    public:
        TrimmerParser() : separator(' ') {}
        explicit TrimmerParser(char separator) : separator(separator) {}

        bool empty() const
        {
            return buffer.empty();
        }

        size_t size() const
        {
            return buffer.size();
        }

        void push(const char c)
        {
            switch (c)
            {
            case ' ':
            case '\t':
                if (buffer.empty() || buffer.back() == separator)
                {
                    break;
                }
                is_white = true;
                break;
            case '\n':
                buffer.push('\n');
                is_white = false;
                break;
            default:
                if (is_white)
                {
                    buffer.push(separator);
                    is_white = false;
                }
                buffer.push(c);
                break;
            }
        }

        std::optional<char> pop()
        {
            if (buffer.empty())
            {
                return std::nullopt;
            }
            auto c = buffer.front();
            buffer.pop();
            return c;
        }
    };

    std::expected<Args, std::string>
    parse_args(int argc, char *argv[])
    {
        Args args{' '};

        if (argc == 1)
        {
            return args;
        }

        if (argv[1][0] != '-' || std::string("--help") == argv[1] || std::string("-h") == argv[1])
        {
            auto error_msg = "Usage: " + std::string(argv[0]) + " [-s<separator> value]";
            return std::unexpected(error_msg);
        }
        for (int i = 1; i < argc; ++i)
        {
            if (argv[i][0] == '-')
            {
                switch (argv[i][1])
                {
                case 's':
                    if (i + 1 >= argc)
                    {
                        auto error_msg = "Missing value for option: " + std::string(argv[i]);
                        return std::unexpected(error_msg);
                    }
                    args.separator = argv[i + 1][0];
                    break;
                default:
                    auto error_msg = "Unknown option: " + std::string(argv[i]);
                    return std::unexpected(error_msg);
                }
            }
        }
        return args;
    }
}