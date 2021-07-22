#include "../minishell.h"

static char	*ft_split_command(char *str, char c)
{
	char **s;
	int	i;

	i = 0;
	s = ft_split(str, c);
	free(str);
	str = ft_space(ft_strdup(s[0]));
	i = 1;
	while (s[i])
	{
		str = ft_strjoin1(str, ft_space(s[i]));
		i++;
	}
	return (str);
}

char	*ft_name_check1(char *str)
{
	if (!ft_strchr(str, '\"'))
		return (str);
	if (ft_strchr(str, '\"'))
		return(ft_split_command(str, '\"'));
	return (str);
}


char	*ft_name_check2(char *str)
{
	if (!ft_strchr(str, '\''))
		return (str);
	else if (ft_strchr(str, '\''))
		return(ft_split_command(str, '\''));
	return (str);
}

void	ft_name_quotes1(t_list1 *tmp)
{
	int	i;

	i = 0;
	while (tmp->temporary[i])
	{
		tmp->temporary[i] = ft_name_check1(tmp->temporary[i]);
		i++;
	}
}
void	ft_name_quotes2(t_list1 *tmp)
{
	int	i;

	i = 0;
	while (tmp->temporary[i])
	{
		tmp->temporary[i] = ft_name_check2(tmp->temporary[i]);
		i++;
	}
}

int	ft_check_buildins(char *str)
{
	if (ft_strcmp(str, "env") == 0)
		return (1);
	else if (ft_strcmp(str, "export") == 0)
		return (1);
	else if (ft_strcmp(str, "unset") == 0)
		return (1);
	else if (ft_strcmp(str, "echo") == 0)
		return (1);
	else if (ft_strcmp(str, "cd") == 0)
		return (1);
	else if (ft_strcmp(str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

void	ft_buildins_one(t_struct *env, t_list1 *fd, int *flag)
{
	*flag = 0;
	if (ft_strcmp(fd->temporary[0], "env") == 0)
		ft_print_env(env, fd);
	else if (ft_strcmp(fd->temporary[0], "export") == 0)
		ft_export(env, fd);
	else if (ft_strcmp(fd->temporary[0], "unset") == 0)
		ft_unset(env, fd);
	else if (ft_strcmp(fd->temporary[0], "cd") == 0)
		ft_cd(env, fd);
	else if (ft_strcmp(fd->temporary[0], "pwd") == 0)
		ft_pwd(fd);
	else if (ft_strcmp(fd->temporary[0], "exit") == 0)
		return ;
	else
		*flag = 1;
}

void	ft_buildins(t_struct *env, t_list1 *fd)
{

	if (ft_strcmp(fd->temporary[0], "env") == 0)
		ft_print_env(env, fd);
	else if (ft_strcmp(fd->temporary[0], "export") == 0)
		ft_export(env, fd);
	else if (ft_strcmp(fd->temporary[0], "unset") == 0)
		ft_unset(env, fd);
	else if (ft_strcmp(fd->temporary[0], "echo") == 0)
		ft_echo(fd);
	else if (ft_strcmp(fd->temporary[0], "cd") == 0)
		ft_cd(env, fd);
	if (ft_strcmp(fd->temporary[0], "pwd") == 0)
		ft_pwd(fd);
	if (ft_strcmp(fd->temporary[0], "exit") == 0)
		return ;
}
