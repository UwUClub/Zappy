from connection import Connection


class Player:
    def __init__(self):
        self.socket = None

    def connect(self, info):
        self.socket = Connection(info["host"], int(info["port"]))
        return self.socket.connect()

    def send(self, data):
        self.socket.send(data)

    def receive(self):
        return self.socket.receive()

