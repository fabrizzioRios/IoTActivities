
import socket

def main():

    HOST = "127.0.0.1"
    PORT = 1111

    client_socket = socket.socket()
    client_socket.connect((HOST, PORT))

    message = input("Client:")

    while message.lower().strip() != 'bye':
        client_socket.send(message.encode())
        data = client_socket.recv(1024).decode()

        print('Server: ' + data)

        message = input("Client")

    client_socket.close()


if __name__ == "__main__":
    main()
