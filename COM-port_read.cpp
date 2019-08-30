#include <stdio.h>   /* Стандартные объявления ввода/вывода */
#include <string.h>  /* Объявления строковых функций */
#include <unistd.h>  /* Объявления стандартных функций UNIX */
#include <fcntl.h>   /* Объявления управления файлами */
#include <errno.h>   /* Объявления кодов ошибок */
#include <termios.h> /* Объявления управления POSIX-терминалом */
#include <fstream>   /* Объявление функции записи*/
#include <iostream>  /* Объявление функции ввода-вывода*/
#include <ctime>	 /* Функции времени*/
using namespace std;

#include <sys/select.h>
 
int fd; /* Файловый дескриптор для порта */
char buf[10]={0};/*размер зависит от размера строки принимаемых данных*/ 
int iIn;
FILE* f;

#ifndef _KBHIT_H_
#define _KBHIT_H_
int kbhit()
{
    struct timeval tv;
    fd_set read_fd;
 
    tv.tv_sec=0;
    tv.tv_usec=0;
    FD_ZERO(&read_fd);
    FD_SET(0,&read_fd);
 
    if(select(1, &read_fd, NULL, NULL, &tv) == -1)
        return 0;
 
    if(FD_ISSET(0,&read_fd))
        return 1;
 
    return 0;
}
#endif //_KBHIT_H_

int open_port(void);
int main(void) { 
  
  port_set:
    fd = open("/dev/ttyACM1", O_RDWR | O_NOCTTY | O_NDELAY); /*'open_port()' - Открывает последовательный порт ttyACMx */
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
 // вывод времени: год месяц день час минута секунда
	time_t seconds = time(NULL);
	tm* timeinfo = localtime(&seconds);
	f = fopen("/home/serg/port.txt", "at");
	fprintf (f, "%s", asctime(timeinfo));
	fclose(f); 
 
 read_port:
	while(!kbhit ()){ 							 //если не нажата клавиша, выполнять цикл
		iIn=read(fd,buf,10);					 /*чтения приходящих данных из порта*/
		f = fopen("/home/serg/port.txt", "at"); // окрываем файл для записи
 		fprintf (f, "%s", buf);
		cout<<buf;
		fclose(f); 

		goto read_port;
	}
    
    time_t secondss = time(NULL);
	tm* timeinfoo = localtime(&secondss);
    f = fopen("/home/serg/port.txt", "at");
    fprintf (f, "%s", asctime(timeinfoo));
    fclose(f); 

    return 0;
}