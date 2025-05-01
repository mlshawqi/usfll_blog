#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
// #include <fcntl.h> 
// int main()
// {
// 	int fd = open("aa.txt", O_WRONLY | O_CREAT);
// 	int fd2 = open("aa.txt", O_WRONLY | O_CREAT);
// 	ft_putchar_fd('a', fd);
// 	printf("\n%d  %d", fd, fd2);
// }