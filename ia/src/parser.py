def help_def(argv):
    for flag in argv:
        if flag == "-help":
            usage(argv[0])
            return True
    return False


def get_info(info, argv, i):
    keys = {
        "-p": "port",
        "-n": "name",
        "-h": "host"
    }
    args = ["-p", "-n", "-h"]

    for argument in args:
        if argv[i] == argument:
            info[keys[argument]] = argv[i + 1]
            return info
    return None


def usage(bin_name):
    print("USAGE: " + bin_name + " -p port -n name -h machine")
    print("\tport\tis the port number")
    print("\tname\tis the name of the team")
    print("\tmachine\tis the name of the machine; localhost by default")


def parse(argv):
    info = {
        "host": "localhost",
        "port": 0,
        "name": ""
    }

    if len(argv) == 1:
        return None
    if help_def(argv):
        exit(0)
    for i in range(1, len(argv)):
        if i % 2 == 1:
            info = get_info(info, argv, i)
        if info is None:
            usage(argv[0])
            return None
        return info
