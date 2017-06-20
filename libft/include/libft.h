/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 16:13:23 by pribault          #+#    #+#             */
/*   Updated: 2017/06/17 16:12:50 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/*
** includes
*/

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>

/*
** macros
*/

# define BUFF_SIZE 4096
# define SIZE 4096

/*
** structures
*/

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

/*
** prototypes
*/

double				ft_atof(char *str);
int					ft_atoi(char *str);
unsigned int		ft_atou(char *str);
void				ft_bzero(void *s, size_t n);
char				ft_get_all_lines(int fd, char **str);
int					ft_get_next_line(int const fd, char **line);
char				*ft_itoa(int n);
int					ft_tolower(int c);
int					ft_toupper(int c);

/*
**	write functions
*/

void				ft_putchar(char c);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putstr(char const *s);
void				ft_showtab(char **tab);

void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char const *s, int fd);

/*
**	test functions
*/

int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
char				ft_isof(int c, char *str);
int					ft_isprime(int n);
int					ft_isprint(int c);

/*
**	maths functions
*/

size_t				ft_factorial(size_t n);
long				ft_power(long n, size_t power);
int					ft_sqrt(int n);

/*
**	mem functions
*/

void				*ft_memalloc(size_t size);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_memdel(void **ap);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);

/*
**	array functions
*/

void				**ft_alloc_array(size_t h, size_t w, size_t size);
int					ft_arraylen(char **array);
void				ft_free_array(void **array, size_t len);

/*
**	list functions
*/

void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstdel(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstswap(t_list **lst1, t_list **lst2);

/*
**	string functions
*/

char				**ft_multisplit(char *str, char *sep);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strchr(const char *s, int c);
void				ft_strclr(char *s);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dst, const char *src);
void				ft_strdel(char **as);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
void				ft_strdel(char **as);
char				*ft_strdup(const char *s1);
int					ft_strequ(char const *s1, char const *s2);
void				ft_striter(char *s, void (*f)(char*));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strncat(char *s1, const char *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strndup(const char *str, size_t n);
char				*ft_strnew(size_t size);
char				*ft_strnstr(const char *big, const char *little, size_t l);
char				*ft_strrchr(const char *s, int c);
char				**ft_strsplit(char const *s, char c);
char				*ft_strstr(const char *big, const char *little);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s);

#endif
