#include "ParserData.hpp"
#include <getopt.h>

namespace Zappy::GUI {
    ParserData::ParserData(const std::string &aAddress, unsigned int aPort, const std::string &aClientName)
    {
        _address = aAddress;
        _port = aPort;
        _clientName = aClientName;
    }

    void ParserData::parseData(int argc, char **argv)
    {
        std::string myFirstOpt;
        std::string mySecondOpt;
        int opt = 0;

        while ((opt = getopt(argc, argv, "p:h:")) != -1) {
            switch (opt) {
                case 'p':
                    _port = static_cast<unsigned int>(std::stoi(optarg));
                    break;
                case 'h':
                    _clientName = optarg;
                    break;
                default:
                    throw ParserException("Invalid argument");
            }
        }
    }

    const std::string &ParserData::getAddress() const
    {
        return _address;
    }

    unsigned int ParserData::getPort() const
    {
        return _port;
    }

    const std::string &ParserData::getClientName() const
    {
        return _clientName;
    }
} // namespace Zappy::GUI