#include "rush02.h"

int	ft_parse_line(char *line, char ***dict, int index);

static int	ft_handle_line(char *line, char ***dict, int *index)
{
	int	status;

	if (line[0] == '\0')
		return (0);
	status = ft_parse_line(line, dict, *index);
	if (status != 0)
		return (1);
	(*index)++;
	return (0);
}

static int	ft_parse_lines(char *buffer, char ***dict,
		int *position, int *index)
{
	int	start;
	char	*line;

	*position = 0;
	start = 0;
	while (buffer[*position] != '\0')
	{
		if (buffer[*position] == '\n')
		{
			line = ft_copy_range(buffer, start, *position - start);
			if (line == NULL || ft_handle_line(line, dict, index))
				return (free(line), -1);
			free(line);
			start = *position + 1;
		}
		(*position)++;
	}
	return (start);
}

int	ft_parse_dict(char *buffer, char ***dict)
{
	int	position;
	int	start;
	int	index;
	char	*line;

	index = 0;
	start = ft_parse_lines(buffer, dict, &position, &index);
	if (start < 0)
		return (1);
	line = ft_copy_range(buffer, start, position - start);
	if (line == NULL || ft_handle_line(line, dict, &index))
		return (free(line), 1);
	free(line);
	dict[index] = NULL;
	return (0);
}
