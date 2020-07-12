#include "include.h"

void    ft_screenshot(char *name)
{
    int fd;

    int	fd;
	if (!((fd = open(fileName, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) > 0))
	{
			ft_putstr_fd("Error\nin while creating file bmp\n", STDOUT);
			freeAll(ERROR);
	}
	write_header(fd, infoBmpFile);
	write_file(fd);
	close(fd);
}