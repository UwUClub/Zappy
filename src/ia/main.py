import sys
from .parser import parse
from .player import Player


def main():
    player = Player()
    info = parse(sys.argv)
    if info is None:
        exit(84)
    if player.connect(info) == -1:
        exit(84)
    player.setTeamName(info._name)
    player.preliminaries()
    player.forward()
    player.right()
    player.left()
    player.connectNbr()
    player.disconnect()
