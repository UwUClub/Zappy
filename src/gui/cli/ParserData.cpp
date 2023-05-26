#include "ParserData.hpp"

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

        if (argc < 3) {
            throw ParserException("Not enough arguments");
        }
        if (argv[1] == NULL || argv[2] == NULL) {
            throw ParserException("Invalid arguments given");
        }
        myFirstOpt = argv[1];
        if (myFirstOpt.compare("-p") != 0 && myFirstOpt.compare("-h") != 0) {
            throw ParserException("Invalid arguments given");
        }
        if (myFirstOpt.compare("-p") == 0) {
            _port = static_cast<unsigned int>(std::stoi(argv[2]));
        } else if (myFirstOpt.compare("-h") == 0) {
            _clientName = argv[2];
        }
        if (argc > 3) {
            if (argv[3] != NULL && argv[4] != NULL) {
                mySecondOpt = argv[3];
                if (mySecondOpt.compare("-h") != 0 && mySecondOpt.compare("-p") != 0) {
                    throw ParserException("Invalid arguments given");
                }
                if (mySecondOpt.compare("-h") == 0) {
                    _clientName = argv[4];
                } else if (mySecondOpt.compare("-p") == 0) {
                    _port = static_cast<unsigned int>(std::stoi(argv[4]));
                }
            }
        }
        if (_port == 0) {
            throw ParserException("Invalid port given");
        }
        if (_clientName.empty()) {
            _clientName = "localhost";
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