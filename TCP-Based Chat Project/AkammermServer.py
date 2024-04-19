import socket
import argparse
import threading

def handle_client(client_sock, client_addr, clients):
    try:
        while True:
            message = client_sock.recv(1024).decode()
            if not message:
                break
            
            for c_sock, c_addr in clients:
                if c_sock != client_sock:
                    c_sock.sendall(f"{client_addr}: {message}".encode())
    except ConnectionResetError:
        print(f"Connection to {client_addr} closed unexpectedly.")
    finally:
        clients.remove((client_sock, client_addr))
        client_sock.close()

def main():
    parser = argparse.ArgumentParser(description="Server program for TCP-based chat")
    parser.add_argument("--port", help="Port number for server to listen on", type=int, required=True)
    args = parser.parse_args()

    server_port = args.port

    server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    server_sock.bind(('0.0.0.0', server_port))
    server_sock.listen(5)
    print(f"Server listening on 0.0.0.0:{server_port}")

    clients = []

    try:
        while True:
            client_sock, client_addr = server_sock.accept()
            print(f"Connection from {client_addr} established.")

            clients.append((client_sock, client_addr))

            client_thread = threading.Thread(target=handle_client, args=(client_sock, client_addr, clients))
            client_thread.start()
    except KeyboardInterrupt:
        print("Keyboard interrupt detected. Exiting...")
    finally:
        for client_sock, _ in clients:
            client_sock.close()
        
        server_sock.close()

if __name__ == "__main__":
    main()
