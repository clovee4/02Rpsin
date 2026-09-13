#include "rush02.h"

/* コロンより左が「数字 + スペース」になっているか確認する */
static int	ft_key_end(char *line, int colon)
{
	int	end;
	int	index;

	end = colon;
	while (end > 0 && line[end - 1] == ' ') /* キー後ろの空白を除く */
		end--;
	if (end == 0)
		return (-1);
	index = 0;
	while (index < end) /* キー本体は数字だけ許可 */
	{
		if (line[index] < '0' || line[index] > '9')
			return (-1);
		index++;
	}
	while (index < colon)
		if (line[index++] != ' ')
			return (-1);
	return (end);
}

/* 値の末尾空白を除き、印字可能文字だけか確認する */
static int	ft_value_end(char *line, int start, int len)
{
	int	end;
	int	index;

	end = len;
	while (end > start && line[end - 1] == ' ') /* 末尾空白を削る */
		end--;
	index = start;
	while (index < end)
	{
		if (line[index] < 32 || line[index] > 126) /* 印字不能文字 */
			return (-1);
		index++;
	}
	if (end == start)
		return (-1);
	return (end);
}

/* 確定した範囲からKEYとVALUEをmallocして保存する */
static int	ft_save_entry(char *line, int key_end, int start, char **entry)
{
	int	end;

	end = ft_value_end(line, start, ft_strlen(line));
	if (end < 0)
		return (1);
	entry[KEY] = ft_copy_range(line, 0, key_end); /* 数字部分 */
	entry[VALUE] = ft_copy_range(line, start, end - start); /* 単語部分 */
	if (entry[KEY] == NULL || entry[VALUE] == NULL)
	{
		free(entry[KEY]);
		free(entry[VALUE]);
		return (1);
	}
	return (0);
}

/* 「42   :   forty two」をキーと値に分けて辞書へ保存する */
int	ft_parse_line(char *line, char ***dict, int index)
{
	int	colon;
	int	key_end;
	int	start;
	colon = 0;
	while (line[colon] && line[colon] != ':') /* 最初のコロンを探す */
		colon++;
	if (line[colon] != ':')
		return (1);
	key_end = ft_key_end(line, colon);
	start = colon + 1;
	while (line[start] == ' ') /* 値の前にある空白を飛ばす */
		start++;
	if (key_end < 0)
		return (1);
	/* KEYとVALUEの2本のcharポインタを置く場所 */
	dict[index] = malloc(sizeof(char *) * 2);
	if (dict[index] == NULL)
		return (1);
	dict[index][KEY] = NULL;
	dict[index][VALUE] = NULL;
	if (ft_save_entry(line, key_end, start, dict[index]) != 0)
		return (free(dict[index]), dict[index] = NULL, 1);
	return (0);
}
