#include "rush02.h"

static int	ft_key_end(char *line, int colon)
{
	int	end;
	int	index;

	end = colon;
	while (end > 0 && line[end - 1] == ' ')
		end--;
	if (end == 0)
		return (-1);
	index = 0;
	while (index < end)
	{
		if (line[index] < '0' || line[index] > '9')
			return (-1);
		index++;
	}
	while (index < colon)
		if (line[index++] != ' ')
			return (-1);
	return (end);
}

static int	ft_value_end(char *line, int start, int len)
{
	int	end;
	int	index;

	end = len;
	while (end > start && line[end - 1] == ' ')
		end--;
	index = start;
	while (index < end)
	{
		if (line[index] < 32 || line[index] > 126)
			return (-1);
		index++;
	}
	if (end == start)
		return (-1);
	return (end);
}

static int	ft_save_entry(char *line, int key_end, int start, char **entry)
{
	int	end;

	end = ft_value_end(line, start, ft_strlen(line));
	if (end < 0)
		return (1);
	entry[KEY] = ft_copy_range(line, 0, key_end);
	entry[VALUE] = ft_copy_range(line, start, end - start);
	if (entry[KEY] == NULL || entry[VALUE] == NULL)
	{
		free(entry[KEY]);
		free(entry[VALUE]);
		return (1);
	}
	return (0);
}

int	ft_parse_line(char *line, char ***dict, int index)
{
	int	colon;
	int	key_end;
	int	start;
	colon = 0;
	while (line[colon] && line[colon] != ':')
		colon++;
	if (line[colon] != ':')
		return (1);
	key_end = ft_key_end(line, colon);
	start = colon + 1;
	while (line[start] == ' ')
		start++;
	if (key_end < 0)
		return (1);
	dict[index] = malloc(sizeof(char *) * 2);
	if (dict[index] == NULL)
		return (1);
	dict[index][KEY] = NULL;
	dict[index][VALUE] = NULL;
	if (ft_save_entry(line, key_end, start, dict[index]) != 0)
		return (free(dict[index]), dict[index] = NULL, 1);
	return (0);
}
