import socket

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(("0.0.0.0", 8000))

send = b'alba'