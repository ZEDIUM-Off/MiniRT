/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 22:55:40 by agaley            #+#    #+#             */
/*   Updated: 2024/03/09 16:16:04 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	fts_count_words(const char *str, const char *charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && ft_strchr(charset, str[i]))
			i++;
		while (str[i] && !ft_strchr(charset, str[i]))
			i++;
		count++;
		while (str[i] && ft_strchr(charset, str[i]))
			i++;
	}
	return (count);
}

static char	*fts_strdup_word(const char *str, const char *charset, int start)
{
	int		i;
	char	*word;

	i = start;
	while (str[i] && !ft_strchr(charset, str[i]))
		i++;
	word = (char *)malloc((i + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (str[start] && !ft_strchr(charset, str[start]))
	{
		word[i] = str[start];
		start++;
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	*fts_free_tab(char **tab, size_t wn)
{
	size_t	i;

	i = 0;
	while (i < wn && tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

char	**fts_split(const char *str, const char *charset)
{
	int		i;
	int		wn;
	char	**tab;

	tab = (char **)malloc((fts_count_words(str, charset) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	wn = 0;
	while (str[i])
	{
		while (str[i] && ft_strchr(charset, str[i]))
			i++;
		tab[wn] = fts_strdup_word(str, charset, i);
		if (!tab[wn])
			return (fts_free_tab(tab, wn));
		while (str[i] && !ft_strchr(charset, str[i]))
			i++;
		wn++;
		while (str[i] && ft_strchr(charset, str[i]))
			i++;
	}
	tab[wn] = (void *)0;
	return (tab);
}
