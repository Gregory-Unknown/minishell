#include "../minishell.h"

// int	ft_check_digit(t_cmd *cmd_list)
// {
// 	int	i;

// 	i = -1;
// 	if (cmd_list->cmdline[1].cmd[0] == '-')
// 		i++;
// 	while (cmd_list->cmdline[1].cmd[++i] != '\0')
// 		if (ft_isdigit(cmd_list->cmdline[1].cmd[i]) == 0)
// 		{
// 			if (cmd_list->exit_flag == 1)
// 			{
// 				cmd_list->err_manage.errcode = 4;
// 				cmd_list->err_manage.errindex = 1;
// 				print_errstr(cmd_list);
// 				exit(-1);
// 			}
// 			else
// 				return (0);
// 		}
// 	return (1);
// }

int				ft_exit(t_struct *env)
{
	long long	result;
	int	number;
	int	flag;

	flag = 0;
	number = 0;
	result = 0;
	(void)env;
	if (g_status == 0)
		printf("exit\n");
	// if (env->temporary[1])
	// {
	// 	if (ft_check_digit(env->temporary) == 0)
	// 	{
	// 		cmd_list->err_manage.errcode = 4;
	// 		cmd_list->err_manage.errindex = 1;
	// 		return (-1);
	// 	}
	// 	if (cmd_list->cmdline[2].cmd != NULL)
	// 	{
	// 		cmd_list->err_manage.errcode = 2;
	// 		return (-1);
	// 	}
	// }
	// else
	if (g_status == 0)
		exit(0);
	// if (cmd_list->exit_flag == 1)
	// {
	// 	result = ft_atoi(cmd_list->cmdline[1].cmd, &err_flag);
	// 	if (err_flag == 1)
	// 	{
	// 		cmd_list->err_manage.errcode = 4;
	// 		cmd_list->err_manage.errindex = 1;
	// 		print_errstr(cmd_list);
	// 		exit(-1);
	// 	}
	// 	exit(result % 256);
	//}
	return (1);
}
