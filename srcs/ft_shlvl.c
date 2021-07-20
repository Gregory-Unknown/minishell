#include "../minishell.h"

typedef struct s_shlvl
{
	int			lvl_num;
	char		*lvl;
	char		*tmp;
	char		*value;
	char		*lvl_str;
}t_shlvl;

static void	ft_shell_lvl_dec(t_list *head, t_shlvl *shlvl)
{
	shlvl->value = ft_strdup(head->content);
	free(head->content);
	shlvl->tmp = ft_substr(shlvl->value, 0, 6);
	shlvl->lvl = ft_substr(shlvl->value, 6, ft_strlen(shlvl->value));
	shlvl->lvl_num = ft_atoi(shlvl->lvl);
	if (shlvl->lvl_num > 1)
	{
		shlvl->lvl_num -= 1;
		shlvl->lvl_str = ft_itoa(shlvl->lvl_num);
		head->content = ft_strjoin1(shlvl->tmp, shlvl->lvl_str);
	}
}

static void	ft_shell_lvl_inc(t_list *head, t_shlvl *shlvl)
{
	shlvl->tmp = ft_substr(head->content, 0, 6);
	shlvl->lvl = ft_substr(head->content, 6, ft_strlen(head->content));
	shlvl->lvl_num = ft_atoi(shlvl->lvl);
	shlvl->lvl_num += 1;
	shlvl->lvl_str = ft_itoa(shlvl->lvl_num);
	shlvl->value = ft_strjoin1(shlvl->tmp, shlvl->lvl_str);
	free(head->content);
	head->content = ft_strdup(shlvl->value);
}

void	ft_shell_lvl(t_struct *env)
{
	t_list	*head;
	t_shlvl	*shlvl;

	shlvl = 0;
	head = 0;
	shlvl = (t_shlvl *)malloc(sizeof(t_shlvl));
	head = env->s_env;
	while (head)
	{
		if (ft_strncmp(head->content, "SHLVL=", 6) == 0)
			ft_shell_lvl_inc(head, shlvl);
		if (ft_strcmp(ft_space(env->s_cmd_line), "exit") == 0)
			ft_shell_lvl_dec(head, shlvl);
		if (ft_space(env->s_cmd_line) == 0)
			ft_shell_lvl_dec(head, shlvl);
		head = head->next;
	}
	free(shlvl);
}
