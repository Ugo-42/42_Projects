FROM alpine:3.22

RUN apk update && apk upgrade && apk add --no-cache mariadb mariadb-client

RUN mkdir -p /run/mysqld && chown -R mysql:mysql /run/mysqld

COPY conf/mariadb-server.cnf /etc/my.cnf.d/mariadb-server.cnf
COPY tools/setup.sh /usr/local/bin/setup.sh
RUN chmod +x /usr/local/bin/setup.sh

EXPOSE 3306

ENTRYPOINT ["sh", "/usr/local/bin/setup.sh"]
