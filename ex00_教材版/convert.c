#include "rush02.h"

int	ft_process_group(char *group, int size, char ***dict, char **result);

/* 渡された3桁以内が全部0かを調べる。000なら1を返す */
static int	ft_group_is_zero(char *group, int size)
{
	int	index;

	index = 0;
	while (index < size) /* グループ内を左から右へ見る */
	{
		if (group[index] != '0') /* 0以外が1つでもあれば空ではない */
			return (0);
		index++;
	}
	return (1);
}

/* 10のzeros乗を表す辞書キーを文字列として作る */
static char	*ft_make_scale_key(int zeros)
{
	char	*key;
	int		index;

	/* '1' + zeros個の'0' + '\0' の大きさ */
	key = malloc(zeros + 2);
	if (key == NULL)
		return (NULL);
	key[0] = '1'; /* 例：zerosが3なら、最初に"1"を置く */
	index = 1;
	while (index <= zeros)
		key[index++] = '0'; /* 後ろへ0を3個置いて"1000"にする */
	key[index] = '\0';
	return (key);
}

/* thousandやmillionなど、3桁グループの単位を追加する */
static int	ft_add_scale(int zeros, char ***dict, char **result)
{
	char	*key;
	char	*word;
	int		status;

	if (zeros == 0) /* 一番右のグループには単位がいらない */
		return (0);
	key = ft_make_scale_key(zeros); /* 例："1000000"を作る */
	if (key == NULL)
		return (1);
	word = ft_find_dict(dict, key); /* キーに対応するmillionを探す */
	free(key); /* 検索用キーはもう使わない */
	if (word == NULL)
		return (1);
	status = ft_append_word(result, word);
	return (status);
}

/* 数字全体を左から3桁ずつ処理する中心部分 */
static int	ft_convert_groups(char *number, char ***dict, char **result)
{
	int	length;
	int	position;
	int	group_size;
	length = ft_strlen(number); /* 全部で何桁あるか */
	group_size = length % 3; /* 一番左だけ1桁や2桁の場合がある */
	if (group_size == 0)
		group_size = 3;
	position = 0;
	while (position < length) /* 左のグループから順番に進む */
	{
		/* 000なら「zero thousand」のように表示せず丸ごと飛ばす */
		if (!ft_group_is_zero(number + position, group_size))
		{
			/* 今見ている1〜3桁を英単語へ変える */
			if (ft_process_group(number + position, group_size,
					dict, result))
				return (1);
			/* 右に残る桁数からthousandやmillionを決める */
			if (ft_add_scale(length - position - group_size, dict, result))
				return (1);
		}
		position += group_size; /* 次のグループ先頭へ移動 */
		group_size = 3;
	}
	return (0);
}

/* 外から呼ばれる変換関数。成功なら完成文字列、失敗ならNULL */
char	*ft_number_to_words(char *number, char ***dict)
{
	char	*result;
	char	*zero;

	/* 00042を42として扱う。ただし0を全部消さない */
	while (number[0] == '0' && number[1] != '\0')
		number++;
	result = NULL; /* append_wordが最初の領域を作る */
	if (number[0] == '0')
	{
		zero = ft_find_dict(dict, "0"); /* 0だけはグループ処理しない */
		if (zero == NULL || ft_append_word(&result, zero) != 0)
			return (free(result), NULL);
		return (result);
	}
	if (ft_convert_groups(number, dict, &result) != 0)
		return (free(result), NULL);
	return (result);
}
