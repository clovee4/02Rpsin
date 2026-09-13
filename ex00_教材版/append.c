#include "rush02.h"

/* srcの文字をdestへコピーし、次に書く位置も進める */
static void	ft_copy_text(char *dest, char *src, int *position)
{
	int	index;

	index = 0;
	while (src[index] != '\0')
	{
		dest[*position] = src[index]; /* 指定された場所へ1文字コピー */
		(*position)++;
		index++;
	}
}

/* 現在の結果の後ろへ、空白を1つ挟んで単語を追加する */
int	ft_append_word(char **result, char *word)
{
	char	*next;
	int		old_size;
	int		position;

	old_size = 0;
	if (*result != NULL) /* 最初はNULLなので長さ0 */
		old_size = ft_strlen(*result);
	/* 古い文字列 + 必要なら空白 + 新語 + '\0' を確保 */
	next = malloc(old_size + (old_size > 0) + ft_strlen(word) + 1);
	if (next == NULL)
		return (1);
	position = 0;
	if (*result != NULL) /* すでにある答えを新しい領域へコピー */
		ft_copy_text(next, *result, &position);
	if (old_size > 0) /* 2語目以降だけ間に空白を入れる */
		next[position++] = ' ';
	ft_copy_text(next, word, &position);
	next[position] = '\0';
	free(*result); /* 古い狭い領域はもう不要 */
	*result = next; /* 呼び出し元のポインタを新しい領域へ更新 */
	return (0);
}
