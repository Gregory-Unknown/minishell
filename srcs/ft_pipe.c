#include "../minishell.h"

// void	ft_pipe(t_struct *env, t_list1 *tmp)
// {
// 	//int fd[2];
// 	//char *str;

// 	// str = ft_strdup(tmp->next->command);
// 	// if (!ft_checker_left_red(str))
// 	// {
// 	// 	free(str);
// 	// 	return ;
// 	// }
// 	// else
// 	// 	free(str);
// 	pipe(tmp->fd);
// 	tmp->pid = fork();
// 	if (tmp->pid == -1)
// 		exit(-1);
// 	else if (tmp->pid == 0)
// 	{
// 		dup2(tmp->fd[1], 1);
// 		close(tmp->fd[0]);
// 		ft_exec(env, tmp);
// 		close(tmp->fd[1]);
// 		exit(1);
// 	}
// 	else
// 	{
// 		dup2(tmp->fd[0], 0);
// 		close(tmp->fd[0]);
// 		close(tmp->fd[1]);
// 	}
// }

void	ft_pipe(t_struct *env, t_list1 *tmp)
{
	int fd[2];

	pipe(fd);
	tmp->pid = fork();
	if (tmp->pid == -1)
		exit(-1);
	else if (tmp->pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		ft_exec(env, tmp);
		close(fd[1]);
		exit(1);
	}
	else
	{
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
	}
}

void	ft_pipe_start(t_struct *env)
{
	t_list1 *tmp;
	int	fd0;

	tmp = env->s_com;
	fd0 = dup(0);
	while (tmp->pipe && !g_status)
	{
		ft_pipe(env, tmp);
		tmp = tmp->next;
	}
	ft_exec(env, tmp);
	dup2(fd0, 0);
	while (wait(NULL) > 0)
		;
}
