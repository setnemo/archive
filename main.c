#include <unistd.h>

int			ft_strcmp(const char *s1, const char *s2)
{
	unsigned char *ss1;
	unsigned char *ss2;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	while (*ss1 && *ss1 == *ss2)
	{
		ss1++;
		ss2++;
	}
	return (*ss1 - *ss2);
}

void		ft_putchar(char c)
{
	write(1, &c, 1);
}


void		ft_putstr(char *str)
{
	int i;

	i = 0;
	if (str)
	{
		while (i[str] != '\0')
		{
			ft_putchar(i[str]);
			++i;
		}
	}
}

void		start_base64(int argc, char **argv)
{
	ft_putstr("start base64\n");
}

void		start_des_ecb(int argc, char **argv)
{
	ft_putstr("start des-ecb\n");
}

void		start_des_cbc(int argc, char **argv)
{
	ft_putstr("start des-cbc\n");
}

int			main(int argc, char **argv)
{

	if (argc > 1)
	{
		if (ft_strcmp(argv[1], "base64") == 0)
			start_base64(argc, argv);
		else if ((ft_strcmp(argv[1], "des") == 0) || (ft_strcmp(argv[1], "des-ecb") == 0))
			start_des_ecb(argc, argv);
		else if (ft_strcmp(argv[1], "des-cbc") == 0)
			start_des_cbc(argc, argv);
		else 
		{
			ft_putstr("ft_ssl: Error: ");
			ft_putstr(argv[1]);
			ft_putstr(" is an invalid command.\n\nStandard commands:\n\nMessage Digest commands:\n\nCipher commands:\nbase64\ndes\ndes-ecb\ndes-cbc\ndes3\ndes3-ecb\ndes3-cbc\n");
		}
	}
	else
		ft_putstr("usage: ft_ssl command [command opts] [command args]\n");
	return (0);
}
