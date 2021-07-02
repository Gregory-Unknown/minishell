#include "../minishell.h"

char	*ft_space(char *str)
{
	char	*tmp;
	int	i;
	int	j;
	int	len;
	if (str[0] == 32 || str[ft_strlen(str) - 1] == 32)
	{
		tmp = ft_strdup(str);
		free(str);
		len = ft_strlen(tmp);
		i = 0;
		while (tmp[i] && tmp[i] == 32)
		{
			i++;
		}
		j = len - 1;
		while (tmp[j] && tmp[j] == 32)
		{
			j--;
		}
		str = (char *)malloc(sizeof(char) * (j - i + 1));
		j = 0;
		while (i < len)
		{
			str[j] = tmp[i];
			j++;
			i++;
		}
		str[j] = '\0';
		free(tmp);
	}
	return (str);
}

char	**ft_make_array(t_struct *env)
{
	char	**array;
	t_list	*tmp;
	int	i;

	tmp = env->s_env;
	i = ft_lstsize(tmp) + 1;
	array = (char **)malloc(sizeof(char *) * i);
	i = 0;
	while (tmp)
	{
		array[i] = ft_strdup(tmp->content);
		i++;
		tmp = tmp->next;
	}
	array[i] = NULL;
	return (array);
}

void	ft_clean(t_struct *env)
{
	ft_free(env->dir);
	ft_free(env->temporary);
}

t_list1	*ft_make_list(t_struct *env)
{
	int i;
	int pipe;
	char	**tmp;
	t_list1	*head;

	env->env_array = ft_make_array(env);
	tmp = ft_split_pipe(env->s_cmd_line, '|');
	env->len = ft_arraylen(tmp);
	pipe = 0;
	if (env->len > 1)
		pipe = 1;
	i = 0;
	while (tmp[i])
	{
		if (tmp[i + 1] == 0)
			pipe = 0;
		ft_push_back(&head, ft_new_list(tmp[i], pipe));
		i++;
	}
	return (head);
}

int	ft_parse_exec(t_struct *env, char *str)
{
	char	**path_arr;
	char	*tmp;
	struct	stat buf[4096];

	path_arr = ft_split(getenv("PATH"), ':');
	env->dir = (char **)malloc(sizeof(char *) * ft_arraylen((path_arr) + 1));
	env->temporary = ft_split(str, ' ');
	env->i = 0;
	while (path_arr[env->i])
	{
		tmp = ft_strjoin(path_arr[env->i], "/");
		tmp = ft_strjoin1(tmp, env->temporary[0]);
		env->dir[env->i] = ft_strdup(tmp);
		free(tmp);
		if (!stat(env->dir[env->i], buf))
			break;
		env->i++;
	}
	return (1);
}

void	ft_exec(t_struct *env)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		execve(env->dir[env->i], env->temporary, env->env_array);
		exit(-1);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}

void	ft_pipe(t_struct *env, t_list1 *tmp)
{
	int fd[2];

	if (tmp->pipe)
		pipe(fd);
	tmp->pid = fork();
	if (tmp->pid == -1)
	{
		exit(-1);
	}
	else if (tmp->pid == 0)
	{
		if (tmp->pipe)
		{
			dup2(fd[1], 1);
			close(fd[0]);
		}
		ft_exec(env);
		close(fd[1]);
		exit(-1);
	}
	else
	{
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
	}
}

void	ft_parser(t_struct *env)
{
	t_list1 *tmp;
	int	fd;

	env->s_com = ft_make_list(env);
	tmp = env->s_com;
	fd = dup(0);
	while (tmp->next)
	{
		ft_parse_exec(env, tmp->command);
		ft_pipe(env, tmp);
		tmp = tmp->next;
	}
	if (tmp->command)
		ft_parse_exec(env, tmp->command);
	ft_exec(env);
	dup2(fd, 0);
	while (wait(NULL) > 0)
		;
}
