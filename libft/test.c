#include "libft.h"

int main(int ac, char **av)
{
	ft_putendl(ft_strcut(av[1], ft_atoi(av[2]), ft_atoi(av[3])));
	return(0);
}

