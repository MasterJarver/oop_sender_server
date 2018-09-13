#include <fstream>
#include <string>
typedef long long ul;
using namespace std;
ul GetFileSize(string filename)
{
    ifstream is(filename.c_str(), ifstream::binary); // открываем файл на чтение
    is.seekg (0, is.end); // размещаем указатель в конец
    const ul size = (ul)is.tellg(); // узнаем размер файла
    is.close(); // закрываем файл на чтение
    return size; // возврааем размер
}
