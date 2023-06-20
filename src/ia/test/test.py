from ..player import Player
from ..iaParser import parse, Config

#Test if the player is correctly initialized
def test_player_init():
    player = Player()
    assert player._socket == None
    assert player._name == ""
    assert player._functionIndex == 0
    assert player._functionList == [player.goToLevel2, player.goToLevel3, player.goToLevel4, player.goToLevel5, player.goToLevel6, player.goToLevel7, player.goToLevel8]
    assert player._lookTiles == []
    assert player._inventory == [0, 0, 0, 0, 0, 0, 0]
    assert player._lastReceivedMessage == ""
    assert player._direction == 0
    assert player._parsedMessage == ""

#Test if the player isn´t connected when sending None or a string that isn´t a ip address
def test_player_cant_connect():
    player = Player()
    aInfo = Config()
    aInfo._host = "localhost"
    aInfo._port = 4242
    aInfo._name = "test"
    assert player.connect(aInfo) == -1

#Test if the parser is correctly initialized
def test_parser_init():
    args = ["./zappy_ia", "-p", "4242", "-n", "Team1", "-h", "localhost"]
    info = parse(args)
    assert info._host == "localhost"
    assert info._port == "4242"
    assert info._name == "Team1"

#Test the setTeamName function
def test_player_setTeamName():
    player = Player()
    player.setTeamName("test")
    assert player._name == "test"
    player.setTeamName("test2")
    assert player._name == "test2"
    player.setTeamName("test3")
    assert player._name == "test3"
    player.setTeamName("")
    assert player._name == ""

#Test the parseInventory function
def test_player_parseInventory():
    player = Player()
    player.parseInventory("[food 0, linemate 1, deraumere 0, sibur 0, mendiane 0, phiras 0, thystame 0]\n")
    assert player._inventory == [0, 1, 0, 0, 0, 0, 0]
    player.parseInventory("[food 13, linemate 0, deraumere 0, sibur 5, mendiane 0, phiras 23472973, thystame 0]\n")
    assert player._inventory == [13, 0, 0, 5, 0, 23472973, 0]
    player.parseInventory("[food 0, linemate 0, deraumere 0, sibur 0, mendiane 0, phiras 0, thystame 0]\n")
    assert player._inventory == [0, 0, 0, 0, 0, 0, 0]
    player.parseInventory("[food 0, linemate 0, deraumere 977484, sibur 0, mendiane 87437675, phiras 0, thystame 4353450]\n")
    assert player._inventory == [0, 0, 977484, 0, 87437675, 0, 4353450]

#Test the crypt function
def test_player_crypt():
    player = Player()
    test : str = player.cryptMessage("test\n")
    assert test == 'yjxy\x0f'
    test : str = player.cryptMessage("test")
    assert test == 'yjxy'
    test : str = player.cryptMessage("test\n\n")
    assert test == 'yjxy\x0f\x0f'
    test : str = player.cryptMessage("JE SUIS UN TEST\n")
    assert test == 'OJ%XZNX%ZS%YJXY\x0f'

#Test the decrypt function
def test_player_decrypt():
    player = Player()
    test : str = player.decryptMessage('yjxy\x0f')
    assert test == "test"
    test : str = player.decryptMessage('yjxy')
    assert test == "tes"
    test : str = player.decryptMessage('yjxy\x0f\x0f')
    assert test == "test\n"
    test : str = player.decryptMessage('OJ%XZNX%ZS%YJXY\x0f')
    assert test == "JE SUIS UN TEST"
