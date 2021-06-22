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

int ft_exec(t_struct *env, char *str)
{
	char	**path_arr;
	char	*tmp;
	char	*final;
	pid_t	pid;
	int	i;
	char	**temporary;
	char	**dir;
	struct	stat buf[4096];
	path_arr = ft_split(getenv("PATH"), ':');
	dir = (char **)malloc(sizeof(char *) * ft_arraylen((path_arr) + 2));
	temporary = ft_split(str, ' ');
	i = 0;
	while (path_arr[i])
	{
		tmp = ft_strjoin(path_arr[i], "/");
		final = ft_strjoin1(tmp, temporary[0]);
		dir[i] = ft_strdup(final);
		free(final);
		if (!stat(dir[i], buf))
			break;
		i++;
	}
	pid = fork();
	if (pid == 0)
		execve(dir[i], temporary, env->env_array);
	wait(0);
	return (1);
}

int	ft_pipe(int in, int out, char *str, t_struct *env)
{
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
		return (ft_exec(env, str));
	}
	return (pid);
}

void	ft_parser(t_struct *env)
{
	int	i;
	int	len;
	int	in;
	int	out;
	int	fd[2];
	pid_t	pid;
	char	**tmp;

	i = 0;
	in = 0;
	env->env_array = ft_make_array(env);
	tmp = ft_split_pipe(env->s_cmd_line, '|');
	len = ft_arraylen(tmp);
	while (i < len - 1)
	{
		opipe(fd);
		ft_pipe(in, fd[1],tmp[i], env);
		close(fd[1]);
		in = fd[0];
		i++;
	}
	if (in != 0)
		dup2(in, 0);
	ft_pipe(in, fd[1],tmp[i], env);
}
