#include "rush02.h"

int	ft_parse_line(char *line, char ***dict, int index);

/* 切り出した1行を解析し、成功した辞書項目数を増やす */
static int	ft_handle_line(char *line, char ***dict, int *index)
{
	int	status;

	if (line[0] == '\0') /* 完全な空行は無視してよい */
		return (0);
	status = ft_parse_line(line, dict, *index);
	if (status != 0)
		return (1);
	(*index)++;
	return (0);
}

/* buffer内の改行を探し、1行ずつ切り出して解析する */
static int	ft_parse_lines(char *buffer, char ***dict,
		int *position, int *index)
{
	int	start;
	char	*line;

	*position = 0;
	start = 0;
	while (buffer[*position] != '\0') /* ファイル末尾まで進む */
	{
		if (buffer[*position] == '\n') /* 1行の終わりを発見 */
		{
			/* 改行を含めず、現在の1行だけをコピーする */
			line = ft_copy_range(buffer, start, *position - start);
			if (line == NULL || ft_handle_line(line, dict, index))
				return (free(line), -1);
			free(line);
			start = *position + 1;
		}
		(*position)++;
	}
	return (start);
}

/* 改行で終わらない最後の行も含め、辞書全体を解析する */
int	ft_parse_dict(char *buffer, char ***dict)
{
	int	position;
	int	start;
	int	index;
	char	*line;

	index = 0;
	start = ft_parse_lines(buffer, dict, &position, &index); /* 改行まで */
	if (start < 0)
		return (1);
	/* 最後に改行がない場合、残った最後の1行を処理する */
	line = ft_copy_range(buffer, start, position - start);
	if (line == NULL || ft_handle_line(line, dict, &index))
		return (free(line), 1);
	free(line);
	dict[index] = NULL; /* 辞書の終わりを示す目印 */
	return (0);
}
