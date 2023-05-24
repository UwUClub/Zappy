import getopt


class Config:
    def __init__(self):
        self.host = "localhost"
        self.port = 0
        self.name = ""


def usage(bin_name):
    print("USAGE: " + bin_name + " -p port -n name -h machine")
    print("\tport\tis the port number")
    print("\tname\tis the name of the team")
    print("\tmachine\tis the name of the machine; localhost by default")


def help_def(argv):
    for flag in argv:
        if flag == "-help":
            usage(argv[0])
            return True
    return False


def parse(argv):
    if help_def(argv):
        return None
    try:
        opts, args = getopt.getopt(argv[1:], "p:n:h:", ["port=", "name=", "host="])
    except getopt.GetoptError:
        usage(argv[0])
        return None
    config = Config()
    for opt, arg in opts:
        if opt in "-p":
            config.port = arg
        elif opt in "-n":
            config.name = arg
        elif opt in "-h":
            config.host = arg
    return config
