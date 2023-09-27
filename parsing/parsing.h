#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct	s_pars {
	char	*n_texture;
	char	*s_texture;
	char	*e_texture;
	char	*w_texture;
	int		f_colors[3];
	int		c_colors[3];
	char	**map;
}				t_pars;

char	*get_next_line(int fd);
char	**ft_split(char const *s, char c);
int		ft_atoi(const char *nptr);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memset(void *s, int c, size_t n);