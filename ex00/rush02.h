#ifndef RUSH02_H
# define RUSH02_H

# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

# define KEY 0
# define VALUE 1
# define READ_SIZE 1024

int		ft_strlen(char *str);
int		ft_error(char *message);
int		ft_strcmp(char *left, char *right);
void	ft_putstr(char *str);
char	*ft_copy_range(char *str, int start, int size);
bool	ft_get_input(int argc, char **argv, char **name, char **number);
char	***ft_read_dict(char *path);
char	*ft_find_dict(char ***dict, char *key);
int		ft_validate_dict(char ***dict);
void	ft_free_dict(char ***dict);
int		ft_append_word(char **result, char *word);
char	*ft_number_to_words(char *number, char ***dict);

#endif
