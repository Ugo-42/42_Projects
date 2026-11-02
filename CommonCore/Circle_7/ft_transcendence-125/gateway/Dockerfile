FROM nginx:alpine

RUN apk add --no-cache openssl

RUN mkdir -p /etc/nginx/ssl && \
    openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
    -keyout /etc/nginx/ssl/transcendence.key \
    -out /etc/nginx/ssl/transcendence.crt \
    -subj "/C=FR/ST=GrandEst/L=Mulhouse/O=42/CN=localhost"

RUN rm /etc/nginx/conf.d/default.conf

COPY templates/nginx.conf.template /etc/nginx/templates/nginx.conf.template

EXPOSE 80 443

CMD ["nginx", "-g", "daemon off;"]
