#include "rush02.h"

/* 文字列の先頭から'\0'までの文字数を数える */
int	ft_strlen(char *str)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
		index++;
	return (index);
}

/* 2つの文字列を左から比較し、同じなら0を返す */
int	ft_strcmp(char *left, char *right)
{
	int	index;

	index = 0;
	while (left[index] && left[index] == right[index]) /* 同じ間進む */
		index++;
	return ((unsigned char)left[index] - (unsigned char)right[index]);
}

/* 文字列全体を標準出力へ一度に書く */
void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

/* 指定メッセージを標準エラーへ書き、終了コード1を返す */
int	ft_error(char *message)
{
	write(2, message, ft_strlen(message));
	return (1);
}

/* strのstart番目からsize文字だけ、新しい領域へコピーする */
char	*ft_copy_range(char *str, int start, int size)
{
	char	*copy;
	int		index;

	copy = malloc(size + 1); /* コピーする文字 + '\0' */
	if (copy == NULL)
		return (NULL);
	index = 0;
	while (index < size)
	{
		copy[index] = str[start + index]; /* 必要な範囲だけコピー */
		index++;
	}
	copy[index] = '\0'; /* Cの文字列として終わらせる */
	return (copy);
}
