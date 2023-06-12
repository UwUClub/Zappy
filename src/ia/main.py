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
    while player._functionIndex < 1:
        player.level2()
    player.disconnect()
