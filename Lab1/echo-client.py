import socket

HOST = "192.168.0.128"  # Server's IP address 
PORT = 65432             # Server's listening port 

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    print("Connected to the server. Type 'quit' to exit.")

    while True:
        
        message = input("You: ")

       
        s.sendall(message.encode('utf-8'))

        
        if message.lower() == 'quit':
            print("Closing connection...")
            break

        
        data = s.recv(1024)
        if not data:
            print("Server closed the connection.")
            break

        print(f"Server: {data.decode('utf-8')}")
