#include <iostream>

namespace Zappy::GUI {
    class ParserData
    {
        public:
            ParserData(std::string aAddress, unsigned int aPort, std::string aMachineName);
            ~ParserData() = default;

            /**
             * @brief update the address, port and machine name
             * @param argv
             * @param argc
             */
            void parseData(int argc, char **argv);

            /**
             * @brief get the address
             * @return std::string
             */
            [[nodiscard]] std::string getAddress() const;

            /**
             * @brief get the port
             * @return unsigned int
             */
            [[nodiscard]] unsigned int getPort() const;

            /**
             * @brief return the machine name
             * @return std::string
             */
            [[nodiscard]] std::string getMachineName() const;

            /**
             * @brief exception class for parser
             */
            class ParserException : public std::exception
            {
                public:
                    /**
                     * @brief ParserException constructor
                     * @param aMessage
                     */
                    explicit ParserException(const std::string &aMessage) : _message(aMessage)
                    {}

                    /**
                     * @brief ParserException destructor
                     */
                    ~ParserException() override = default;

                    /**
                     * @brief return the message of the exception
                     * @return message
                     */
                    [[nodiscard]] const char *what() const noexcept override
                    {
                        return _message.c_str();
                    }

                private:
                    std::string _message;
            };

        private:
            std::string _address;
            unsigned int _port;
            std::string _machineName;
    };
} // namespace Zappy::GUI