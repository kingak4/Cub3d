/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:00:11 by kikwasni          #+#    #+#             */
/*   Updated: 2025/05/13 09:48:48 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>
# include <limits.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 22
# endif

void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memset(void *str, int c, size_t n);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
char			*ft_strchr(const char *str, int c);
char			*ft_strdup(const char *s);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
size_t			ft_strlcat(char *dest, const char *src, size_t size);
unsigned int	ft_strlcpy(char *dest, const char *src, unsigned int size);
size_t			ft_strlen(const char *s);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strncmp(char *s1, char *s2, unsigned int n);
char			*ft_strrchr(const char *str, int c);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_atoi(const char *nptr);
void			*ft_memmove(void *dest, const void *src, size_t n);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_itoa(int n);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
int				ft_printf(const char *format, ...);
int				ft_putstr(char *str);
void			ft_putchar(char c);
int				ft_putnbr(int nb);
int				ft_putnbr_unsigned(unsigned int nb);
int				ft_print_upperx(unsigned int nb);
int				ft_printx(unsigned int n);
int				ft_print_pointer(void *p);
char			*read_buffer(int fd, char *rest, int bytes_read);
char			*get_next_line(int fd);
void			*ft_memcpy1(void *dest, void *src, size_t n);
int				ft_strlen1(char *s);
char			*add_to_rest(char *rest, char *buffer);
void			*ft_calloc1(size_t nmeb, size_t size);
char			*ft_strjoin1(char *s1, char *s2);
char			*ft_substr1(char *s, int start, int len);
char			*one_line(char *buffer);
char			*next_res(char *rest);

#endif