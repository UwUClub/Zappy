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
def helpDef(aArgv):
    for myFlag in aArgv:
        if myFlag == "-help":
            usage(aArgv[0])
            return True
    return False


## @brief Parse the arguments of the program
## @param argv The arguments of the program
## @return The configuration of the program
def parse(aArgv):
    if helpDef(aArgv):
        return None
    try:
        myOpts, myArgs = getopt.getopt(aArgv[1:], "p:n:h:", ["port=", "name=", "host="])
    except getopt.GetoptError:
        usage(aArgv[0])
        return None
    myConfig = Config()
    for myOpt, myArg in myOpts:
        if myOpt in "-p":
            myConfig.port = myArg
        elif myOpt in "-n":
            myConfig.name = myArg
        elif myOpt in "-h":
            myConfig.host = myArg
    return myConfig
