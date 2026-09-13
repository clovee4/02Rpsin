#include "rush02.h"

static char	*ft_grow_buffer(char *old, int used, char *part, int size)
{
	char	*new;
	int		index;

	new = malloc(used + size + 1);
	if (new == NULL)
		return (NULL);
	index = -1;
	while (++index < used)
		new[index] = old[index];
	index = -1;
	while (++index < size)
		new[used + index] = part[index];
	new[used + size] = '\0';
	free(old);
	return (new);
}

static char	*ft_read_all(int fd)
{
	char	part[READ_SIZE];
	char	*buffer;
	char	*new;
	int		bytes;
	int		used;
	buffer = NULL;
	used = 0;
	bytes = read(fd, part, READ_SIZE);
	while (bytes > 0)
	{
		new = ft_grow_buffer(buffer, used, part, bytes);
		if (new == NULL)
			return (free(buffer), NULL);
		buffer = new;
		used += bytes;
		bytes = read(fd, part, READ_SIZE);
	}
	if (bytes < 0)
		return (free(buffer), NULL);
	if (buffer == NULL)
		buffer = ft_copy_range("", 0, 0);
	return (buffer);
}

static int	ft_count_lines(char *buffer)
{
	int	index;
	int	lines;

	index = 0;
	lines = 0;
	while (buffer[index] != '\0')
	{
		if (buffer[index] == '\n')
			lines++;
		index++;
	}
	if (index > 0 && buffer[index - 1] != '\n')
		lines++;
	return (lines);
}

int	ft_parse_dict(char *buffer, char ***dict);

static char	***ft_make_dict(char *buffer)
{
	char	***dict;
	int		lines;
	int		index;

	lines = ft_count_lines(buffer);
	dict = malloc(sizeof(char **) * (lines + 1));
	if (dict == NULL)
		return (NULL);
	index = 0;
	while (index <= lines)
		dict[index++] = NULL;
	if (ft_parse_dict(buffer, dict) != 0)
	{
		ft_free_dict(dict);
		return (NULL);
	}
	return (dict);
}

char	***ft_read_dict(char *path)
{
	char	*buffer;
	char	***dict;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	buffer = ft_read_all(fd);
	if (close(fd) < 0 || buffer == NULL)
		return (free(buffer), NULL);
	dict = ft_make_dict(buffer);
	free(buffer);
	if (dict == NULL)
		return (NULL);
	if (ft_validate_dict(dict) != 0)
	{
		ft_free_dict(dict);
		return (NULL);
	}
	return (dict);
}
