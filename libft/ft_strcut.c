#include "libft.h"

char	*ft_strcut(char *str, int from, int to)
{
	char	*newstr;
	int 	i;
	int	j;

	i = 0;
	j = from;
	if (!str || to < from)
		return (NULL);
	newstr = ft_strnew(to - from + 1);
	while (str[j] && j < to)
	{
		newstr[i] = str[j];
		i++;
		j++;
	}
	return (newstr);
}
