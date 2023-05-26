#include <getopt.h>
#include <map>
#include <string>

namespace Zappy::GUI {
    class GetOpt
    {
        public:
            GetOpt(int argc, char **argv);
            ~GetOpt();

            /**
             * @brief geting the options
             * @param void
             * @return options
             */
            std::map<std::string, std::string> getOptions() const;

            /**
             * @brief exception class for getOpt
             */
            class GetOptException : public std::exception
            {
                public:
                    /**
                     * @brief GetOptException constructor
                     * @param aMessage
                     */
                    GetOptException(const std::string &aMessage) : Message(aMessage)
                    {}
                    ~GetOptException() = default;

                    /**
                     * @brief return the message of the exception
                     * @return message
                     */
                    [[nodiscard]] const char *what() const noexcept override
                    {
                        return Message.c_str();
                    }

                private:
                    std::string Message;
            };

        private:
            std::map<std::string, std::string> Options;
    };
} // namespace Zappy::GUI