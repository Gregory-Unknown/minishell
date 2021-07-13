#include "../minishell.h"

void	ft_print_echo(int i, t_struct *env, int (*fd))
{
	while (i < ft_arraylen(env->temporary) - 1)
	{
		write(fd[1], env->temporary[i], ft_strlen(env->temporary[i]));
		write(fd[1], " ", 1);
		i++;
	}
	write(fd[1], env->temporary[i], ft_strlen(env->temporary[i]));
}

int	ft_echo(t_struct *env, int (*fd))
{
	if (ft_strcmp(env->temporary[0], "echo"))
	{
		write(fd[1], "minishell: ", 11);
		write(fd[1], env->temporary[0], ft_strlen(env->temporary[0]));
		write(fd[1], ": command not found\n", 20);
		return (1);
	}
	if (!env->temporary[1])
		write(fd[1], "\n", 1);
	else if (ft_strcmp(env->temporary[1], "-n") == 0)
	{
		if (!env->temporary[2])
			write(fd[1], "", 1);
		else
			ft_print_echo(2, env, fd);
	}
	else
	{
		ft_print_echo(1, env, fd);
		write(fd[1], "\n", 1);
	}
	return (0);
}
