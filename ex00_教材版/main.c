#include "rush02.h"

/*
** プログラムの入口。
** 1. 引数を確認する
** 2. 辞書を読む
** 3. 数字を英単語へ変える
** 4. 表示して、mallocしたメモリを片付ける
*/
int	main(int argc, char **argv)
{
	char	*dict_name;
	char	*number;
	char	*words;
	char	***dict;

	/* 引数の個数と、numberが数字だけかを確認する */
	if (ft_get_input(argc, argv, &dict_name, &number) == false)
		return (ft_error("Error\n"));
	/* 辞書ファイルを読み、使いやすい三重ポインタへ変換する */
	dict = ft_read_dict(dict_name);
	if (dict == NULL)
		return (ft_error("Dict Error\n"));
	/* 数字の文字列と辞書から、完成した英単語を作る */
	words = ft_number_to_words(number, dict);
	if (words == NULL)
	{
		/* 変換失敗でも、先に作った辞書は忘れず解放する */
		ft_free_dict(dict);
		return (ft_error("Dict Error\n"));
	}
	/* 変換が全部成功したので、ここで初めて答えを表示する */
	ft_putstr(words);
	write(1, "\n", 1);
	/* mallocで作ったwordsとdictを両方片付ける */
	free(words);
	ft_free_dict(dict);
	return (0);
}
