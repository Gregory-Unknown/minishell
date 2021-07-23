#include "../minishell.h"

static void	ft_check_fd(t_list1 *tmp)
{
	if (tmp->dr == 1)
	{
		dup2(tmp->fd[1], 1);
		close(tmp->fd[1]);
	}
	else if (tmp->sr == 1)
	{
		dup2(tmp->fd[1], 1);
		close(tmp->fd[1]);
	}
	else if (tmp->dl == 1)
	{
		dup2(tmp->fd[0], 0);
		close(tmp->fd[0]);
	}
	else if (tmp->sl == 1)
	{
		dup2(tmp->fd[0], 0);
		close(tmp->fd[0]);
	}
	else
	{
		dup2(tmp->fd[0], 0);
		dup2(tmp->fd[1], 1);
	}
}

static void	ft_fork_execve(t_struct *env, t_list1 *tmp, pid_t pid)
{
	pid = fork();
	if (pid == -1)
	{
		ft_clean(env);
		exit(-1);
	}
	else if (!pid)
	{
		if (tmp->builtins)
		{
			ft_buildins(env, tmp);
			ft_clean(env);
		}
		else
		{
			ft_check_fd(tmp);
			if (tmp->temporary && !g_status)
				g_status = execve(tmp->dir[tmp->i],
						tmp->temporary, env->env_array);
			ft_clean(env);
		}
		exit(1);
	}
	else
		waitpid(pid, NULL, 0);
}

void	ft_exec(t_struct *env, t_list1 *tmp)
{
	int		flag;
	pid_t	pid;

	pid = 0;
	flag = 1;
	if (!env->count_pipe && tmp->builtins)
		ft_buildins_one(env, tmp, &flag);
	if (flag)
		ft_fork_execve(env, tmp, pid);
}
