#include "ParserData.hpp"

namespace Zappy::GUI {
    ParserData::ParserData(std::string aAddress, int aPort, std::string aMachineName)
    {
        _address = aAddress;
        _port = aPort;
        _machineName = aMachineName;
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
            _port = std::stoi(argv[2]);
        } else if (myFirstOpt.compare("-h") == 0) {
            _machineName = argv[2];
        }
        if (argc > 3) {
            if (argv[3] != NULL && argv[4] != NULL) {
                mySecondOpt = argv[3];
                if (mySecondOpt.compare("-h") != 0 && mySecondOpt.compare("-p") != 0) {
                    throw ParserException("Invalid arguments given");
                }
                if (mySecondOpt.compare("-h") == 0) {
                    _machineName = argv[4];
                } else if (mySecondOpt.compare("-p") == 0) {
                    _port = std::stoi(argv[4]);
                }
            }
        }
        if (_port == 0) {
            throw ParserException("Invalid port given");
        }
        if (_machineName.empty()) {
            _machineName = "localhost";
        }
    }

    std::string ParserData::getAddress() const
    {
        return _address;
    }

    int ParserData::getPort() const
    {
        return _port;
    }

    std::string ParserData::getMachineName() const
    {
        return _machineName;
    }
} // namespace Zappy::GUI