# IoTActivities

In this repository is stored the code of the server and the client coded in python. We used the socket library. This library is already in the python packages and it only needs to ve imported in the python codes.
We used the host ***127.0.0.1*** and the port ***1111*** to make the connection between the server and the client. With a message function called send, we asked for an input and then we send the message, the message is received in the client and then a response is writed. 
The response is sended and then evaluated, if the message is bye, the cicle is broken and the script is finished, other way, the exchange of messages keep going until a the messagge received is bye.

## How to run our script

Before we run, we nee to make a directory, then clone the repository and execute both scripts. 

**Install github**

    *sudo apt-get install git-all*

**Make the directory**

    mkdir [NewDirectory]

**Enter the directory** 

    cd [NewDirectory]

**Clone the repository to the directory**

    git clone https://github.com/fabrizzioRios/IoTActivities.git

**Execute both scripts**

    python3 cliente.py
    python3 main.py
