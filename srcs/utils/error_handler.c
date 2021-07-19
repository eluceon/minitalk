#include "utils.h"

int	error_message(char *description)
{
	ft_putstr_fd(RED_COLOR, STDERR_FILENO);
	ft_putstr_fd("[!] minitalk: ", STDERR_FILENO);
	ft_putstr_fd(NONE_COLOR, STDERR_FILENO);
	ft_putendl_fd(description, STDERR_FILENO);
	return (1);
}
