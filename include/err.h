/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 13:02:30 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/03 13:02:31 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_H
# define ERR_H
# define ER00 "ft_ssl: Error: \""
# define ER01 "\" is an invalid command.\n"
# define ER02 "ERROR! '"
# define ER10 "Standard commands:\n"
# define ER11 "Message Digest commands:\n"
# define ER12 "Cipher commands:\n   base64\n   des\n   des-ecb\n   des-cbc\n"
# define ER30 "ft_ssl: option requires an argument\n"
# define ER31 "   -e,  encrypt mode (default, with all cipher commands)\n"
# define ER32 "   -d,  decrypt mode (with all cipher commands)\n"
# define ER33 "   -a,  base64 encode/decode (with DES algorithms)\n"
# define ER34 "   -k,  key in hex is the next arguement (with DES algorithms)\n"
# define ER35 "   -v,  iv in hex is the next argument (with DES algorithms)\n"
# define ER36 "   -p,  print the iv/key (with DES algorithms)\n"
# define ER37 "   -i,  example: \"-i [input_file_name]\" (default STDIN)\n"
# define ER38 "   -o,  example: \"-o [output_file_name]\" (default STDOUT)\n"
# define ERRS ER31, ER32, ER33, ER34, ER35, ER36
# define ERRM ER37, ER38
# define ERP1 ER00, argv[1], ER01, ER10, ERRS, ER11, ERRM, ER12
# define ERP2 ER02, str, ER01, ER30, ERRS, ERRM
#endif
