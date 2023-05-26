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

        GetOpt myGetOpt(argc, argv);
        std::map<std::string, std::string> myOptions = myGetOpt.getOptions();
        if (myOptions.find("port") != myOptions.end()) {
            _port = (std::stoi(myOptions["port"]));
        } else {
            throw ParserException("Port is missing");
        }
        if (myOptions.find("machine") != myOptions.end()) {
            _machineName = myOptions["machine"];
        } else {
            _machineName = "localhost";
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