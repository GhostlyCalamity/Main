#include <stdio.h>   /* Стандартные объявления ввода/вывода */
#include <string.h>  /* Объявления строковых функций */
#include <unistd.h>  /* Объявления стандартных функций UNIX */
#include <fcntl.h>   /* Объявления управления файлами */
#include <errno.h>   /* Объявления кодов ошибок */
#include <termios.h> /* Объявления управления POSIX-терминалом */
#include <fstream>   /* Объявление функции записи*/
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctime>
 using namespace std;
 
int fd; /* Файловый дескриптор для порта */
char buf[10]={0};/*размер зависит от размера строки принимаемых данных*/ 
int iIn;
FILE* f;

int open_port(void);
int main(void) { 
  
  port_set:
    fd = open("/dev/ttyACM6", O_RDWR | O_NOCTTY | O_NDELAY); /*'open_port()' - Открывает последовательный порт */
      if (fd == -1)
        {
          /*  * Возвращает файловый дескриптор при успехе или -1 при ошибке. */
           printf("error port\n");
           perror("open_port: Unable to open /dev/ttyUSBn - ");
        }
     else
        {
         struct termios options; /*структура для установки порта*/
         tcgetattr(fd, &options); /*читает пораметры порта*/
        
      	 cfsetispeed(&options, B9600);/*установка скорости порта*/
         cfsetospeed(&options, B9600); /*установка скорости порта*/
         
         options.c_cflag &= ~PARENB; /*выкл проверка четности*/
         options.c_cflag &= ~CSTOPB; /*выкл 2-х стобит, вкл 1 стопбит*/
         options.c_cflag &= ~CSIZE; /*выкл битовой маски*/
         options.c_cflag |= CS8; /*вкл 8бит*/
         tcsetattr(fd, TCSANOW, &options); /*сохронения параметров порта*/
        
        }
 
 read_port:
 
 	iIn=read(fd,buf,10); /*чтения приходящих данных из порта*/

	f = fopen("/home/serg/port.txt", "at"); // окрываем файл для записи
 	fprintf (f, "%s", buf);
	//usleep(10000);
	cout<<buf;
	fclose(f); 

goto read_port;
	
    return 0;
}