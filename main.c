#include <unistd.h>
#include <stdbool.h>

void	ft_process_group(char *nb, int pos, int size)
{
	write(1, &nb[pos], size);
	write(1, "\n", 1);
	// ft_find_dict(?)
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

void	ft_split_number(char *nb)
{
	int	len;
	int	first;
	int	pos;

	pos = 0;
	len = ft_strlen(nb);
	first = len % 3;
	if (first == 0)
		first = 3;
	ft_process_group(nb, pos, first);
	pos += first;
	while (pos < len)
	{
		ft_process_group(nb, pos, 3);
		pos += 3;
	}
}

bool	ft_is_nbr(char *str)
{
	int	i;

	if (str[0] == '\0')
		return (false);
	i = 0;
	while (str[i] != '\0')
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return (false);
		i++;
	}
	return (true);
}

int	main(int argc, char *argv[])
{
	char	*number;

	if (!(argc == 2 || argc == 3))
		return (1);
	if (argc == 2)
		number = argv[1];
	else
		number = argv[2];
	if (ft_is_nbr(number) == false)
		return (1);
	ft_split_number(number);
	return (0);
}
