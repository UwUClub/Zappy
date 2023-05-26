#include "GetOpt.hpp"

namespace Zappy::GUI {
    GetOpt::GetOpt(int argc, char **argv)
    {
        int opt;

        while ((opt = getopt(argc, argv, "p:h:")) != -1) {
            switch (opt) {
                case 'p':
                    Options["port"] = optarg;
                    break;
                case 'h':
                    Options["machine"] = optarg;
                    break;
                default:
                    throw GetOptException("Invalid argument");
            }
        }
    }

    GetOpt::~GetOpt()
    {}

    std::map<std::string, std::string> GetOpt::getOptions() const
    {
        return Options;
    }
} // namespace Zappy::GUI