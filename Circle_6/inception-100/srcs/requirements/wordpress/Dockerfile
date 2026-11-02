FROM alpine:3.22

RUN apk update && apk upgrade && apk add --no-cache \
    php83 php83-fpm php83-mysqli php83-phar php83-iconv \
    php83-curl php83-dom php83-exif php83-fileinfo \
    php83-gd php83-mbstring php83-openssl php83-xml php83-zip \
    curl mariadb-client

RUN adduser -S www-data -G www-data 2>/dev/null || true

RUN echo "memory_limit=512M" > /etc/php83/conf.d/memory-limit.ini

RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar && \
    chmod +x wp-cli.phar && mv wp-cli.phar /usr/local/bin/wp

RUN mkdir -p /var/www/wordpress && chown -R www-data:www-data /var/www/wordpress

RUN sed -i 's/listen = 127.0.0.1:9000/listen = 0.0.0.0:9000/g' /etc/php83/php-fpm.d/www.conf
RUN sed -i 's/user = nobody/user = www-data/g' /etc/php83/php-fpm.d/www.conf
RUN sed -i 's/group = nobody/group = www-data/g' /etc/php83/php-fpm.d/www.conf

COPY tools/setup.sh /usr/local/bin/setup.sh
RUN chmod +x /usr/local/bin/setup.sh

WORKDIR /var/www/wordpress

EXPOSE 9000

ENTRYPOINT ["sh", "/usr/local/bin/setup.sh"]
