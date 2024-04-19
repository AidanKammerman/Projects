# TCP-Based Chat Program

This project implements a TCP-based chat program consisting of a client and server component. The server facilitates communication between multiple clients by relaying messages between them.

## Overview

The chat program operates on a client-server architecture, allowing users to connect to a central server and exchange messages with other connected clients. The server is responsible for managing client connections and relaying messages between them.

## Components

### Client
- The client program allows users to connect to the chat server and exchange messages with other clients.
- Clients can send messages to the server, which are then broadcasted to all other connected clients.
- The client supports commands such as `/quit` to exit the chat session.

### Server
- The server program listens for incoming client connections and manages the communication between them.
- When a client sends a message to the server, the server broadcasts it to all other connected clients.
- The server maintains a list of active client connections and handles disconnections gracefully.

## Requirements

- Python 3.x
- argparse library (for command-line argument parsing)
- socket library (for network communication)

