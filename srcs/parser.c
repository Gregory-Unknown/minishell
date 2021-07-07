#include "../minishell.h"

char	*ft_space(char *str)
{
	char	*tmp;
	int	i;
	int	j;
	int	len;
	int	flag;

	if (!str)
		return (NULL);
	i = 0;
	flag = 0;
	len = ft_strlen(str);
	if (str[i] == 32)
	{
		while (str[i] && str[i] == 32)
			i++;
		flag = 1;
	}
	j = len - 1;
	if (str[j] == 32)
	{
		while (str[j] && str[j] == 32)
			j--;
		flag = 2;
	}
	if (!flag)
		return (str);
	tmp = ft_strdup(str);
	free(str);
	str = (char *)malloc(sizeof(char) * (j - i + 2));
	if (!str)
		return (NULL);
	len = j;
	j = 0;
	while (i <= len)
	{
		str[j] = tmp[i];
		j++;
		i++;
	}
	str[j] = '\0';
	free(tmp);
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
	if (!array)
		return (NULL);
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
	//ft_free(env->dir);
	ft_free(env->temporary);
	ft_free(env->env_array);
	ft_clear_all_list(&(env->s_com), free);
}

t_list1	*ft_make_list(t_struct *env)
{
	int i;
	int pipe;
	char	**tmp;
	t_list1	*head;

	env->env_array = ft_make_array(env);
	tmp = ft_split_pipe(env->s_cmd_line, '|');
	i = 0;
	while (tmp[i])
	{
		tmp[i] = ft_space(tmp[i]);
		i++;
	}
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

int	ft_is_redirect(char *s)
{
	if (ft_strncmp(s, ">>", 2) == 0)
		return (1);
	else if (ft_strncmp(s, ">", 1) == 0)
		return (1);
	else if (ft_strncmp(s, "<<", 2) == 0)
		return (1);
	else if (ft_strncmp(s, "<", 1) == 0)
		return (1);
	return (0);
}

int	ft_check_redirect(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_is_redirect(&s[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_find_count(char *s, t_list1 *tmp)
{
	int	i;
	int	flag;
	int	count;

	i = 0;
	flag = 0;
	count = 0;
	while (s[i] && ft_is_redirect(&s[i]) == 0)
	{
		if (flag == 0 && s[i] != 34 && s[i] != 39 && s[i] != 32 && s[i])
		{
			flag = 1;
			count++;
		}
		if (s[i] && flag && s[i] == 34)
		{
			i++;
			count++;
			while (s[i] && s[i] != 34)
				i++;
		}
		if (s[i] && flag && s[i] == 39)
		{
			i++;
			count++;
			while (s[i] && s[i] != 39)
				i++;
		}
		if (s[i] == 32 && flag == 1)
			flag = 0;
		i++;
	}
	if (s[i])
		tmp->redcom = ft_strdup(&s[i]);
	return (count);
}

void	ft_redirect(t_struct *env, t_list1 *tmp)
{
	int	i;
	int	count;
	char **s;

	count = ft_find_count(tmp->command, tmp);
	if (!count)
		env->temporary = NULL;
	if (ft_check_redirect(tmp->command))
	{
		i = 0;
		env->temporary = (char **)malloc(sizeof(char *) * (count + 1));
		s = ft_split_pipe(tmp->command, ' ');
		while (s[i] && ft_is_redirect(s[i]) == 0)
		{
			env->temporary[i] = ft_strdup(s[i]);
			i++;
		}
		env->temporary[i] = NULL;
	}
	else
		env->temporary = ft_split_pipe(tmp->command, ' ');
}

int	ft_parse_exec(t_struct *env, t_list1 *tmp)
{
	char	**path_arr;
	char	*s;
	struct	stat buf[4096];

	path_arr = ft_split(getenv("PATH"), ':');
	env->dir = (char **)malloc(sizeof(char *) * (ft_arraylen(path_arr) + 2));
	if (!env->dir)
		return (0);
	ft_redirect(env, tmp);
	env->i = 0;
	while (env->temporary[0] && path_arr[env->i])
	{
		s = ft_strjoin(path_arr[env->i], "/");
		if (!s)
			return (0);
		s = ft_strjoin1(s, env->temporary[0]);
		if (!s)
			return (0);
		env->dir[env->i] = ft_strdup(s);
		if (!env->dir[env->i])
			return (0);
		free(s);
		if (!stat(env->dir[env->i], buf))
		{
			env->dir[env->i + 1] = NULL;
			break;
		}
			env->i++;
	}
	if (env->dir[env->i + 1] != NULL)
		env->dir[env->i] = NULL;
	if (env->i == ft_arraylen(path_arr))
		printf("minishell: %s: command not found\n", env->temporary[0]);
	return (1);
}

void	ft_exec(t_struct *env, t_list1 *tmp)
{
	pid_t	pid;
	int	fd[2];
	int	i;

	pid = fork();
	if (!pid)
	{
		if (tmp->redcom)
		{
			tmp->redirect_command = ft_split_pipe(tmp->redcom, ' ');
			i = 0;
			while (tmp->redirect_command[i])
			{
				if (ft_strcmp(tmp->redirect_command[i], ">>") == 0)
				{
					i++;
					if (tmp->redirect_command[i])
						fd[1] = open(tmp->redirect_command[i], O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
					else
						printf("minishell: syntax error near unexpected token `newline'\n");
					if (fd[1] < 0)
						exit(1);
					dup2(fd[1], 1);
					close(fd[1]);
				}
				if (ft_strcmp(tmp->redirect_command[i], ">") == 0)
				{
					i++;
					if (tmp->redirect_command[i])
						fd[1] = open(tmp->redirect_command[i], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
					else
						printf("minishell: syntax error near unexpected token `newline'\n");
					if (fd[1] < 0)
						exit(1);
					dup2(fd[1], 1);
					close(fd[1]);
				}
				if (ft_strcmp(tmp->redirect_command[i], "<<") == 0)
				{
						char	*line;

						i++;
						if (tmp->redirect_command[i])
						{
							while (ft_strcmp((line = readline("> ")), tmp->redirect_command[i]))
								;
						}
						else
							printf("bash: syntax error near unexpected token `newline'\n");
						close(fd[1]);
						dup2(fd[0], 0);
						close(fd[0]);
				}
				if (ft_strcmp(tmp->redirect_command[i], "<") == 0)
				{
					i++;
					fd[0] = open(tmp->redirect_command[i], O_RDONLY);
					if (fd[0] < 0)
						printf("minishell: %s: No such file or directory\n", tmp->redirect_command[i]);
					dup2(fd[0], 0);
					close(fd[0]);
					close(fd[1]);
				}
				i++;
			}
		}
		if (env->temporary)
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
		dup2(fd[1], 1);
		close(fd[0]);
		ft_exec(env, tmp);
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
	int	res;

	res = 0;
	env->dir = 0;
	env->temporary = 0;
	env->s_com = ft_make_list(env);
	tmp = env->s_com;
	fd = dup(0);
	while (tmp->pipe)
	{
		ft_parse_exec(env, tmp);
		ft_pipe(env, tmp);
		tmp = tmp->next;
	}
	ft_parse_exec(env, tmp);
	ft_exec(env, tmp);
	dup2(fd, 0);
	while (wait(NULL) > 0)
		;
	ft_clean(env);
}
