#pragma once

#include <iostream>

namespace Zappy::GUI {
    class ParserData
    {
        public:
            ParserData(const std::string &aAddress, unsigned int aPort, const std::string &aClientName);
            ~ParserData() = default;

            /**
             * @brief update the address, port and machine name
             * @param aArgv
             * @param aArgc
             */
            void parseData(int aArgc, char **aArgv);

            /**
             * @brief get the address
             * @return std::string
             */
            [[nodiscard]] const std::string &getAddress() const;

            /**
             * @brief get the port
             * @return unsigned int
             */
            [[nodiscard]] unsigned int getPort() const;

            /**
             * @brief return the machine name
             * @return std::string
             */
            [[nodiscard]] const std::string &getClientName() const;

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
                    explicit ParserException(const std::string &aMessage)
                        : _message(aMessage)
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
            std::string _clientName;
    };
} // namespace Zappy::GUI