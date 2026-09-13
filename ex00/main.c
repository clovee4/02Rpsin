#include "rush02.h"

int	main(int argc, char **argv)
{
	char	*dict_name;
	char	*number;
	char	*words;
	char	***dict;

	if (ft_get_input(argc, argv, &dict_name, &number) == false)
		return (ft_error("Error\n"));
	dict = ft_read_dict(dict_name);
	if (dict == NULL)
		return (ft_error("Dict Error\n"));
	words = ft_number_to_words(number, dict);
	if (words == NULL)
	{
		ft_free_dict(dict);
		return (ft_error("Dict Error\n"));
	}
	ft_putstr(words);
	write(1, "\n", 1);
	free(words);
	ft_free_dict(dict);
	return (0);
}
