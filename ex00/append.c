#include "rush02.h"

static void	ft_copy_text(char *dest, char *src, int *position)
{
	int	index;

	index = 0;
	while (src[index] != '\0')
	{
		dest[*position] = src[index];
		(*position)++;
		index++;
	}
}

int	ft_append_word(char **result, char *word)
{
	char	*next;
	int		old_size;
	int		position;

	old_size = 0;
	if (*result != NULL)
		old_size = ft_strlen(*result);
	next = malloc(old_size + (old_size > 0) + ft_strlen(word) + 1);
	if (next == NULL)
		return (1);
	position = 0;
	if (*result != NULL)
		ft_copy_text(next, *result, &position);
	if (old_size > 0)
		next[position++] = ' ';
	ft_copy_text(next, word, &position);
	next[position] = '\0';
	free(*result);
	*result = next;
	return (0);
}
