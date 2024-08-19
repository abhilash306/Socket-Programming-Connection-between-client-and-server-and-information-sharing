#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[0])
{
	char u[40], p[10];
	char c[40];
	float avgp, avgc, avgm, avge, avgcs;
	avgp = 0;
	avgc = 0;
	avge = 0;
	avgm = 0;
	avgcs = 0;

	int buf0[20], buf1[20], buf2[20], buf3[20], buf4[20], buf5[20];

	int w = 0;
	int w1 = 0;
	int j = 0;
	int option, x;
	int arr1[5];
	int sock = 0, valread, client_fd, valread1;
	struct sockaddr_in serv_addr;
	char *user = "client connected";
	char buffer[1024] = {0};
	char buffer1[1024] = {0};
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	int PORT = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}
	// connecting with server
	if ((client_fd = connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0))
	{
		printf("\nConnection Failed \n");
		return -1;
	}
	send(sock, user, strlen(user), 0);
	valread = read(sock, buffer, 1024);
	printf("%s\n", buffer);
	scanf("%s", u);
	printf("\n");
	send(sock, u, strlen(u), 0);
	strcat(u, " ");
	valread1 = read(sock, buffer1, 1024);
	printf("%s\n", buffer1);
	scanf("%s", p);
	printf("\n");
	send(sock, p, strlen(p), 0);
	strcat(u, p);
	recv(sock, &x, 4, 0);
	bzero(buffer1, 1024);
	valread1 = read(sock, buffer1, 1024);
	printf("%s\n", buffer1);
	printf("\n\n");

	if (x == 0)                      // for wrong username or password
	{
		printf("you have entered wrong data\n");
		exit(1);
	}

	if (strstr(u, "Instructor 0001") != NULL)                           // options dispalyed for user logged in as instructor
	{
		printf("select any one of  the options given below:\n\n1:marks of all students\n2:Class Average \n3:Number of Student Failed\n4:Best performing students\n5:Worst performing students\n");
		scanf("%d", &option);
		send(sock, &option, 4, 0);
		if (option == 1)
		{
			while (w < 20)
			{
				valread1 = read(sock, &buf0[w], 4);
				valread1 = read(sock, &buf1[w], 4);
				valread1 = read(sock, &buf2[w], 4);
				valread1 = read(sock, &buf3[w], 4);
				valread1 = read(sock, &buf4[w], 4);
				valread1 = read(sock, &buf5[w], 4);
				w++;
			}
			printf("Name			Physics			Chemistry	      Maths	             English		 Computer science     Aggregate percentage\n");
			while (w1 < 20)
			{
				j++;
				bzero(buffer, 1024);
				valread1 = read(sock, buffer, 1024);
				printf("%s			%d			%d			%d			%d			%d            %d\n", buffer, buf0[w1], buf1[w1], buf2[w1], buf3[w1], buf4[w1], buf5[w1]);
				// recv(sock, buff1[w2],sizeof(buff1[w2]),0);
				send(sock, &j, 4, 0);
				valread1 = read(sock, &w1, 4);
				// printf("%s\n",buff1[w2]);
				bzero(buffer, 1024);
			}
		}
		if (option == 2)
		{
			valread1 = read(sock, &avgp, 4);
			valread1 = read(sock, &avgc, 4);
			valread1 = read(sock, &avgm, 4);
			valread1 = read(sock, &avge, 4);
			valread1 = read(sock, &avgcs, 4);

			printf("Physics average = %f\n", avgp / 20);
			printf("chemistry average = %f\n", avgc / 20);
			printf("mathematics average = %f\n", avgm / 20);
			printf("English average = %f\n", avge / 20);
			printf("Computer  science average = %f\n", avgcs / 20);
			printf("overall average = %f\n", ((avgp + avgc + avgm + avge + avgcs) / 100));
		}
		if (option == 3)
		{
			int fail[5];
			valread1 = read(sock, &fail[0], 4);
			valread1 = read(sock, &fail[1], 4);
			valread1 = read(sock, &fail[2], 4);
			valread1 = read(sock, &fail[3], 4);
			valread1 = read(sock, &fail[4], 4);
			printf("No. of students failed in physics : %d\n", fail[0]);
			printf("No. of students failed in chemistry : %d\n", fail[1]);
			printf("No. of students failed in maths : %d\n", fail[2]);
			printf("No. of students failed in english : %d\n", fail[3]);
			printf("No. of students failed in computer science : %d\n", fail[4]);
		}
		bzero(buffer1, 1024);
		bzero(buffer, 1024);

		if (option == 4)
		{
			float top;

			valread1 = read(sock, &top, 4);
			valread1 = read(sock, buffer, 1024);

			printf("best performing student is %s  and his total marks is %f\n", buffer, top);
		}
		if (option == 5)
		{
			float worst;
			valread1 = read(sock, &worst, 4);
			valread1 = read(sock, buffer1, 1024);

			printf("worst performing student is %s  and his total marks is %f\n", buffer1, worst);
		}

		if (option > 5 || option < 1)
		{
			printf("Wrong choice\n");
		}
	}
	else                                              // options displayed if user logged in as student
	{
		printf("select any one of  the options given below:\n\n1:Your Marks\n2:Your Aggregate\n3:Your Maximum scoring subject\n4:Your Minimum scoring subject\n");
		scanf("%d", &option);
		send(sock, &option, 4, 0);
		if (option == 1)
		{
			valread1 = read(sock, &arr1[0], 4);
			valread1 = read(sock, &arr1[1], 4);
			valread1 = read(sock, &arr1[2], 4);
			valread1 = read(sock, &arr1[3], 4);
			valread1 = read(sock, &arr1[4], 4);
			printf("Physics = %d    Chemistry = %d     Mathematics = %d     English = %d     Computer Science = %d\n", arr1[0], arr1[1], arr1[2], arr1[3], arr1[4]);
		}
		if (option == 2)
		{
			float avg;
			valread1 = read(sock, &avg, 4);
			printf("Your aggregate percentage is %f\n", avg);
		}
		if (option == 3)
		{
			int top;
			bzero(buffer, 1024);
			valread1 = read(sock, &top, 4);
			valread1 = read(sock, buffer, 1024);
			printf("best perfoming subject is %s  and subject marks is %d\n", buffer, top);
		}
		if (option == 4)
		{
			int worst;
			valread1 = read(sock, &worst, 4);
			bzero(buffer1, 1024);
			valread1 = read(sock, buffer1, 1024);

			printf("worst perfoming subject is %s  and subject marks is %d\n", buffer1, worst);
		}
		if (option > 4 || option < 1)
		{
			printf("Wrong choice\n");
		}
	}

	// closing the connected socket
	close(client_fd);
	return 0;
}
