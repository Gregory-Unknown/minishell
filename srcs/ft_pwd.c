#include "../minishell.h"

void	ft_pwd(int (*fd))
{
	char	cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		write(fd[1], cwd, ft_strlen(cwd));
		write(fd[1], "\n", 1);
	}
	// else
	// 	perror("getcwd() error");
}
