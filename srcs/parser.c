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

int ft_parse_exec(t_struct *env, char *str)
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
	//env->dir[env->i] = NULL;
	return (1);
}

void	ft_pipe(int in, int out, t_struct *env)
{
	pid_t	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		if (in != 0)
		{
			dup2(in, 0);
			close(in);
		}
		if (out != 1)
		{
			dup2(out, 1);
			close(out);
		}
		execve(env->dir[env->i], env->temporary, env->env_array);
	}
	else
	{
		waitpid(pid, &status, 0);
		// if (env->j > env->count)
		// {

		// 	env->count++;
		// }
		// execve(env->dir[env->i], env->temporary, env->env_array);
	}
}

void	ft_parser(t_struct *env)
{
	int	len, in, out;
	int	fd[2];
	char	**tmp;

	env->j = 0;
	in = 0;
	out = fd[1];
	env->count = 1;
	env->env_array = ft_make_array(env);
	tmp = ft_split_pipe(env->s_cmd_line, '|');
	len = ft_arraylen(tmp);
	pipe(fd);
	while (env->j < len)
	{
		ft_parse_exec(env, tmp[env->j]);
		ft_pipe(in, fd[1], env);
		out = fd[1];
		close(fd[1]);
		in = fd[0];
		env->j++;
	}
	close(fd[0]);
	if (in != 0)
		dup2(in, 0);
	out = STDOUT_FILENO;
	if (len < 2)
		ft_pipe(in, out, env);
}
