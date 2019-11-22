#ifndef MI_RS232_H
#define MI_RS232_H

int rs232init(char *puerto, int velocidad);
void rs232close(int fd);
int rs232rx(int fd);
void rs232tx(int fd, int caracter);
void rs232leo(int fd);
void rs232escribo(int fd);

#endif // MI_RS232_H
