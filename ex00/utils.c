#include "rush02.h"

int	ft_strlen(char *str)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
		index++;
	return (index);
}

int	ft_strcmp(char *left, char *right)
{
	int	index;

	index = 0;
	while (left[index] && left[index] == right[index])
		index++;
	return ((unsigned char)left[index] - (unsigned char)right[index]);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

int	ft_error(char *message)
{
	write(2, message, ft_strlen(message));
	return (1);
}

char	*ft_copy_range(char *str, int start, int size)
{
	char	*copy;
	int		index;

	copy = malloc(size + 1);
	if (copy == NULL)
		return (NULL);
	index = 0;
	while (index < size)
	{
		copy[index] = str[start + index];
		index++;
	}
	copy[index] = '\0';
	return (copy);
}
