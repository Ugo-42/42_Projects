#!/bin/sh

echo "Waiting for MariaDB..."

while ! mariadb -h mariadb -u $SQL_USER -p$SQL_PASSWORD -e "SELECT 1;" > /dev/null 2>&1; do
    sleep 2
    echo "MariaDB is unavailable - sleeping"
done

echo "MariaDB is up and authenticated!"

if [ ! -f "wp-config.php" ]; then
    echo "Starting WordPress installation..."
    wp core download --allow-root
    wp config create --allow-root --dbname=$SQL_DATABASE --dbuser=$SQL_USER --dbpass=$SQL_PASSWORD --dbhost=mariadb
    wp core install --allow-root --url=$DOMAIN_NAME --title=$WP_TITLE --admin_user=$WP_ADMIN_USER --admin_password=$WP_ADMIN_PASSWORD --admin_email=$WP_ADMIN_EMAIL
    wp user create $WP_USER $WP_USER_EMAIL --user_pass=$WP_USER_PASSWORD --role=author --allow-root
    echo "WordPress setup completed."
fi

echo "Starting PHP-FPM..."
exec php-fpm83 -F
