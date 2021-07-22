#include "../minishell.h"

void	ft_double_right(char *str, t_list1 *tmp)
{
	if (str)
	{
		if (tmp->fd[1] != 1)
			close(tmp->fd[1]);
		tmp->fd[1] = open(str, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
		if (tmp->fd[1] < 0)
			exit(1);
	}
	else
	{
		printf("minishell: syntax error near unexpected token `newline'1\n");
		g_status = 258;
		return ;
	}
	tmp->dr = 1;
}

void	ft_single_right(char *str, t_list1 *tmp)
{
	if (str)
	{
		if (tmp->fd[1] != 1)
			close(tmp->fd[1]);
		tmp->fd[1] = open(str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		if (tmp->fd[1] < 0)
			exit(1);
	}
	else
	{
		printf("minishell: syntax error near unexpected token `newline'2\n");
		g_status = 258;
		return ;
	}
	tmp->sr = 1;
}

void	ft_double_left(char *str, t_list1 *tmp)
{
	char	*line;
	int	fds;
	fds = 0;
	if (str)
	{
		fds = open(".tmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		if (fds < 0)
			printf("minishell: %s: No such file or directory\n", str);
		while (ft_strcmp((line = readline("> ")), str))
		{
			write(fds, line, ft_strlen(line));
			write(fds, "\n", 1);
		}
		close(fds);
	}
	else
		printf("bash: syntax error near unexpected token `newline'3\n");
	tmp->fd[0] = open(".tmp", O_RDONLY);
	if (tmp->fd[0] < 0)
		printf("minishell: %s: No such file or directory\n", str);
	tmp->dl = 1;
}

void	ft_single_left(char *str, t_list1 *tmp)
{
	if (str)
	{
		tmp->fd[0] = open(str, O_RDONLY);
		if (tmp->fd[0] < 0)
			printf("minishell: %s: No such file or directory\n", str);
	}
	else
		printf("bash: syntax error near unexpected token `newline'4\n");
	tmp->sl = 1;
}
