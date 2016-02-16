/* A server for transmitting output of tc command to client */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close

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
  printf("Initialization Done\n");
  host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
  host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP.
  host_info.ai_flags = AI_PASSIVE;     // IP Wildcard
  status = getaddrinfo(NULL,SERVER_PORT_NO, &host_info, &host_info_list);
  if (status != 0)  printf("getaddrinfo error\n");

  printf("Creating a socket...\n");
  int socketfd ; // The socket descripter
  socketfd = socket(host_info_list->ai_family, host_info_list->ai_socktype, host_info_list->ai_protocol);
  if (socketfd == -1)  printf("socket error\n") ;

  printf("Binding a socket...\n");
  int yes = 1;
  status = setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
  status = bind(socketfd, host_info_list->ai_addr, host_info_list->ai_addrlen);
  if (status == -1)  printf("bind error\n");

  while(1){
    printf("Listen()ing for connections...\n");
    status =  listen(socketfd, 5);
    if (status == -1)  printf("Listen error\n");

    int new_fd; // The socket descripter for client
    struct sockaddr_storage their_addr;
    socklen_t addr_size = sizeof(their_addr);
    new_fd = accept(socketfd, (struct sockaddr *)&their_addr, &addr_size);
    printf("Accepted Connection...\n");

    // Need to create a thrd or Forking a child process to communicate


    printf("send()ing back a message...\n");
    char msg[1000] = "";// = "The Messave from tc server.";
    char msg2[1000] = "";// = "The Messave from tc server.";
    command_output("tc -s class show dev wlan0|grep -w 'Sent'",msg);
    command_output("iptables -t mangle -nvx -L | grep 'set 0x3'",msg2);

    int len1,len2;
    ssize_t bytes_sent;
    strcat(msg,msg2);
    len1 = strlen(msg);
    bytes_sent = send(new_fd, msg, len1, 0);
    //sleep(10);

    // Need to send a termination message
   close(new_fd);
  }
  //cout << "Stopping server..." << std::endl;
  freeaddrinfo(host_info_list);
  //close(new_fd);
  return 0;
}
