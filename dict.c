#include <fcntl.h>
#include <unistd.h>

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

int	ft_parse_line(char *str, int len)
{
	int		colon;
	char	key[1000];
	char	value[1000];

	colon = 0;
	while (colon < len && str[colon] != ':')
		colon++;
	if (colon == len)
		return (1);
	ft_strncpy(key, str, colon);
	key[colon] = '\0';
	ft_strncpy(value, &str[colon + 1], len - (colon + 1));
	value[len - (colon + 1)] = '\0';
	return (0);
}

int	ft_parse_dict(char *buffer)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
		{
			if (ft_parse_line(&buffer[start], i - start) != 0)
				return (1);
			start = i + 1;
		}
		i++;
	}
	if (i > start)
	{
		if (ft_parse_line(&buffer[start], i - start) != 0)
			return (1);
	}
	return (0);
}

int	ft_read_dict(void)
{
	int		fd;
	int		bytes;
	char	buffer[1000];

	fd = open("numbers.dict", O_RDONLY);
	if (fd < 0)
		return (1);
	bytes = read(fd, buffer, 999);
	if (bytes < 0)
		return (1);
	buffer[bytes] = '\0';
	ft_parse_dict(buffer);
	close(fd);
	return (0);
}
