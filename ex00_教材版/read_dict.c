#include "rush02.h"

/* 読込済みbufferの後ろへ、新しく読んだpartをつなげる */
static char	*ft_grow_buffer(char *old, int used, char *part, int size)
{
	char	*new;
	int		index;

	new = malloc(used + size + 1); /* 全データと終端文字の場所 */
	if (new == NULL)
		return (NULL);
	index = -1;
	while (++index < used) /* これまで読んだ内容をコピー */
		new[index] = old[index];
	index = -1;
	while (++index < size) /* 今回readした内容を後ろへコピー */
		new[used + index] = part[index];
	new[used + size] = '\0';
	free(old); /* 古い小さなbufferを片付ける */
	return (new);
}

/* readを繰り返し、ファイル末尾までを1本の文字列にする */
static char	*ft_read_all(int fd)
{
	char	part[READ_SIZE];
	char	*buffer;
	char	*new;
	int		bytes;
	int		used;
	buffer = NULL;
	used = 0;
	bytes = read(fd, part, READ_SIZE); /* 最大1024バイト読む */
	while (bytes > 0) /* 0になったらファイル末尾 */
	{
		new = ft_grow_buffer(buffer, used, part, bytes); /* 後ろへ追加 */
		if (new == NULL)
			return (free(buffer), NULL);
		buffer = new;
		used += bytes; /* 現在保存済みの合計バイト数 */
		bytes = read(fd, part, READ_SIZE);
	}
	if (bytes < 0)
		return (free(buffer), NULL);
	if (buffer == NULL)
		buffer = ft_copy_range("", 0, 0);
	return (buffer);
}

/* 辞書保存用配列を確保するため、行数を数える */
static int	ft_count_lines(char *buffer)
{
	int	index;
	int	lines;

	index = 0;
	lines = 0;
	while (buffer[index] != '\0')
	{
		if (buffer[index] == '\n')
			lines++;
		index++;
	}
	if (index > 0 && buffer[index - 1] != '\n')
		lines++;
	return (lines);
}

int	ft_parse_dict(char *buffer, char ***dict);

/* 行数分の辞書を確保し、すべてNULLで安全に初期化する */
static char	***ft_make_dict(char *buffer)
{
	char	***dict;
	int		lines;
	int		index;

	lines = ft_count_lines(buffer);
	/* 各行へのポインタ + 辞書末尾を示すNULL */
	dict = malloc(sizeof(char **) * (lines + 1));
	if (dict == NULL)
		return (NULL);
	index = 0;
	while (index <= lines) /* 途中失敗でも安全にfreeできるようにする */
		dict[index++] = NULL;
	if (ft_parse_dict(buffer, dict) != 0)
	{
		ft_free_dict(dict);
		return (NULL);
	}
	return (dict);
}

/* パスを開き、読込・解析・必須キー確認まで行う */
char	***ft_read_dict(char *path)
{
	char	*buffer;
	char	***dict;
	int		fd;

	fd = open(path, O_RDONLY); /* 読み取り専用で辞書を開く */
	if (fd < 0)
		return (NULL);
	buffer = ft_read_all(fd); /* 辞書全体を文字列として読む */
	if (close(fd) < 0 || buffer == NULL)
		return (free(buffer), NULL);
	dict = ft_make_dict(buffer); /* 文字列を検索できる辞書へ変換 */
	free(buffer);
	if (dict == NULL)
		return (NULL);
	if (ft_validate_dict(dict) != 0) /* 必須キー不足なら不正辞書 */
	{
		ft_free_dict(dict);
		return (NULL);
	}
	return (dict);
}
