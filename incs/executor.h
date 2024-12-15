#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "minishell.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

// The executor runs the pipeline of t_command
// Use pipes, fork, execve.
// handle builtins and redirections.
int execute_pipeline(t_minishell *shell, t_command *cmd);
int open_redirs(t_command *c);

#endif
