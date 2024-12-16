#include "minishell.h"

int	builtin_env(t_minishell *shell)
{
	env_print(shell->envp);
	return (0);
}
