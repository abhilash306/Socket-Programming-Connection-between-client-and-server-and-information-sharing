# SocketProgramming
Writing a client-server program using C, where clients (instructor/student of 
class) access the server (storing students’ marks in 5 subjects out of 100) for 
information about marks in examination. 

Client and Server 

Communication between two processes in which one process is client which 
connects to the other process is server for some information sharing. Once the 
connection is made than both sides can send and receive data and information. 
Connection between client and server is established using socket programming. 
All the data is stored on the server side which is made available to the client 
depending on request made. 

Functions used on client side to establish connection: 
1. socket(): creates a socket between client and server.
2. connect(): connects the client to the address of server. 
3. send(): used to sends the information from client side to server side.
4. recv(): used to receive information from server side to client side.

Functions used on server side to establish connection: 
1. socket(): creates socket between server and client. 
2. bind(): it assigns address to the socket. 
3. listen(): this function listen for connection before accepting it. 
4. accept(): this finally accepts the connection with the client. 
5. send(): used to sends the information from server side to client side.
6. recv(): used to receive information from client side to server side

Special header files used on server and client side: 
1 sys/types.h : contains the definition of data types used in system calls.
2 sys/socket.h : contains the definition of structure needed for socket.
3 netinet/in.h : contains constants and structures needed for internet domain 
address.

In this assignment, separate menu are created for instructor and students and those 
menu are displayed accordingly when a student or instructor login. The username 
and password are pre stored in a text file named user_pass.txt and students’ 
marks are stored in student_marks.csv. 
