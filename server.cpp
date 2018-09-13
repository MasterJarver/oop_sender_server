#include "server.h"
typedef long long ul;
Server::Server(char* portS, char* nameS) // конструктор
{
    this->portI = atoi(portS); // преобразование строки в int
    this->nameS = nameS; // запись в поле имя
}
void Server::ShowPortName()
{
    cout << portI << endl;
    cout << nameS << endl;
}
void Server::StartServer() // запуск сервера, открытие серверного сокета и клиентского сокета
{
    MasterSocket = socket(AF_INET, 	SOCK_STREAM, IPPROTO_TCP); // Декларируем серверный сокет
    SockAddr.sin_family = AF_INET; // используем IPv4
    SockAddr.sin_port = htons(portI); // приводим portI к сетевому порядку байт
    SockAddr.sin_addr.s_addr = htonl(INADDR_ANY); // открываем сокет на все ip адреса
    bind(MasterSocket, (struct sockaddr*)(&SockAddr), sizeof(SockAddr));//биндим сокет(привязка сокета к порту)
    listen(MasterSocket, SOMAXCONN); // открываем приём, создаем очередь SOMAXCONN
    cout << "point to wait client!!!" << endl;
    ClientSocket = accept(MasterSocket, 0, 0); // создаем клиентский сокет
    cout << "accept client socket" << endl;
}
ul Server::ReadFileSize()
{
    cout << "begin read file" << endl;
    while(recvSize == 0) // пока есть инфа для чтения
    {
        recvSize = (ul)recv(ClientSocket, &waitSizeFile, 4, MSG_NOSIGNAL); // читаем в переменную из сокета
        //cout << "RecvSize: " << recvSize << endl;
        cout << "wait_size_file: " << waitSizeFile << endl;
        if(waitSizeFile <= 0)
        {
            //cout << "Error" << endl;
            break;
        }
    }
    return waitSizeFile; // возвращаем размер файла в байтах
}
void Server::InfoForHuman(int time) // вывод инфрмации для чтения размера файла хуманом
{
    cout << "wait size file in bytes: " << waitSizeFile << endl;
    sleep(time); // время для чтения
}
ul Server::SaveFile() // запись файла на диск, возвращает i(количество записанных байт)
{
    if(waitSizeFile <= 0)
    {
        //cout << "Error Wait Size" << endl;
        return -1;
    }
    ofstream of(nameS, ofstream::binary); // открыли файл на дозапись в бинарном режиме
    while(i != waitSizeFile) // пока i не равно ожидаемому размеру
    {
        recvSize = (ul)recv(ClientSocket, Buffer, WHENCE, MSG_NOSIGNAL); // читаем в буфер из сокета
        //cout << "RecvSize: " << recvSize << endl;
        if(recvSize != 0 || recvSize != -1) // если есть инфа для чтения
        {
            of.seekp(i, of.beg); // смещение указателя на i элементов от начала
            of.write(Buffer, recvSize); // пишем из буфера RecvSize байт
            i += recvSize;
            cout << "accept bytes: " << i << endl;
        }
    }
    of.close(); // закрываем файл на запись
    return i;
}
void Server::StopServer() // остановка сервера, закрытие сокета сервера и клиента
{
    shutdown(ClientSocket, SHUT_RDWR); // разрываем соединение клиентского сокета
    close(ClientSocket); // закрываем дескриптор клиентского сокета
    shutdown(MasterSocket, SHUT_RDWR); // закрываем соединение
    close(MasterSocket); // закрываем дескриптор
}
void Server::ShowWriteBytes()
{
    cout << "final bytes: " << i << endl;
    cout << "end program." << endl;
}
