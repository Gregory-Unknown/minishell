#include "../minishell.h"

int	ft_status(t_struct *env)
{
	if (env->status)
		return (g_status % 256);
	return (g_status);
}
