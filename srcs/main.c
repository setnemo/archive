#include "../libft/include/libft.h"

static const char b64_table[] = {
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
  'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
  'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
  'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
  'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
  'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
  'w', 'x', 'y', 'z', '0', '1', '2', '3',
  '4', '5', '6', '7', '8', '9', '+', '/'
};

#define ER0 "usage:  ft_ssl command [command opts] [command args]\n"
#define ER10 "ft_ssl: Error: \""
#define ER11 "\" is an invalid command.\n"
#define ER12 "Standard commands:\n"
#define ER13 "Message Digest commands:\n"
#define ER14 "Cipher commands:\n   base64\n   des\n   des-ecb\n   des-cbc\n"
#define ER15 "   des3\n   des3-ecb   \n   des3-cbc\n"
#define ER2 "ft_ssl: option requires an argument "
#define ER30 "   -h,  display this message\n"
#define ER31 "   -e,  encrypt mode (default, with all cipher commands)\n"
#define ER32 "   -d,  decrypt mode (with all cipher commands)\n"
#define ER33 "   -a,  base64 encode/decode (with DES algorithms)\n"
#define ER34 "   -k,  key in hex is the next arguement (with DES algorithms)\n"
#define ER35 "   -i,  input file for message\n"
#define ER36 "   -o,  output file for message\n"
#define ER301 ER30, ER31, ER32, ER33, ER34
#define ER302 ER35, ER36
#define ER000 ER10, argv, ER11, ER12, ER301, ER13, ER302, ER14, ER15
#define ER001 ER2, argv, ER0, ER12, ER301, ER13, ER302, ER14, ER15
#define ER002 ER0, ER12, ER301, ER13, ER302, ER14, ER15
#define CHF(x) argv[a][b] == x
#define CHN(x) argv[a][b + 1] == x
#define CHP(x) argv[a][b - 1] == x

void	ft_ssl_err(int a, char *argv)
{
	if (!argv)
		ft_printf(ER0);
	else
	{
		if (a == 1)
			ft_printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s", ER000);
		if (a == 2)
		{
			ft_printf("%s%s\n%s%s%s%s%s%s%s%s%s%s%s%s", ER001);
			exit(1);
		}
		if (a == 0)
			ft_printf("%s%s%s%s%s%s%s%s%s%s%s%s", ER002);
	}

}

char *b64_encode (const unsigned char *src, size_t len) {
	int i = 0;
	int j = 0;
	char *enc = NULL;
	size_t size = 0;
	unsigned char buf[4];
	unsigned char tmp[3];

	// alloc
	enc = (char *) malloc(1);
	if (NULL == enc) { return NULL; }

	// parse until end of source
	while (len--) {
		// read up to 3 bytes at a time into `tmp'
		tmp[i++] = *(src++);

		// if 3 bytes read then encode into `buf'
		if (3 == i) {
			buf[0] = (tmp[0] & 0xfc) >> 2;
			buf[1] = ((tmp[0] & 0x03) << 4) + ((tmp[1] & 0xf0) >> 4);
			buf[2] = ((tmp[1] & 0x0f) << 2) + ((tmp[2] & 0xc0) >> 6);
			buf[3] = tmp[2] & 0x3f;

			// allocate 4 new byts for `enc` and
			// then translate each encoded buffer
			// part by index from the base 64 index table
			// into `enc' unsigned char array
			enc = (char *) realloc(enc, size + 4);
			for (i = 0; i < 4; ++i) {
				enc[size++] = b64_table[buf[i]];
			}

			// reset index
			i = 0;
		}
	}

	// remainder
	if (i > 0) {
		// fill `tmp' with `\0' at most 3 times
		for (j = i; j < 3; ++j) {
			tmp[j] = '\0';
		}

		// perform same codec as above
		buf[0] = (tmp[0] & 0xfc) >> 2;
		buf[1] = ((tmp[0] & 0x03) << 4) + ((tmp[1] & 0xf0) >> 4);
		buf[2] = ((tmp[1] & 0x0f) << 2) + ((tmp[2] & 0xc0) >> 6);
		buf[3] = tmp[2] & 0x3f;

		// perform same write to `enc` with new allocation
		for (j = 0; (j < i + 1); ++j) {
			enc = (char *) realloc(enc, size + 1);
			enc[size++] = b64_table[buf[j]];
		}

		// while there is still a remainder
		// append `=' to `enc'
		while ((i++ < 3)) {
			enc = (char *) realloc(enc, size + 1);
			enc[size++] = '=';
		}
	}

	// Make sure we have enough space to add '\0' character at end.
	enc = (char *) realloc(enc, size + 1);
	enc[size] = '\0';

	return enc;
}


unsigned char *b64_decode_ex (const char *src, size_t len, size_t *decsize) {
	int i = 0;
	int j = 0;
	int l = 0;
	size_t size = 0;
	unsigned char *dec = NULL;
	unsigned char buf[3];
	unsigned char tmp[4];

	// alloc
	dec = (unsigned char *) malloc(1);
	if (NULL == dec) { return NULL; }

	// parse until end of source
	while (len--) {
		// break if char is `=' or not base64 char
		if ('=' == src[j]) { break; }
		if (!(ft_isalnum(src[j]) || '+' == src[j] || '/' == src[j])) { break; }

		// read up to 4 bytes at a time into `tmp'
		tmp[i++] = src[j++];

		// if 4 bytes read then decode into `buf'
		if (4 == i) {
			// translate values in `tmp' from table
			for (i = 0; i < 4; ++i) {
				// find translation char in `b64_table'
				for (l = 0; l < 64; ++l) {
					if (tmp[i] == b64_table[l]) {
						tmp[i] = l;
						break;
					}
				}
			}

			// decode
			buf[0] = (tmp[0] << 2) + ((tmp[1] & 0x30) >> 4);
			buf[1] = ((tmp[1] & 0xf) << 4) + ((tmp[2] & 0x3c) >> 2);
			buf[2] = ((tmp[2] & 0x3) << 6) + tmp[3];

			// write decoded buffer to `dec'
			dec = (unsigned char *) realloc(dec, size + 3);
			if (dec != NULL){
				for (i = 0; i < 3; ++i) {
					dec[size++] = buf[i];
				}
			} else {
				return NULL;
			}

			// reset
			i = 0;
		}
	}

	// remainder
	if (i > 0) {
		// fill `tmp' with `\0' at most 4 times
		for (j = i; j < 4; ++j) {
			tmp[j] = '\0';
		}

		// translate remainder
		for (j = 0; j < 4; ++j) {
				// find translation char in `b64_table'
				for (l = 0; l < 64; ++l) {
					if (tmp[j] == b64_table[l]) {
						tmp[j] = l;
						break;
					}
				}
		}

		// decode remainder
		buf[0] = (tmp[0] << 2) + ((tmp[1] & 0x30) >> 4);
		buf[1] = ((tmp[1] & 0xf) << 4) + ((tmp[2] & 0x3c) >> 2);
		buf[2] = ((tmp[2] & 0x3) << 6) + tmp[3];

		// write remainer decoded buffer to `dec'
		dec = (unsigned char *) realloc(dec, size + (i - 1));
		if (dec != NULL){
			for (j = 0; (j < i - 1); ++j) {
				dec[size++] = buf[j];
			}
		} else {
			return NULL;
		}
	}

	// Make sure we have enough space to add '\0' character at end.
	dec = (unsigned char *) realloc(dec, size + 1);
	if (dec != NULL){
		dec[size] = '\0';
	} else {
		return NULL;
	}

	// Return back the size of decoded string if demanded.
	if (decsize != NULL) {
		*decsize = size;
	}

	return dec;
}

unsigned char *b64_decode (const char *src, size_t len) {
	return (b64_decode_ex(src, len, NULL));
}
short		ft_check_base64_arg(int argc, char **argv)
{
	int		a;
	int		b;
	unsigned short	flag;
	char *si;
	char *so;
	a = 2;
	b = 0;
	flag = 0;
	while (a < argc)
	{
		b = 0;
		while (argv[a][b])
		{
			if (CHF('-') && (CHN('e') || CHN('d') || CHN('i') || CHN('o') || CHN('h')))
			{
				b++;
				if (argv[a][b] && CHF('h') && b == 1)
					ft_ssl_err(0, "help");
				if (argv[a][b] && CHF('e') && b == 1 && CHP('-'))
					flag |= 1;
				if (argv[a][b] && CHF('d') && b == 1 && CHP('-'))
					flag |= 2;
				if (argv[a][b] && CHF('i') && b == 1 && CHP('-'))
				{
					flag |= 4;
					if (argv[a + 1] != NULL)
					{
						flag |= 16;
						si = argv[a + 1];
					}
				}
				if (argv[a][b] && CHF('o') && b == 1 && CHP('-'))
				{
					flag |= 8;
					if (argv[a + 1] != NULL)
					{
						flag |= 32;
						so = argv[a + 1];
					}
				}
			}
			b++;
		} 
		a++;
	}
	//check flags
	ft_printf("all flags:%i\n", argc - 2);
	if (flag & 1)
		ft_printf("-e\n");
	if (flag & 2)
		ft_printf("-d\n");
	if (flag & 4)
		ft_printf("-i\n");
	if (flag & 8)
		ft_printf("-o\n");
	if (flag & 16)
		ft_printf("-i file:%s\n", si);
	if (flag & 32)
		ft_printf("-o file:%s\n", so);
	return (0);
}

void		start_base64(int argc, char **argv)
{
	//ft_putstr("start base64\n");
	if (argc > 7)
		ft_ssl_err(2, argv[argc - 1]);
	if (ft_check_base64_arg(argc, argv) > 0)
		exit(1);
	// char *enc = b64_encode("brian the monkey and bradley the kinkajou are friends\n", ft_strlen("brian the monkey and bradley the kinkajou are friends\n"));

	// ft_printf("%s\n", enc); // YnJpYW4gdGhlIG1vbmtleSBhbmQgYnJhZGxleSB0aGUga2lua2Fqb3UgYXJlIGZyaWVuZHM=
	// if (ft_strcmp(enc, "YnJpYW4gdGhlIG1vbmtleSBhbmQgYnJhZGxleSB0aGUga2lua2Fqb3UgYXJlIGZyaWVuZHM=") == 0)
	// 	ft_putstr("OK\n");
	// char *dec = b64_decode(enc, ft_strlen(enc));

	// ft_printf("%s\n", dec); // brian the monkey and bradley the kinkajou are friends
	// if (ft_strcmp(dec, "brian the monkey and bradley the kinkajou are friends") == 0)
	// 	ft_putstr("OK\n");
	// free(enc);
	// free(dec);
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
		else if (ft_strcmp(argv[1], "-h") == 0)
			ft_ssl_err(0, "help");
		else 
			ft_ssl_err(1, argv[1]);
	}
	else
		ft_ssl_err(0, NULL);
	return (0);
}
