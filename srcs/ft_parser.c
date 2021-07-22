#include "../minishell.h"

void	ft_check_error()
{
	// if (g_status == 127)

	// if (g_status == 126)
}

void	ft_clean(t_struct *env)
{
	ft_clear_all_list(&(env->s_com), free);
}

t_list1	*ft_make_list(t_struct *env)
{
	int	i;
	int	len;
	char	**tmp;
	t_list1	*head;

	env->s_com = 0;
	head = env->s_com;
	tmp = ft_split_pipe(env->s_cmd_line, '|');
	i = 0;
	len = ft_arraylen(tmp) - 1;
	while (i < len)
	{
		ft_push_back(&head, (ft_new_list(ft_space(ft_strdup(tmp[i])), 1)));
		env->count_pipe++;
		i++;
	}
	ft_push_back(&head, ft_new_list(ft_space(ft_strdup(tmp[i])), 0));
	return (head);
}

void	ft_pass_quote(int *i, char *str)
{
	if (str[*i] && str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] && str[*i] != '\'')
			(*i)++;
	}
	if (str[*i] && str[*i] == '\"')
	{
		(*i)++;
		while (str[*i] && str[*i] != '\"')
			(*i)++;
	}
}

int	ft_find_redirection(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		ft_pass_quote(&i, str);
		flag++;
		if (ft_strncmp(&str[i], ">>", 2) == 0)
			return (i);
		else if (ft_strncmp(&str[i], ">", 1) == 0)
			return (i);
		else if (ft_strncmp(&str[i], "<<", 2) == 0)
			return (i);
		else if (ft_strncmp(&str[i], "<", 1) == 0)
			return (i);
		else
			flag--;
		i++;
	}
	if (flag)
		return (0);
	return (-1);
}

void	ft_redirect_check_out(t_list1 *tmp)
{
	int	i;
	char	*str;

	str = 0;
	i = ft_find_redirection(tmp->command);
	if (i > 0)
	{
		str = ft_strdup(tmp->command);
		free(tmp->command);
		tmp->command = 0;
		tmp->command = ft_substr(str, 0, i);
		tmp->redcom = ft_strdup(&str[i]);
		free(str);
	}
	else if (i == 0)
	{
		tmp->redcom = ft_strdup(tmp->command);
		free(tmp->command);
		tmp->command = 0;
	}
}


int	ft_is_redirect(char *s)
{
	if (ft_strncmp(s, ">>", 2) == 0)
		return (2);
	else if (ft_strncmp(s, ">", 1) == 0)
		return (1);
	else if (ft_strncmp(s, "<<", 2) == 0)
		return (2);
	else if (ft_strncmp(s, "<", 1) == 0)
		return (1);
	return (0);
}

int	ft_check_end(char *str, int i)
{
	i++;
	while (str[i] && ft_is_redirect(&str[i]) == 0)
		i++;
	return (i);
}

void	ft_redirect_split_out(t_list1 *tmp)
{
	int	i;
	int	j;
	int	num;
	char	*temp;
	char	*str;

	i = 0;
	str = ft_strdup("");
	while (tmp->redcom[i])
	{
		num = ft_is_redirect(&(tmp->redcom)[i]);
		if (num)
		{
			if (num == 1)
				j = ft_check_end(tmp->redcom, i);
			else if (num == 2)
				j = ft_check_end(tmp->redcom, i + 1);
			temp = ft_strjoin("/", ft_substr(tmp->redcom, i, j));
			str = ft_strjoin1(str, temp);
			free(temp);
		}
		i++;
	}
	tmp->redirect_command = ft_split(str, '/');
	free(str);
}

void	ft_get_path_param(t_list1 *tmp)
{
	tmp->dir = ft_malloc_array(2);
	tmp->i = 0;
	tmp->dir[tmp->i] = ft_strdup(tmp->temporary[0]);
	tmp->i = 1;
	tmp->dir[tmp->i] = 0;
	tmp->i = 0;
}

void	ft_check_valid_path(t_list1 *tmp)
{
	struct	stat buf[4096];

	if (!stat(tmp->temporary[0], buf))
	{
		tmp->dir = ft_malloc_array(2);
		tmp->dir[0] = ft_strdup(tmp->temporary[0]);
		tmp->dir[1] = 0;
	}
	else
		g_status = 127;
}

void	ft_find_path(t_list1 *tmp, char **path_arr)
{
	char	*s;
	struct	stat buf[4096];

	while (path_arr[tmp->i] && !g_status)
	{
		s = ft_strjoin(path_arr[tmp->i], "/");
		s = ft_strjoin1(s, tmp->temporary[0]);
		tmp->dir[tmp->i] = ft_strdup(s);
		free(s);
		if (!stat(tmp->dir[tmp->i], buf))
		{
			tmp->dir[tmp->i + 1] = NULL;
			break;
		}
			tmp->i++;
	}
	if (tmp->dir[tmp->i + 1] != NULL)
		tmp->dir[tmp->i] = NULL;
}

void	ft_get_path_command(t_list1	*tmp)
{
	char	**path_arr;

	path_arr = ft_split(getenv("PATH"), ':');
	if (!path_arr)
		exit(-1);
	tmp->dir = ft_malloc_array(ft_arraylen(path_arr) + 2);
	tmp->i = 0;
	ft_find_path(tmp, path_arr);
	if (tmp->i >= ft_arraylen(path_arr))
		g_status = 127;
}

void	ft_command_check_out(t_list1 *tmp, t_struct *env)
{
	tmp->temporary = ft_split_pipe(tmp->command, ' ');
	ft_name_quotes1(tmp);
	ft_check_dollar(tmp, env);
	ft_name_quotes2(tmp);
	if (tmp->temporary && !ft_strcmp(tmp->temporary[0], "./minishell") && !tmp->temporary[1] && !g_status)
		ft_shell_lvl(env);
	else if (ft_strncmp(tmp->temporary[0], "./", 2) == 0)
		ft_get_path_param(tmp);
	else if (tmp->temporary[0][0] == '/')
		ft_check_valid_path(tmp);
	else if(ft_check_buildins(tmp->temporary[0]))
		tmp->builtins = 1;
	else
		ft_get_path_command(tmp);
}

void	ft_make_list_redirect(t_struct *env)
{
	int	i;
	t_list1	*tmp;

	i = 0;
	tmp = env->s_com;
	while (tmp && !g_status)
	{
		ft_redirect_check_out(tmp);
		if (tmp->redcom && !g_status)
			ft_redirect_split_out(tmp);
		if (tmp->command && !g_status)
			ft_command_check_out(tmp, env);
		if (tmp->redcom && !g_status)
			ft_process_redirect(tmp);

		tmp = tmp->next;
	}
}

void	ft_init_param(t_struct *env)
{
	env->s_com = ft_make_list(env);
	ft_make_list_redirect(env);
}

void	ft_parser(t_struct *env)
{
	ft_init_param(env);
	if (!g_status)
		ft_pipe_start(env);
	ft_check_error();
}
