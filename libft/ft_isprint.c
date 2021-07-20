/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flurk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 09:46:43 by flurk             #+#    #+#             */
/*   Updated: 2020/11/24 15:26:59 by flurk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c > 255 || c < 0)
		return (0);
	if ((unsigned char)c >= 32 && (unsigned char)c <= 126)
		return (1);
	else
		return (0);
}