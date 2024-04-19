import socket
import argparse
import threading

def receive_messages(sock):
    try:
        while True:
            message = sock.recv(1024).decode()
            if not message:
                break
            print(message)
    except ConnectionResetError:
        print("Connection to server closed unexpectedly.")
    finally:
        sock.close()

def main():
    parser = argparse.ArgumentParser(description="Client program for TCP-based chat")
    parser.add_argument("--id", help="Client ID", required=True)
    parser.add_argument("--port", help="Port number for client to listen on", type=int, required=True)
    parser.add_argument("--server", help="Server IP address and port number", required=True)
    args = parser.parse_args()

    client_id = args.id
    client_port = args.port
    server_ip, server_port = args.server.split(':')

    client_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
        client_sock.connect((server_ip, int(server_port)))
        print(f"Connected to server at {server_ip}:{server_port}")

        recv_thread = threading.Thread(target=receive_messages, args=(client_sock,))
        recv_thread.start()

        while True:
            message = input()

            client_sock.sendall(message.encode())

            if message == '/quit':
                break
    except KeyboardInterrupt:
        print("Keyboard interrupt detected. Exiting...")
    finally:
        client_sock.close()

if __name__ == "__main__":
    main()
