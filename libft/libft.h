/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:13:55 by psaulnie          #+#    #+#             */
/*   Updated: 2021/12/21 14:34:39 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void			ft_lstadd_front(t_list **alst, t_list *new);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
int				ft_lstsize(t_list *lst);
t_list			*ft_lstnew(void *content);
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));

void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
void			ft_bzero(void *pointer, size_t size);

void			*ft_memset(void *pointer, int value, size_t count);
void			*ft_memcpy(void *dest, const void *src, size_t size);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memchr(const void *memoryBlock, int searchedChar,
					size_t size);

void			*ft_calloc(size_t elementCount, size_t elementsize);

char			*ft_itoa(int n);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strdup(const char *source);
char			*ft_strchr(const char *str, int c);
char			*ft_strrchr(const char *str, int c);
char			*ft_strnstr(const char *str, char const *needle, size_t n);

char			**ft_split(char const *s, char c);

size_t			ft_strlen(const char *str);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
size_t			ft_strlcat(char *dest, const char *src, size_t size);

int				ft_strncmp(const char *first, const char *second,
					size_t length);
int				ft_atoi(const char *str);
int				ft_isalnum(int character);
int				ft_isalpha(int character);
int				ft_isascii(int character);
int				ft_isdigit(int character);
int				ft_isprint(int character);
int				ft_toupper(int character);
int				ft_tolower(int character);
int				ft_memcmp(const void *first, const void *second, size_t length);

/*	Get Next Line	*/

char			*get_next_line(int fd);
char			*gnl_strjoin(char *s1, char const *s2);
char			*gnl_strndup(const char *src, char c);
size_t			gnl_strlen(const char *str);
char			*gnl_strchr(const char *str);
char			*gnl_substr(char const *s, unsigned int start, int *len);

#endif