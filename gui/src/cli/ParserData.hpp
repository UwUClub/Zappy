#include <iostream>

namespace Zappy::GUI {
class ParserData
{
  public:
    ParserData(std::string aAddress, int aPort, std::string aMachineName);
    ~ParserData() = default;

    /**
     * @brief update the address, port and machine name
     * @return void
     * @param argc, argv
     */
    void parseData(int argc, char **argv);

    /**
     * @brief return the address
     * @return std::string
     * @param void
     */
    std::string getAddress() const;

    /**
     * @brief return the port
     * @return int
     * @param void
     */
    int getPort() const;

    /**
     * @brief return the machine name
     * @return std::string
     * @param void
     */
    std::string getMachineName() const;

    /**
     * @brief exception class for parser
     */
    class ParserException : public std::exception
    {
      public:
        explicit ParserException(const std::string &aMessage) : _message(aMessage) {}

        ~ParserException() override = default;

        [[nodiscard]] const char *what() const noexcept override { return _message.c_str(); }

      private:
        std::string _message;
    };

  private:
    std::string _address;
    int _port;
    std::string _machineName;
};
}// namespace Zappy::GUI