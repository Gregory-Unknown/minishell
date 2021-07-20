#include <stdio.h>
#include "libft/libft.h"

char	*ft_space(char *str)
{
	int	i;
	int	j;
	int	len;

	if (!str)
		return (NULL);
	i = 0;
	len = ft_strlen(str);
	if (str[i] == 32)
	{
		while (str[i] && str[i] == 32)
			i++;
	}
	j = len - 1;
	if (str[j] == 32)
	{
		while (str[j] && str[j] == 32)
			j--;
	}
	if (i == 0 && j + 1 == len)
		return (str);
	return (ft_substr(str, i, j + 1));
}

int	ft_is_redirect(char *s)
{
	if (ft_strncmp(s, ">>", 2) == 0)
		return (2);
	else if (ft_strncmp(s, ">", 1) == 0)
		return (1);
	else if (ft_strncmp(s, "<<", 2) == 0)
		return (2);
	else if (ft_strncmp(s, "<", 1) == 0)
		return (1);
	return (0);
}

int	ft_check_end(char *str, int i)
{
	i++;
	while (str[i] && ft_is_redirect(&str[i]) == 0)
		i++;
	return (i);
}

void	ft_redirect_split_out(char *redcom)
{
	int	i;
	int	j;
	int	num;
	char	*str;
	char	*tmp;
	char	**redirect_command;

	i = 0;
	j = 0;
	str = ft_strdup(redcom);
	free(redcom);
	redcom = ft_strdup("");
	while (str[i])
	{
		num = ft_is_redirect(&str[i]);
		if (num)
		{
			if (num == 1)
				j = ft_check_end(str, i);
			else if (num == 2)
				j = ft_check_end(str, i + 1);
			printf("i = %d\nj = %d\n\n", i, j);
			tmp = ft_strjoin("/", ft_substr(str, i, j));
			redcom = ft_strjoin1(redcom, ft_space(tmp));
			free(tmp);
		}
		i++;
	}
	redirect_command = ft_split(redcom, '/');
	i = 0;
	while (redirect_command[i])
	{
		printf("redirect[%d] - %s\n", i, redirect_command[i]);
		i++;
	}
}

int	main()
{
	char	*str = ft_strdup("         >1>2>3>4>5>6>7>8>9");
	char	*s = ft_space(str);
	//ft_redirect_split_out(str);
	printf("%s\n", s);
	free(str);
}
//gcc libft/ft_strdup.c libft/ft_strncmp.c libft/ft_strlen.c mim.c libft/ft_split.c libft/ft_strjoin.c libft/ft_strjoin1.c libft/ft_substr.c && ./a.out
