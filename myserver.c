// Server side C/C++ program to demonstrate Socket
// programming
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
// structure to store student details
struct st
{
    char name[30];
    int s1;
    int s2;
    int s3;
    int s4;
    int s5;
    int a;
};

int main(int argc, char *argv[])
{
    FILE *fi;
    fi = fopen("student_marks.csv", "r"); // opening student_marks.csv file in reading mode
    char temp[512];
    int cline = 1;
    FILE *ptr;
    ptr = fopen("user_pass.txt", "r"); // opening user_pass.txt file in reading mode

    int g;
    int h;
    float per[20], per1[20];
    int arr[5];
    float avg;
    int min_indx1;
    int arr1[5];
    float temp_array;
    float avgp, avgc, avgm, avge, avgcs;
    int savg[5];
    char subj[5][20] = {"Physics", "Chemistry", "Mathematics", "English", "Computer Science"};

    int x = 0;
    char s[512];
    int line = 1;
    int l, q;
    int server_fd, new_socket, valread, valread1, valread2;
    int ret, pass;
    struct sockaddr_in address;
    int opt = 1;
    int j1 = 0;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char u[20] = {0};
    char p[20] = {0};
    char *user1 = "Enter Username";
    char *pass1 = "Enter Password";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // attaching socket to the port declared while executing myserver.c in the terminal
    int PORT = atoi(argv[1]);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // binding server with client
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 5) < 0) // listening from the client
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) // accepting connection request from client
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // reading username and password sent from client side
    valread = read(new_socket, buffer, 1024);
    printf("%s\n", buffer);
    send(new_socket, user1, strlen(user1), 0);
    valread1 = read(new_socket, u, 20);
    send(new_socket, pass1, strlen(pass1), 0);
    valread1 = read(new_socket, p, 20);
    strcat(u, " ");
    strcat(u, p);

    while (fgets(s, 512, ptr) != NULL) // authenticating username and password
    {
        if ((strstr(s, u)) != NULL)
        {
            x++;
            l = line;
        }

        line++;
    }

    if (x > 0)
    {
        send(new_socket, "login successful", strlen("login successful"), 0);
    }
    else
    {
        send(new_socket, &x, 4, 0);
        send(new_socket, "login failed", strlen("login failed"), 0);

        exit(1);
    }

    struct st std[20];

    char z[100];
    char *sp;
    int i = 0;
    while (fgets(z, 100, fi) != NULL) // storing data from student_marks.csv file into the structure name and subject wise
    {
        sp = strtok(z, ",");
        strcpy(std[i].name, sp);

        sp = strtok(NULL, ",");
        std[i].s1 = atoi(sp);

        sp = strtok(NULL, ",");
        std[i].s2 = atoi(sp);

        sp = strtok(NULL, ",");
        std[i].s3 = atoi(sp);

        sp = strtok(NULL, ",");
        std[i].s4 = atoi(sp);

        sp = strtok(NULL, ",");
        std[i].s5 = atoi(sp);
        i++;
    }

    // storing subject marks into an array for sorting purpose
    arr[0] = std[l - 1].s1;
    arr[1] = std[l - 1].s2;
    arr[2] = std[l - 1].s3;
    arr[3] = std[l - 1].s4;
    arr[4] = std[l - 1].s5;
    arr1[0] = std[l - 1].s1;
    arr1[1] = std[l - 1].s2;
    arr1[2] = std[l - 1].s3;
    arr1[3] = std[l - 1].s4;
    arr1[4] = std[l - 1].s5;

    for (int i1 = 0; i1 < 4; i1++) // sorting using selection sort algorithm
    {
        min_indx1 = i1;
        for (int j1 = i1 + 1; j1 < 5; j1++)
        {
            if (arr[j1] < arr[min_indx1])
            {
                min_indx1 = j1;
            }
        }
        if (min_indx1 != i1)
        {
            temp_array = arr[min_indx1];
            arr[min_indx1] = arr[i1];
            arr[i1] = temp_array;
        }
    }

    for (int j = 0; j < 20; j++) // adding marks of every studentand storing it into per[] array
    {
        per[j] = (std[j].s1 + std[j].s2 + std[j].s3 + std[j].s4 + std[j].s5);
        per1[j] = (std[j].s1 + std[j].s2 + std[j].s3 + std[j].s4 + std[j].s5);
    }

    int min_indx;
    for (int i1 = 0; i1 < 19; i1++) // sorting total marks of every student using selection sort algorithm
    {
        min_indx = i1;
        for (int j1 = i1 + 1; j1 < 20; j1++)
        {
            if (per[j1] < per[min_indx])
            {
                min_indx = j1;
            }
        }
        if (min_indx != i1)
        {
            temp_array = per[min_indx];
            per[min_indx] = per[i1];
            per[i1] = temp_array;
        }
    }

    for (int k = 0; k < 20; k++)
    {
        std[k].a = ((std[k].s1 + std[k].s2 + std[k].s3 + std[k].s4 + std[k].s5) / 5);
    }

    if (strstr(u, "Instructor 0001") != NULL) // checking if user is instructor or not
    {
        int q1;
        valread1 = read(new_socket, &q1, 4);
        int fail1 = 0;
        int fail2 = 0;
        int fail3 = 0;
        int fail4 = 0;
        int fail5 = 0;
        int j = 0;
        int i1 = 0;

        switch (q1) // if instructor is logged then he can performe desired action and all operation happens here in server side which is sent to client
        {
        case 1:
            while (j < 20)
            {
                send(new_socket, &std[j].s1, 4, 0);
                send(new_socket, &std[j].s2, 4, 0);
                send(new_socket, &std[j].s3, 4, 0);
                send(new_socket, &std[j].s4, 4, 0);
                send(new_socket, &std[j].s5, 4, 0);
                send(new_socket, &std[j].a, 4, 0);

                j++;
            }

            while (j1 < 20)
            {
                i1++;
                send(new_socket, std[j1].name, strlen(std[j1].name), 0);
                valread2 = read(new_socket, &j1, 4);
                send(new_socket, &i1, 4, 0);
            }
            break;

        case 2:

            avgp = 0;
            avgc = 0;
            avge = 0;
            avgm = 0;
            avgcs = 0;
            for (int j = 0; j < 20; j++)
            {
                avgp += std[j].s1;
                avgc += std[j].s2;
                avgm += std[j].s3;
                avge += std[j].s4;
                avgcs += std[j].s5;
            }
            send(new_socket, &avgp, 4, 0);
            send(new_socket, &avgc, 4, 0);
            send(new_socket, &avgm, 4, 0);
            send(new_socket, &avge, 4, 0);
            send(new_socket, &avgcs, 4, 0);
            break;

        case 3:
            for (int j = 0; j < 20; j++)
            {
                if (std[j].s1 < 33.33)
                    fail1++;

                if (std[j].s2 < 33.33)
                    fail2++;

                if (std[j].s3 < 33.33)
                    fail3++;

                if (std[j].s4 < 33.33)
                    fail4++;

                if (std[j].s5 < 33.33)
                    fail5++;
            }
            send(new_socket, &fail1, 4, 0);
            send(new_socket, &fail2, 4, 0);
            send(new_socket, &fail3, 4, 0);
            send(new_socket, &fail4, 4, 0);
            send(new_socket, &fail5, 4, 0);
            break;

        case 4:
            for (int i1 = 0; i1 < 20; i1++)
            {
                if (per1[i1] == per[19])
                {
                    send(new_socket, &per[19], 4, 0);
                    send(new_socket, std[i1].name, strlen(std[i1].name), 0);
                }
            }
            break;

        case 5:
            for (int i1 = 0; i1 < 20; i1++)
            {
                if (per1[i1] == per[0])
                {
                    send(new_socket, &per[0], 4, 0);
                    send(new_socket, std[i1].name, strlen(std[i1].name), 0);
                }
            }
            break;

        default:
            exit(1);
            break;
        }
    }

    else // if student is logged then he can perform action as he desired and all operation happens here in server side which is sent to client
    {

        int q1;
        valread1 = read(new_socket, &q1, 4);

        switch (q1)
        {
        case 1:
            send(new_socket, &arr1[0], 4, 0);
            send(new_socket, &arr1[1], 4, 0);
            send(new_socket, &arr1[2], 4, 0);
            send(new_socket, &arr1[3], 4, 0);
            send(new_socket, &arr1[4], 4, 0);
            break;

        case 2:
            avg = (std[l - 1].s1 + std[l - 1].s2 + std[l - 1].s3 + std[l - 1].s4 + std[l - 1].s5) / 5;
            send(new_socket, &avg, 4, 0);
            break;

        case 3:
            for (int i1 = 0; i1 < 5; i1++)
            {
                if (arr1[i1] == arr[4])
                    g = i1;
            }
            send(new_socket, &arr[4], 4, 0);
            send(new_socket, subj[g], strlen(subj[g]), 0);
            break;

        case 4:
            for (int i1 = 0; i1 < 5; i1++)
            {
                if (arr1[i1] == arr[0])
                    h = i1;
            }
            send(new_socket, &arr[0], 4, 0);
            send(new_socket, subj[h], strlen(subj[h]), 0);
            break;

        default:
            exit(1);
            break;
        }
    }
    fclose(ptr); // closing student_mark file
    fclose(fi);  // closing user_id file

    // closing the connected socket
    close(new_socket);
    // closing the listening socket
    shutdown(server_fd, SHUT_RDWR);
    return 0;
}
