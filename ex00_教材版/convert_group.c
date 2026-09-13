#include "rush02.h"

/* 数字を最大3文字の辞書キーへ変え、対応する単語を追加する */
static int	ft_add_key(char **result, char ***dict, int number)
{
	char	key[4];
	char	*word;
	int		start;

	key[0] = '0' + number / 100; /* 百の位を文字にする */
	key[1] = '0' + number / 10 % 10; /* 十の位 */
	key[2] = '0' + number % 10; /* 一の位 */
	key[3] = '\0';
	start = 0;
	/* "042"を"42"、"007"を"7"として検索する */
	while (key[start] == '0' && key[start + 1] != '\0')
		start++;
	word = ft_find_dict(dict, key + start); /* 辞書から英単語を探す */
	if (word == NULL)
		return (1);
	return (ft_append_word(result, word));
}

/* "342"という文字列を整数342へ変える。最大3桁だけなので安全 */
static int	ft_group_value(char *group, int size)
{
	int	value;
	int	index;

	value = 0;
	index = 0;
	while (index < size)
	{
		/* 今までの数字を左へずらし、新しい1桁を右へ足す */
		value = value * 10 + group[index] - '0';
		index++;
	}
	return (value);
}

/* 0〜999を「百・十・一」の辞書キーへ分解する */
int	ft_process_group(char *group, int size, char ***dict, char **result)
{
	int	value;

	value = ft_group_value(group, size); /* 文字列を計算しやすいintへ */
	if (value >= 100) /* 342なら、まず3と100を追加 */
	{
		if (ft_add_key(result, dict, value / 100)
			|| ft_add_key(result, dict, 100))
			return (1);
		value %= 100; /* 処理済みの百の位を捨て、42を残す */
	}
	if (value >= 20) /* 42なら40を追加する */
	{
		if (ft_add_key(result, dict, value / 10 * 10))
			return (1);
		value %= 10; /* 十の位を捨て、2を残す */
	}
	/* 1〜19、または最後に残った一の位を追加する */
	if (value > 0 && ft_add_key(result, dict, value))
		return (1);
	return (0);
}
