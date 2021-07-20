#include "../minishell.h"

void	ft_update_pwd(t_struct *env)
{
	t_list	*tmp;
	char	*tmp2;
	char	**tmp3;
	char	str[1024];

	tmp = env->s_env;
	tmp2 = 0;
	getcwd(str, sizeof(str));
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "PWD=", 4) == 0)
		{
			tmp2 = ft_strdup(tmp->content);
			free(tmp->content);
			tmp->content = ft_strjoin("PWD=", str);
		}
		else if (tmp2 && ft_strncmp(tmp->content, "OLDPWD=", 7) == 0)
		{
			free(tmp->content);
			tmp3 = ft_split(tmp2, '=');
			tmp->content = ft_strjoin("OLDPWD=", tmp3[1]);
			free(tmp2);
			ft_free(tmp3);
		}
		tmp = tmp->next;
	}
}

int	ft_cd(t_struct *env, t_list1 *fd)
{
	char *str;

	if (fd->temporary[1] == 0)
	{
		chdir(getenv("HOME"));
		ft_update_pwd(env);
		return (1);
	}
	str = getcwd(0, 0);
	if (fd->temporary[1][0] == '~')
	{
		if (fd->temporary[1][1] == '/')
			fd->temporary[1] = ft_strjoin(getenv("HOME"), &fd->temporary[1][1]);
		else if (fd->temporary[1][1] == 0)
		{
			chdir(getenv("HOME"));
			free(str);
			ft_update_pwd(env);
			return (1);
		}
	}
	if (chdir(fd->temporary[1]) == -1)
	{
		chdir(str);
		free(str);
		ft_update_pwd(env);
		return (-1);
	}
	free(str);
	ft_update_pwd(env);
	return (1);
}
