#include "rush02.h"

int	ft_process_group(char *group, int size, char ***dict, char **result);

static int	ft_group_is_zero(char *group, int size)
{
	int	index;

	index = 0;
	while (index < size)
	{
		if (group[index] != '0')
			return (0);
		index++;
	}
	return (1);
}

static char	*ft_make_scale_key(int zeros)
{
	char	*key;
	int		index;

	key = malloc(zeros + 2);
	if (key == NULL)
		return (NULL);
	key[0] = '1';
	index = 1;
	while (index <= zeros)
		key[index++] = '0';
	key[index] = '\0';
	return (key);
}

static int	ft_add_scale(int zeros, char ***dict, char **result)
{
	char	*key;
	char	*word;
	int		status;

	if (zeros == 0)
		return (0);
	key = ft_make_scale_key(zeros);
	if (key == NULL)
		return (1);
	word = ft_find_dict(dict, key);
	free(key);
	if (word == NULL)
		return (1);
	status = ft_append_word(result, word);
	return (status);
}

static int	ft_convert_groups(char *number, char ***dict, char **result)
{
	int	length;
	int	position;
	int	group_size;
	length = ft_strlen(number);
	group_size = length % 3;
	if (group_size == 0)
		group_size = 3;
	position = 0;
	while (position < length)
	{
		if (!ft_group_is_zero(number + position, group_size))
		{
			if (ft_process_group(number + position, group_size,
					dict, result))
				return (1);
			if (ft_add_scale(length - position - group_size, dict, result))
				return (1);
		}
		position += group_size;
		group_size = 3;
	}
	return (0);
}

char	*ft_number_to_words(char *number, char ***dict)
{
	char	*result;
	char	*zero;

	while (number[0] == '0' && number[1] != '\0')
		number++;
	result = NULL;
	if (number[0] == '0')
	{
		zero = ft_find_dict(dict, "0");
		if (zero == NULL || ft_append_word(&result, zero) != 0)
			return (free(result), NULL);
		return (result);
	}
	if (ft_convert_groups(number, dict, &result) != 0)
		return (free(result), NULL);
	return (result);
}
