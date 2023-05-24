import getopt


## @brief Class that contains the configuration of the program
class Config:
    ## @brief Constructor
    def __init__(self):
        self._host = "localhost"
        self._port = 0
        self._name = ""


## @brief Print the usage of the program
## @param bin_name The name of the binary
## @return None
def usage(bin_name):
    print("USAGE: " + bin_name + " -p port -n name -h machine")
    print("\tport\tis the port number")
    print("\tname\tis the name of the team")
    print("\tmachine\tis the name of the machine; localhost by default")


## @brief Check if the help flag is present
## @param argv The arguments of the program
## @return True if the help flag is present, False otherwise
def help_def(a_argv):
    for my_flag in a_argv:
        if my_flag == "-help":
            usage(a_argv[0])
            return True
    return False


## @brief Parse the arguments of the program
## @param argv The arguments of the program
## @return The configuration of the program
def parse(a_argv):
    if help_def(a_argv):
        return None
    try:
        my_opts, my_args = getopt.getopt(a_argv[1:], "p:n:h:", ["port=", "name=", "host="])
    except getopt.GetoptError:
        usage(a_argv[0])
        return None
    my_config = Config()
    for my_opt, my_arg in my_opts:
        if my_opt in "-p":
            my_config.port = my_arg
        elif my_opt in "-n":
            my_config.name = my_arg
        elif my_opt in "-h":
            my_config.host = my_arg
    return my_config
