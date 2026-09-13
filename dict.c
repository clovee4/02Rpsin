#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define KEY 0
#define VALUE 1

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

int	ft_count_lines(char *buffer)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			count++;
		i++;
	}
	if (i > 0 && buffer[i - 1] != '\n')
		count++;
	return (count);
}

int	ft_parse_line(char *str, int len, char ***dict, int index)
{
	int	colon;

	colon = 0;
	while (colon < len && str[colon] != ':')
		colon++;
	if (colon == len)
		return (1);
	dict[index] = malloc(sizeof(char *) * 2);
	if (dict[index] == NULL)
		return (1);
	dict[index][KEY] = malloc(colon + 1);
	dict[index][VALUE] = malloc(len - colon);
	if (dict[index][KEY] == NULL || dict[index][VALUE] == NULL)
		return (1);
	ft_strncpy(dict[index][KEY], str, colon);
	dict[index][KEY][colon] = '\0';
	ft_strncpy(dict[index][VALUE],
		&str[colon + 1], len - colon - 1);
	dict[index][VALUE][len - colon - 1] = '\0';
	return (0);
}

int	ft_parse_dict(char *buffer, char ***dict)
{
	int	i;
	int	start;
	int	index;

	i = 0;
	start = 0;
	index = 0;
	while (1)
	{
		if (buffer[i] == '\n' || buffer[i] == '\0')
		{
			if (i > start
				&& ft_parse_line(&buffer[start],
					i - start, dict, index) != 0)
				return (1);
			if (i > start)
				index++;
			if (buffer[i] == '\0')
				break ;
			start = i + 1;
		}
		i++;
	}
	dict[index] = NULL;
	return (0);
}

int	***ft_read_dict(void)
{
	int		fd;
	int		bytes;
	int		lines;
	char	buffer[1000];
	char	***dict;

	fd = open("numbers.dict", O_RDONLY);
	if (fd < 0)
		return (NULL);
	bytes = read(fd, buffer, 999);
	close(fd);
	if (bytes < 0)
		return (NULL);
	buffer[bytes] = '\0';
	lines = ft_count_lines(buffer);
	dict = malloc(sizeof(char **) * (lines + 1));
	if (dict == NULL)
		return (NULL);
	if (ft_parse_dict(buffer, dict) != 0)
		return (NULL);
	return (dict);
}
