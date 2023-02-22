#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_CLIENTS 10
#define MAXDATASIZE 1024

int main(int argc, char **argv)
{
    if(argc > 1){
        //Definición de Variables
        int fd, fd2, client_lenght, port;
        port = atoi(argv[1]);
        //Estructuras de información
        struct sockaddr_in server; //Guardar información del servidor
        struct sockaddr_in client; //Guardar información del cliente
        pthread_t thread;//Para crear el hilo
        //Configuración del server
        server.sin_family= AF_INET; //TCP/IP
        server.sin_port= htons(port); //Puerto
        server.sin_addr.s_addr= INADDR_ANY; //Cualquier cliente se puede conectar
        char enviar[1024];//Para enviar mensaje
        bzero(&(server.sin_zero),8); //Rellenar con 0's
        //Se define el socket
        if(( fd=socket(AF_INET,SOCK_STREAM,0) ) <0){
            perror("Error de apertura de Socket\n");
            exit(-1);
        }
        //Se avisa al sistema de la creación del Socket
        if(bind(fd,(struct sockaddr*)&server, sizeof(struct sockaddr))==-1) {
            perror("Error en bind()\n");
            exit(-1);
        }
        //Establecer el Socket en modo escucha
        if(listen(fd, MAX_CLIENTS) == -1){
            perror("Error en listen()\n");
            exit(-1);
        }
        //Aceptación de conexiones
        while(1){
            client_lenght = sizeof(struct sockaddr_in);
            //Llamada a accept()
            if ((fd2 = accept(fd,(struct sockaddr *)&client, &client_lenght))==-1){
                perror("Error en accept()\n");
                exit(-1);
            }
            //Llamada al thread
            if (pthread_create(&thread, NULL, handle_client, (void*)&fd2) != 0) {
                perror("Error en la creacion de Thread");
                continue;
            }   
        }
        close(fd);
    }else{
        printf("NO se ingreso el puerto por PARAMETRO\n");
    }
    return 0;  
}
//Función para la comunicación con pthreads
void *handle_client(void *arg) {
    int fd2 = (int)arg;
    char BUFFER[MAXDATASIZE] = {0};
    int msg_read;

    // Receive message from client
    msg_read = read(fd2, BUFFER, 1024);
    printf("Mensaje del Cliente: %s\n", BUFFER);

    // Send response to client
    char *message = "Hello from server";
    send(fd2, message, strlen(message), 0);

    //Termino de la conversacion
    if(strcmp(BUFFER,"salir")==0){
        break;
    }
    // Close client socket and exit thread
    close(fd2);//Se cierra fd2
    pthread_exit(NULL);
}

