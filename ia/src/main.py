import sys
from parser import parse
from player import Player

player = Player()


def main():
    info = parse(sys.argv)
    if info is None:
        exit(84)
    if player.connect(info) == -1:
        exit(84)


if __name__ == "__main__":
    main()
