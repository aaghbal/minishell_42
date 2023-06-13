#include "minishell.h"

void	doc_handler(int signal)
{
	if (signal == 3)
		return ;
	else if (signal == 2 || signal == 11)
		exit (0);
}
