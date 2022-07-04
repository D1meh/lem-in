/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:08:23 by epfennig          #+#    #+#             */
/*   Updated: 2022/07/04 16:34:30 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int				get_next_line(int fd, char **line)
{
	ssize_t		ret;
	char		buff[BUFFER_SIZE + (ret = 1)];
	static char	*str = NULL;
	char		*temp;

	if (fd < 0 || fd >= 256 || !line || BUFFER_SIZE <= 0)
		return (-1);
	str == NULL ? str = ft_memalloc(1 * sizeof(char)) : NULL;
	while (!ft_strchr(str, '\n') && (ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		temp = ft_strjoin(str, buff);
		ft_strfree(&str);
		str = temp;
	}
	if (ret == 0)
		*line = ft_strdup(str);
	else if (ret > 0)
		*line = ft_substr(str, 0, (ft_strchr(str, '\n') - str));
	else
		return (-1);
	temp = ft_strdup(str + (ft_strlen(*line) + ((ret > 0) ? +1 : +0)));
	ft_strfree(&str);
	str = temp;
	return (ret == 0 ? 0 * ft_strfree(&str) : 1);
}
