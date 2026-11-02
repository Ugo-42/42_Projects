# User Documentation - Inception

## 1. Description of Services
This project provides a fully containerized WordPress stack designed for security and performance.
- **Nginx**: Acts as the entry point, providing a secure HTTPS connection.
- **WordPress**: The content management system used to build and manage the website.
- **MariaDB**: The relational database that securely stores all site content and user data.

## 2. Managing the Project
To manage the lifecycle of the infrastructure, use the following commands from the root directory:
- **To Start**: Run `make` or `make up`. This initializes the volumes and starts all services.
- **To Stop**: Run `make down`. This stops the services without deleting your website data.

## 3. Accessing the Services
Once the project is running, you can access the following:
- **The Website**: [https://ugwentzi.42.fr](https://ugwentzi.42.fr)
- **The Admin Panel**: [https://ugwentzi.42.fr/wp-admin](https://ugwentzi.42.fr/wp-admin)

*Note: You may see a browser security warning. This is expected as the project uses a self-signed SSL certificate for local development.*

## 4. Credentials
User credentials and database settings are managed via the `.env` file located in the `srcs/` directory.
- The **Admin User** has full rights to manage themes and plugins.
- The **Standard User** is restricted to content creation and editing.

## 5. Verifying Service Health
You can check if all services are functioning correctly by running:
`docker ps`
Ensure that the status for `nginx`, `wordpress`, and `mariadb` is "Up".
