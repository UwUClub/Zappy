import pytest
from player import Player
from parser import parse, Config

# Test if the player is correctly initialized
def test_player_init():
    player = Player()
    assert player._socket == None
    assert player._teamName == None
    assert player._functionIndex == 0
    assert player._functionList == [self.goToLevel2, self.goToLevel3, self.goToLevel4, self.goToLevel5, self.goToLevel6, self.goToLevel7, self.goToLevel8]
    assert player._lookTiles == []
    assert player._inventory == [0, 0, 0, 0, 0, 0, 0]
    assert player._lastReceivedMessage == ""
    assert player._direction == 0
    assert player._parsedMessage == ""

# Test if the player isn´t connected when sending None or a string that isn´t a ip address
def test_player_cant_connect():
    player = Player()
    assert player.connect(None) == -1
    assert player.connect("test") == -1

# Test if the player is correctly connected
def test_player_connect():
    player = Player()
    config = Config()
    config._host = "localhost"
    config._port = 4242
    config._name = "test"
    assert player.connect(config) == 0