#include "rush02.h"

static bool	ft_is_number(char *str)
{
	int	index;

	if (str[0] == '\0')
		return (false);
	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] < '0' || str[index] > '9')
			return (false);
		index++;
	}
	return (true);
}

bool	ft_get_input(int argc, char **argv, char **name, char **number)
{
	if (argc != 2 && argc != 3)
		return (false);
	if (argc == 2)
	{
		*name = "numbers.dict";
		*number = argv[1];
	}
	else
	{
		*name = argv[1];
		*number = argv[2];
	}
	return (ft_is_number(*number));
}
