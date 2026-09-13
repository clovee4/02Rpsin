#include "rush02.h"

static int	ft_add_key(char **result, char ***dict, int number)
{
	char	key[4];
	char	*word;
	int		start;

	key[0] = '0' + number / 100;
	key[1] = '0' + number / 10 % 10;
	key[2] = '0' + number % 10;
	key[3] = '\0';
	start = 0;
	while (key[start] == '0' && key[start + 1] != '\0')
		start++;
	word = ft_find_dict(dict, key + start);
	if (word == NULL)
		return (1);
	return (ft_append_word(result, word));
}

static int	ft_group_value(char *group, int size)
{
	int	value;
	int	index;

	value = 0;
	index = 0;
	while (index < size)
	{
		value = value * 10 + group[index] - '0';
		index++;
	}
	return (value);
}

int	ft_process_group(char *group, int size, char ***dict, char **result)
{
	int	value;

	value = ft_group_value(group, size);
	if (value >= 100)
	{
		if (ft_add_key(result, dict, value / 100)
			|| ft_add_key(result, dict, 100))
			return (1);
		value %= 100;
	}
	if (value >= 20)
	{
		if (ft_add_key(result, dict, value / 10 * 10))
			return (1);
		value %= 10;
	}
	if (value > 0 && ft_add_key(result, dict, value))
		return (1);
	return (0);
}
