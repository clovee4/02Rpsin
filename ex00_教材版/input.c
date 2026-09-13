#include "rush02.h"

/* 文字列が空でなく、全部'0'〜'9'ならtrueを返す */
static bool	ft_is_number(char *str)
{
	int	index;

	if (str[0] == '\0') /* 空文字列は数値ではない */
		return (false);
	index = 0;
	while (str[index] != '\0') /* 末尾のヌル文字まで1文字ずつ見る */
	{
		if (str[index] < '0' || str[index] > '9') /* 数字以外を発見 */
			return (false);
		index++;
	}
	return (true);
}

/* 引数から「辞書名」と「変換する数」を選ぶ */
bool	ft_get_input(int argc, char **argv, char **name, char **number)
{
	if (argc != 2 && argc != 3) /* 実行名込みで2個か3個だけ許す */
		return (false);
	if (argc == 2)
	{
		*name = "numbers.dict"; /* 辞書指定なしなら標準辞書 */
		*number = argv[1];
	}
	else
	{
		*name = argv[1]; /* 1個目が辞書、2個目が数字 */
		*number = argv[2];
	}
	return (ft_is_number(*number)); /* 最後に数字として正しいか確認 */
}
