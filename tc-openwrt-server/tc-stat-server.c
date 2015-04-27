/* A server for transmitting output of tc command to client */
#include<stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

// All communication happens on this port
const char *SERVER_PORT_NO = "9000";

int command_output(char* cmd,char *result) {
  //returns the command output from terminal in string format
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return -1;
    char buffer[128];
    while(!feof(pipe)) {
    	if(fgets(buffer, 128, pipe) != NULL)
    		strcat(result , buffer);
    }
    pclose(pipe);
    return 1;
}
int main(int argc, char *argv[])
{


  int status;// For Error Checking
  struct addrinfo host_info;// Filled by getaddrinfo()
  struct addrinfo *host_info_list;
  memset(&host_info, 0, sizeof host_info); // getaddrinfo() expects all zeros
  //cout<<"Initialization Done"<<endl;
  host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
  host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP.
  host_info.ai_flags = AI_PASSIVE;     // IP Wildcard
  status = getaddrinfo(NULL,SERVER_PORT_NO, &host_info, &host_info_list);
  //if (status != 0)  //cout << "getaddrinfo error" << gai_strerror(status) ;

  //cout << "Creating a socket..."  << std::endl;
  int socketfd ; // The socket descripter
  socketfd = socket(host_info_list->ai_family, host_info_list->ai_socktype,
                        host_info_list->ai_protocol);
  //if (socketfd == -1)  std:://cout << "socket error " ;

  //cout << "Binding a socket..."  << std::endl;
  int yes = 1;
  status = setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
  status = bind(socketfd, host_info_list->ai_addr, host_info_list->ai_addrlen);
  if (status == -1)  printf("bind error\n");

  printf("Listen()ing for connections...\n");
  status =  listen(socketfd, 5);
  if (status == -1)  printf("Listen error\n");

  int new_fd; // The socket descripter for client
  struct sockaddr_storage their_addr;
  socklen_t addr_size = sizeof(their_addr);
  new_fd = accept(socketfd, (struct sockaddr *)&their_addr, &addr_size);
  printf("Accepted Connection...\n");

  printf("send()ing back a message...\n");
  char msg[1000] = "";// = "The Messave from tc server.";
  command_output("ls",msg);

  int len;
  ssize_t bytes_sent;
  len = strlen(msg);
  bytes_sent = send(new_fd, msg, len, 0);

  //cout << "Stopping server..." << std::endl;
  freeaddrinfo(host_info_list);
  //close(new_fd);
  //close(socketfd);
  return 0;
}
