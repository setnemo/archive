FROM php:7.1-apache

RUN apt-get -y update --fix-missing
RUN apt-get upgrade -y

# Install useful tools
RUN apt-get -y install nano

# Install important libraries
RUN apt-get -y install --fix-missing apt-utils build-essential git curl libcurl3 libcurl3-dev zip

# Composer
RUN curl -sS https://getcomposer.org/installer | php -- --install-dir=/usr/local/bin --filename=composer

# Install xdebug
RUN pecl install xdebug-2.5.0
RUN docker-php-ext-enable xdebug

# Other PHP7 Extensions

RUN apt-get -y install libmcrypt-dev
RUN docker-php-ext-install mcrypt

RUN apt-get -y install libsqlite3-dev libsqlite3-0 mysql-client
RUN docker-php-ext-install pdo_mysql 
RUN docker-php-ext-install pdo_sqlite
RUN docker-php-ext-install mysqli

RUN docker-php-ext-install curl
RUN docker-php-ext-install tokenizer
RUN docker-php-ext-install json

RUN apt-get -y install zlib1g-dev
RUN docker-php-ext-install zip

RUN apt-get -y install libicu-dev
RUN apt-get -y install sendmail
RUN docker-php-ext-install -j$(nproc) intl

RUN docker-php-ext-install mbstring

RUN apt-get install -y libfreetype6-dev libjpeg62-turbo-dev libpng-dev
RUN docker-php-ext-configure gd --with-freetype-dir=/usr/include/ --with-jpeg-dir=/usr/include/ 
RUN docker-php-ext-install -j$(nproc) gd
RUN apt-get update && apt-get install -q -y ssmtp mailutils && rm -rf /var/lib/apt/lists/*

RUN echo "hostname=localhost.localdomain" > /etc/ssmtp/smtp.conf
RUN echo "root=c.maessen@camagru.com" >> /etc/ssmtp/smtp.conf
RUN echo "mailhub=maildev" >> /etc/ssmtp/smtp.conf
# The above 'maildev' is the name you used for the link command
# in your docker-compose file or docker link command.
# Docker automatically adds that name in the hosts file
# of the container you're linking MailDev to.

# Set up php sendmail config
RUN echo "sendmail_path=sendmail -i -t" >> /usr/local/etc/php/conf.d/php-sendmail.ini

# Fully qualified domain name configuration for sendmail on localhost.
# Without this sendmail will not work.
# This must match the value for 'hostname' field that you set in ssmtp.conf.
RUN echo "localhost localhost.localdomain" >> /etc/hosts

RUN apt-get update   -y

RUN apt-get clean  -y

RUN apt-get autoremove -y

RUN apt-get update && apt-get upgrade  -y

RUN dpkg --configure -a




run echo mail > /etc/hostname
RUN echo '127.0.0.1 mail.example.com mail localhost' >> /etc/hosts
RUN echo ':: 1 mail.example.com mail localhost ip6-localhost ip6-loopback' >> /etc/hosts
RUN echo 'fe00 :: 0 ip6-localnet' >> /etc/hosts
RUN echo 'ff00 :: 0 ip6-mcastprefix' >> /etc/hosts
RUN echo 'ff02 :: 1 ip6-allnodes' >> /etc/hosts
RUN echo 'ff02 :: 2 ip6-allrouters' >> /etc/hosts

run chown root:root /etc/hosts

run apt-get install -q -y vim

# Install Postfix.
run echo "postfix postfix/main_mailer_type string Internet site" > preseed.txt
run echo "postfix postfix/mailname string mail.example.com" >> preseed.txt
# Use Mailbox format.
run debconf-set-selections preseed.txt
run DEBIAN_FRONTEND=noninteractive apt-get install -q -y postfix

run postconf -e myhostname=mail.example.com
run postconf -e mydestination="mail.example.com, example.com, localhost.localdomain, localhost"
run postconf -e mail_spool_directory="/var/spool/mail/"
run postconf -e mailbox_command=""

# Add a local user to receive mail at root@example.com, with a delivery directory
# (for the Mailbox format).
run mkdir /var/spool/mail/root
run chown root:mail /var/spool/mail/root

RUN echo 'postmaster: root' >> /etc/aliases
RUN echo 'root: root' >> /etc/aliases
RUN echo 'info: root' >> /etc/aliases
run chown root:root /etc/aliases
run newaliases

# Use syslog-ng to get Postfix logs (rsyslog uses upstart which does not seem
# to run within Docker).
run apt-get install -q -y syslog-ng

expose 25
RUN  apt-get install -f
RUN a2enmod rewrite headers
RUN service syslog-ng start
RUN service postfix start 



# Enable apache modules
