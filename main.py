#! /usr/bin/python
import socket


def main():
    HOST = "127.0.0.1"
    PORT = 1111

    server_socket = socket.socket()
    server_socket.bind((HOST, PORT))

    server_socket.listen(2)
    conn, address = server_socket.accept()
    print("Connection from: " + str(address))
    while True:
        data = conn.recv(1024).decode()
        if not data:
            break
        print("Client: " + str(data))
        data = input('Server:')
        conn.send(data.encode())

    conn.close()


if __name__ == "__main__":
    main()
