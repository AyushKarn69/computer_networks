import socket

HOST = "0.0.0.0"  # all networks for listning
PORT = 65432      # unprivileged port for server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    print(f"Server started. Waiting for connection on port {PORT}...")
    
    conn, addr = s.accept()
    with conn:
        print(f"Connected by {addr}")
        
        while True:
            # Receive message from client
            data = conn.recv(1024).decode()
            if not data:
                print("Client disconnected.")
                break
            
            print(f"Client: {data}")

           

           
            msg = input("Server: ")
            conn.sendall(msg.encode())

            if msg.lower() == "quit":
                print("Server closing connection.")
                break
