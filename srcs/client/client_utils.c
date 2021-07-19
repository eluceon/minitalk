#include "client.h"

int	is_wrong_arg(int argc, char *argv[])
{
	int	i;

	i = -1;
	if (argc != 3)
		return (error_message("./client [server-pid] [message]"));
	while (argv[1][++i])
	{
		if (!ft_isdigit(argv[1][i]))
			return (error_message("First argument is not a number"));
	}
	return (0);
}
