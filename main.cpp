#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>
#include <fstream>
#include "getfilesize.h"
#include <server.h>
typedef unsigned long long ul;
using namespace std;
int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        cout << "Invalid arguments, need 2" << endl;
        return 1;
    }
    Server server(argv[1], argv[2]);
    server.ShowPortName();
    server.StartServer();
    server.ReadFileSize();
    server.InfoForHuman(3);
    server.SaveFile();
    server.StopServer();
    server.ShowWriteBytes();
    return 0;
}
