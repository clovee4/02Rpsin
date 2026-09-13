#include "rush02.h"

/* keyと同じ文字列を持つ辞書項目を、上から順に探す */
char	*ft_find_dict(char ***dict, char *key)
{
	int	index;

	index = 0;
	while (dict[index] != NULL) /* 辞書末尾のNULLまで繰り返す */
	{
		if (ft_strcmp(dict[index][KEY], key) == 0) /* 内容が完全一致 */
			return (dict[index][VALUE]);
		index++;
	}
	return (NULL);
}

/* 辞書作成時にmallocした領域を、内側から順番に解放する */
void	ft_free_dict(char ***dict)
{
	int	index;

	if (dict == NULL)
		return ;
	index = 0;
	while (dict[index] != NULL)
	{
		free(dict[index][KEY]); /* キー文字列 */
		free(dict[index][VALUE]); /* 値の文字列 */
		free(dict[index]); /* KEYとVALUEを持っていた配列 */
		index++;
	}
	free(dict); /* 最後に辞書全体の外側を解放 */
}

/* 0〜19、20〜90、100が辞書にあるかを確認する */
static int	ft_has_small_keys(char ***dict)
{
	char	key[4];
	int		number;
	number = 0;
	while (number <= 100)
	{
		key[0] = '0' + number / 100;
		key[1] = '0' + number / 10 % 10;
		key[2] = '0' + number % 10;
		key[3] = '\0';
		if (number < 10 && ft_find_dict(dict, key + 2) == NULL)
			return (1);
		if (number >= 10 && number < 20
			&& ft_find_dict(dict, key + 1) == NULL)
			return (1);
		if (number >= 20 && number < 100 && number % 10 == 0
			&& ft_find_dict(dict, key + 1) == NULL)
			return (1);
		if (number == 100 && ft_find_dict(dict, key) == NULL)
			return (1);
		number++;
	}
	return (0);
}

/* thousandからundecillionまでの必須キーを確認する */
int	ft_validate_dict(char ***dict)
{
	char	key[39];
	int		zeros;
	int		index;

	if (ft_has_small_keys(dict) != 0)
		return (1);
	zeros = 3;
	while (zeros <= 36)
	{
		key[0] = '1';
		index = 1;
		while (index <= zeros)
			key[index++] = '0';
		key[index] = '\0';
		if (ft_find_dict(dict, key) == NULL)
			return (1);
		zeros += 3;
	}
	return (0);
}
