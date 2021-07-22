#include <stdio.h>
#include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

int	main()
{
	char	*line;
	char	**str;
	int	i;

	line = ft_strdup("ls -la \"| grep\" a >> 123 | wc > 1");
	str = ft_split_pipe(line, '|');
	printf("STROKA %s\n", line);
	i = 0;
	while (str[i])
	{
		printf("STROKA |%s|\n", str[i]);
		i++;
	}
	free(line);
	ft_free(str);
	return (0);
}
//gcc libft/ft_strdup.c libft/ft_strncmp.c libft/ft_strlen.c mim.c libft/ft_split.c libft/ft_strjoin.c libft/ft_strjoin1.c libft/ft_substr.c && ./a.out
