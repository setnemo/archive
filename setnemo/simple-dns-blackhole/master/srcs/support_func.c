

#include "support_func.h"

// выводим ошибку ерно и завершаем выполнение программы
void 		error(char *err)
{
	perror(err);
	exit(1);
}

//аналог strstr() - только для пакета запроса. Ищем совпадение
static int	dns_memcmp(unsigned char *s1, char *s2, int len1, int len2)
{
	int i;

	i = 0;
	while (i < len1)
	{
		if (s1[i] == *s2)
		{
			if (memcmp(&s1[i], s2, len2) == 0)
				return (1);
		}
		i++;
	}
	return (0);
}

//сравниваем запрос со своим черным списком
int			check_blacklist(unsigned char *buffer, t_db *db, int buflen)
{
	int a;

	a = 0;
	while (db->blacklist[a])
	{
		// в запросе, который сохранен в буфер - адрес сайта начинается с 13 байта		
		if (dns_memcmp(buffer, db->blacklist[a], buflen, strlen(db->blacklist[a])))
			return (1);
		a++;
	}
	return (0);
}

//заменяем точки на количество байт после точки, чтобы во время проверка сравнивать через memcmp
void		replace_dot(t_db *db)
{
	int		a;
	int		b;
	int		temp;
	char	*point;

	a = 0;
	// цикл, пока есть строка в массиве
	while (db->blacklist[a])
	{
		b = 0;
		//идем по строке
		while (db->blacklist[a][b])
		{
			//если точка '.', то сохраняем поинтер на это место и считаем сколько
			//чаров после точки, чтобы сохранить количество вместо точки (для сравнения с пакетом в запросе)
			if (db->blacklist[a][b] == '.')
				{
					temp = b;
					point = &db->blacklist[a][b];
					b++;
					while (isalnum(db->blacklist[a][b]))
						b++;
					*point = b - temp - 1;
					b--;
				}
			b++;
		}
		a++;
	}
}

//занулить строку
void		ft_strclr(char *s)
{
	while (s != NULL && *s)
		*s++ = '\0';
}

//сконкатенировать и замолочить строку, вернуть указатель на нее
char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	i;

	i = 0;
	if (s1 != NULL && s2 != NULL)
	{
		new = (char*)malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
		if (new == NULL)
			return (NULL);
		if (strlen(s1) + strlen(s2) + 1 != 1)
		{
			while (*s1)
				new[i++] = *(s1)++;
			while (*s2)
				new[i++] = *(s2)++;
		}
		new[i] = '\0';
		return (new);
	}
	return (NULL);
}

//замолочить новую строку по длины size + нуль-терминатор и вернуть указатель на нее 
char		*ft_strnew(size_t size)
{
	char	*new;
	size_t	i;

	new = (char*)malloc(sizeof(char) * (size + 1));
	if (new)
	{
		i = 0;
		while (size + 1 > i)
		{
			new[i] = '\0';
			i++;
		}
		return (new);
	}
	return (NULL);
}

//замолочить новую строку из строки с индекса start длиной len + '\0' и вернуть указатель
char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*new;

	i = 0;
	new = (char*)malloc(sizeof(char) * (len + 1));
	if (!new || !s)
		return (NULL);
	while (len > 0)
	{
		new[i] = s[start];
		i++;
		start++;
		len--;
	}
	new[i] = '\0';
	return (new);
}

//доп функция для **ft_strsplit(char const *s, char c)
static	size_t	ft_strsplit_count_word(char *s, char c)
{
	size_t	count;

	count = 0;
	while (s && *s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

//доп функция для **ft_strsplit(char const *s, char c)
static	size_t	ft_strsplit_count_len(char *s, char c)
{
	size_t countc;

	countc = 0;
	while (*s && *s != c)
	{
		countc++;
		s++;
	}
	return (countc);
}

//принимает строку и создает массив строк по делиметру char c
char			**ft_strsplit(char const *s, char c)
{
	char	**new;
	size_t	countc;
	size_t	count;
	size_t	a;

	countc = 0;
	a = 0;
	if (!s)
		return (NULL);
	count = ft_strsplit_count_word((char*)s, c);
	if (!(new = (char**)malloc(sizeof(char*) * (count + 1))))
		return (NULL);
	while (a < count)
	{
		countc = 0;
		while (s && *s && *s == c)
			s++;
		countc = ft_strsplit_count_len((char*)s, c);
		new[a] = ft_strsub(s, 0, countc);
		while (s && *s && *s != c)
			s++;
		a++;
	}
	new[a] = NULL;
	return (new);
}
