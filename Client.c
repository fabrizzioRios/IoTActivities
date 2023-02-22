#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <netdb.h>//Necesario para hostent
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    if(argc > 2){
        //Definición de Valores
        char *ip;
        int fd, numbytes, port;
        char BUFFER[1024] = {0};
        char *message = "Hello from Client";
        int msg_read;

        port=atoi(argv[2]);
        ip=argv[1];

        struct hostent *he; //Recibe información sobre el nodo remoto
        struct sockaddr_in server; //Informa sobre la dirección del servidor

        if((he=gethostbyname(ip))==NULL){
            //llamada a gethostbyname()
            printf("gethostbyname() error\n");
            exit(-1);           
        }
        //Definición de Socket
        if((fd=socket(AF_INET,SOCK_STREAM,0))==-1){
            //llamada a socket()
            printf("socket() error\n");
            exit(-1);
        }
        //Datos del Servidor
        server.sin_family = AF_INET;
        server.sin_port = htons(port);
        server.sin_addr = *((struct in_addr *)he->h_addr);//Se pasa la información de *he a h_addr
        bzero(&(server.sin_zero),8);
        //Conexión al Servidor
        if(connect(fd,(struct sockaddr *)&server,sizeof(struct sockaddr))==-1){
            printf("connect() error\n");
            exit(-1);
        }
        if((numbytes=recv(fd,BUFFER,100,0))==-1){
            //llamada a recv()
            printf("Error en recv()\n");  
            exit(-1);
        }
        BUFFER[numbytes]='\0';
        //printf("Mensaje del Servidor: % s\n");//Mensaje de Bienvenida del Servidor
        while(1){
            //El servidor espera el primer mensaje
            send(fd,message,strlen(message),0);

            //El cliente recibe el mensaje del servidor
            msg_read = read(fd,BUFFER,1024,0);
            printf("Mensaje del Servidor: %s\n", BUFFER);
            
            //imprime respuesta del servidor
            printf("Servidor: %s\n",BUFFER);
            
            }
        close(fd);
    }
    else{
        printf("No se ingreso la IP, ni el puerto por parametro\n");
    }
    return 0;
}
