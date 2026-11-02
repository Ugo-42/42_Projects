FROM alpine:3.22

RUN apk update && apk upgrade && apk add --no-cache nginx openssl

RUN mkdir -p /etc/nginx/ssl && \
    openssl req -x509 -nodes -out /etc/nginx/ssl/inception.crt -keyout /etc/nginx/ssl/inception.key \
    -subj "/C=FR/ST=IDF/L=Paris/O=42/OU=42/CN=ugwentzi.42.fr/UID=ugwentzi"

COPY conf/nginx.conf /etc/nginx/http.d/default.conf

EXPOSE 443

CMD ["nginx", "-g", "daemon off;"]
