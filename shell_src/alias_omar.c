#include "../includes/sh.h"

char	*get_my_alias(char *str, int *a)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	while (str[i] && (str[i] == '\n' || str[i] == '\t' || str[i] == ' '))
		i++;
	j = i;
	while (str[i] && str[i] != '\n' && str[i] != '\t' && str[i] != ' ')
		i++;
	new = ft_strsub(str, j, i - j);
	if (ft_strchr(new, '$') ||  ft_strchr(new, '$'))
	{
		free(new);
		return (NULL);
	}
	a[0] = i;
	return (new);
}

char	*replace_alias(char *new)
{
	t_alias	*alias;

	alias = g_alias;
	while (alias)
	{
		if (ft_strcmp(alias->alias, new) == 0)
		{
			free(new);
			return (ft_strdup(alias->value));
		}
		alias = alias->next;
	}
	free(new);
	return (NULL);
}

char	*switch_to_alias(char *str)
{
	char	*new;
	int		j;
	char	*tmp;

	new = get_my_alias(str, &j);
	if (new == NULL)
		return (str);
	new = replace_alias(new);
	if (new == NULL)
		return (str);
	tmp = str;
	str = ft_strsub(str, j, ft_strlen(str) - j);
	free(tmp);
	tmp = new;
	new = ft_strjoin(new, str);
	free(tmp);
	free(str);
	return (new);
}