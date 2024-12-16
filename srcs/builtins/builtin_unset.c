#include "minishell.h"

int	builtin_unset(t_minishell *shell, char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		env_remove_key(&shell->envp, argv[i]);
		i++;
	}
	return (0);
}
