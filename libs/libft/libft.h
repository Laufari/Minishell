/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 22:29:17 by laufarin          #+#    #+#             */
/*   Updated: 2025/03/31 14:21:15 by laufarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif
# define BASE_MAYUS "0123456789ABCDEF"
# define BASE_MIN "0123456789abcdef"

//Libft

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2); 
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(char *s1);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
//char    *ft_strjoin3(const char *s1, const char *s2, const char *s3);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
//t_list	*ft_lstnew(void *content);
//void	ft_lstadd_front(t_list **lst, t_list *new);
//t_list	*ft_lstlast(t_list *lst);
//void	ft_lstadd_back(t_list **lst, t_list *new);
//void	ft_lstdelone(t_list *lst, void (*del)(void*));
//void	ft_lstclear(t_list **lst, void (*del)(void*));
//void	ft_lstiter(t_list *lst, void (*f)(void *));
//t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
char	**ft_realloc(char **str, char *s1);

//GET_NEXT_LINE

char	*update_storage(char *storage);
char	*extract_line(char *storage);
char	*fill_storage(int fd, char *storage);
char	*get_next_line(int fd);
char	*gnl_strjoin(char *s1, char *s2);
char	*ft_strjoin_gn(char *s1, char *s2);

//FT_PRINTF

int		ft_printf(const char *s, ...);
int		ft_printf_strings(char *s);
//int		ft_printf_prcnt(char c);
int		ft_printf_numbers(int num);
int		ft_unsigned(unsigned int n);
int		ft_printf_hexa(unsigned int nb);
int		ft_printf_hexamin(unsigned int nb);
int		ft_printf_char(char c);
int		ft_printf_pointer(unsigned long nb);

#endif
