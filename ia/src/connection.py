import socket


class Connection:
    def __init__(self, host, port):
        self.socket = None
        self.host = host
        self.port = port

    def connect(self):
        print("Connecting to {} on port {}".format(self.host, self.port))
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            self.socket.connect((self.host, self.port))
        except Exception as e:
            print("Error: {}".format(e))
            return -1
        return 0

    def disconnect(self):
        print("Disconnecting from {} on port {}".format(self.host, self.port))
        self.socket.close()
        self.socket = None

    def send(self, data):
        print("Sending data: {}".format(data))
        self.socket.send(data.encode())

    def receive(self):
        print("Receiving data")
        return self.socket.recv(2048).decode()
