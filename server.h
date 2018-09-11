#ifndef SERVER_H
#define SERVER_H
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>
#include <fstream>
using namespace std;
typedef unsigned long long ul;
class Server
{
private:
    static const int SIZE = 1024; // размер буфера
    static const int WHENCE = 1024; // шаг чтения
    char Buffer[SIZE]; // создаем буфер
    int portI; //= atoi(portS); // преобразование строки в int
    char* nameS; // строка из main с именем файла для сохранения
    ul i = 0; // итератор байт
    ul waitSizeFile = 0; // ожидаемый размер файла
    ul fileSize = 0; // реальный размер файла
    long long recvSize = 0; // размер вычитаннх байт
    int MasterSocket = 0; // серверный сокет
    struct sockaddr_in SockAddr; // структура для задания пары IP port
    int ClientSocket = 0; // клиентский сокет
public:
    Server(char* portS, char* nameS); // конструктор, собирает порт и имя файла для сохранения//
    void ShowPortName();
    void StartServer(); // запуск сервера, открытие сокета, клиента тоже//
    ul ReadFileSize(); // получаем размер файла от клиента, возвращает waitSizeFile
    void InfoForHuman(int time); // вывод инфрмации для чтения размера файла хуманом
    ul SaveFile(); // запись файла на диск, возвращает i(количество записанных байт)
    void StopServer(); // остановка сервера, закрытие сокета сервера и клиента
    void ShowWriteBytes(); // показывает количество записанных байт
};
#endif // SERVER_H
