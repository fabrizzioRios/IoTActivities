// Client side C/C++ program to demonstrate Socket programming
#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
//#include "com.h"
#include "mqtt_frames.h"

#define PORT 1883
pthread_mutex_t socketMutex = PTHREAD_MUTEX_INITIALIZER;
sPingReq sRequest;

void timer_handler(int signum){

	static int count = 0;
	printf("timer expired %d times\n", ++count);
}

void *timer_thread(void *arg)
{
    struct sigaction sa;
    struct itimerval timer;

    /* Install timer_handler as the signal handler for SIGVTALRM. */
    memset (&sa, 0, sizeof (sa));
    sa.sa_handler = &timer_handler;
    sigaction (SIGVTALRM, &sa, NULL);

    /* Configure the timer to expire after 250 msec... */
    timer.it_value.tv_sec = 40;
    timer.it_value.tv_usec = 0;

    /* ... and every 250 msec after that. */
    timer.it_interval.tv_sec = 40;
    timer.it_interval.tv_usec = 0;
    

    /* Start a virtual timer. It counts down whenever this process is
    executing. */
    setitimer (ITIMER_VIRTUAL, &timer, NULL);

    /* Do busy work. */
    //while (1)
    //{
    	printf("\n");
    	sRequest = vfnCreateREQUEST();
    	printf("\n");
	printf("This is the FrameType 0x%x \r\n", sRequest.bFrameType);
      	printf("This is the Topic 0x%d \r\n", sRequest.bMsgLength);
      	printf("\n");
    //}

    return NULL;
}


int main(int argc, char const *argv[]) {
  int sock = 0;
  int res;
  
  struct sockaddr_in serv_addr;
  
  // char *hello = "Hello from client";
  // char buffer[1024] = {0};
  
  ssize_t iWriteRc = 0;
  uint8_t *bpInstruction = (uint8_t *)malloc(10);
  sConnect sReturn;
  sConnACK sAcknowledge;
  sPublish sPublish;
  sSubscribe sSubscribe;

  printf("argv[] %s , sizeof %ld \r\n", argv[1], strlen(argv[1]));
  
  pthread_t tid;
  
  
  printf("\n");
  sReturn = vfnCreateFrame(argv[1], sizeof(argv[1]));
  printf("This is the sFrameType 0x%x \r\n", sReturn.bFrameType);
  printf("This is the wMsgLen 0x%x \r\n", sReturn.wMsgLen);
  printf("This is the wProtlNameLen 0x%x \r\n", sReturn.wProtlNameLen);
  printf("This is the sProtName %s \r\n", sReturn.sProtName);
  printf("This is the bVersion 0x%x \r\n", sReturn.bVersion);
  printf("This is the bConnectFlags 0x%x \r\n", sReturn.bConnectFlags);
  printf("This is the bKeepAlive 0x%x \r\n", sReturn.bKeepAlive);
  printf("This is the wClientIdLen 0x%x \r\n", sReturn.wClientIdLen);
  printf("This is the sClientID %s \r\n", sReturn.sClientID);
  printf("\n");

  printf("\n");
  sAcknowledge = vfnCreateCONNACK();
  printf("This is the sFrameType 0x%x \r\n", sAcknowledge.bFrameType);
  printf("This is the wMsgLen 0x%x \r\n", sAcknowledge.bMsgLength);
  printf("This is the wProtlNameLen 0x%x \r\n", sAcknowledge.bReturnCode);
  printf("\n");
  
  pthread_create(&tid, NULL, timer_thread, NULL);
  pthread_join(tid, NULL);
  
// Creación de Menu
  printf("\n");
  printf("Que accion te gustaria hacer?\n\n");
  printf("Publicar - 1\nSuscribirse - 2\n");
  printf("Opción: ");
  // Fin menú
  scanf("%i", &res); // Toma de respuesta por parte del cliente
  // Validación de respuesta
    if (res == 1) {
      printf("\n");
      sPublish =
          vfnCreatePUBLISH((char *)&sPublish.sTopic, (char *)sPublish.sMessage);
      printf("This is the FrameType 0x%x \r\n", sPublish.bFrameType);
      printf("This is the Topic 0x%s \r\n", sPublish.sTopic);
      printf("This is the Message 0x%s \r\n", sPublish.sMessage);
      printf("This is the Topic Lenght %d \r\n", sPublish.wTopicLength);
      printf("This is the Message Lenght 0x%x \r\n", sPublish.wMessageLength);
      printf("This is the Remaining Length 0x%x \r\n",sPublish.bRemainingLength);
      printf("\n");

    } else if (res == 2) {

      printf("\n");
      sSubscribe = vfnCreateSUBSCRIBE();
      printf("This is the Frame Type 0x%x \r\n", sSubscribe.bFrameType);
      printf("This is the Remaining Length 0x%x \r\n",
             sSubscribe.bRemainingLength);
      printf("This is the Packet Identifier 0x%x \r\n",
             sSubscribe.wPacketIdentifier);
      printf("This is the Topic Name Length %d \r\n",
             sSubscribe.wTopicNameLength);
      printf("This is the Topic 0x%s \r\n", sSubscribe.sTopic);
      printf("This is the QOS 0x%x \r\n", sSubscribe.bRequestedQOS);
      printf("\n");
    }
    // Término de Validación
  /*int socket(int domain, int type, int protocol);
      AF_INET	= IPv4 Internet protocols
      SOCK_STREAM = Provides sequenced, reliable,
                              two-way, connection-based byte streams.
                              An out-of-band data transmission mechanism may be
     supported. Protocol specifies a particular protocol to be used with the
     socket. Normally only a single protocol exists to support a particular
      socket type within a given protocol family,
      in which case protocol can be specified as 0.
      */
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("error \n");
    return -1;
  }

  // struct sockaddr_in
  //{
  //	sa_family_t    sin_family; /* address family: AF_INET */
  //	in_port_t      sin_port;   /* port in network byte order */
  //	struct in_addr sin_addr;   /* internet address */
  // };
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);
  serv_addr.sin_addr.s_addr = inet_addr("10.0.2.15");

  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    printf("\n Connection Failed \n");
    return -1;
  }
  // sFrameConnect.bFrameType = 0x10;
  // sFrameConnect.wMsgLen = wNum;
  // sFrameConnect.wProtlNameLen = 0x0004;
  // sFrameConnect.sProtName = 'MATT';
  // sFrameConnect.bVersion = 0x04;
  // sFrameConnect.bConnectFlags = 0x02;
  // sFrameConnect.bKeepAlive = 0x000A;
  // sFrameConnect.wClientIdLen = 0x0005;
  // sFrameConnectsClientID = 'Mario';

  iWriteRc = send(sock, (char *)&sReturn, strlen((char *)&sReturn), 0);
  if (iWriteRc <= 0) {
    printf("\n Send Fallido \n");
    return -1;
  }
  printf("Hello from Client \n");

  while (1) {
    fgets((char *)bpInstruction, 10, stdin);
    pthread_mutex_lock(&socketMutex);
    iWriteRc = send(sock, bpInstruction, strlen((char *)bpInstruction), 0);
    if (iWriteRc <= 0) {
      printf("Shuting down the socket: %ld\n", iWriteRc);
    }
    sRequest = vfnCreateREQUEST(); // Creación del Request

    pthread_mutex_unlock(&socketMutex);
    sleep(1);
  }
  return 0;
}



