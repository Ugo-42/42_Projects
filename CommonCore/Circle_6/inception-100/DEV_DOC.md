# Developer Documentation - Inception

## 1. Environment Setup
### Prerequisites
- Docker and Docker Compose installed on a Linux environment.
- Root or sudo privileges to manage network and volume paths.

### Configuration
- **Domain**: You must map your local IP to the project domain by adding `127.0.0.1 ugwentzi.42.fr` to the `/etc/hosts` file.
- **Secrets**: Environment variables are stored in `srcs/.env`. This file defines the database names, passwords, and the WordPress admin credentials used during the automated setup.

## 2. Build and Launch
The infrastructure is defined in `srcs/docker-compose.yml`. Each service is built from a custom `Dockerfile` located in `srcs/requirements/`.
- Use `make re` to trigger a full rebuild of the images.
- Use `make logs` to monitor real-time output from the PHP-FPM and Nginx processes.

## 3. Persistent Data and Volumes
The project uses Docker volumes to ensure data persists even if containers are deleted:
- **WordPress Files**: Mounted to the host at `/home/ugwentzi/data/wordpress`.
- **Database Data**: Mounted to the host at `/home/ugwentzi/data/mariadb`.

## 4. Troubleshooting Commands
- **Check Configuration**: `docker exec nginx nginx -t` (Verifies Nginx syntax).
- **Database Access**: `docker exec -it mariadb mariadb -u root -p` (Manual SQL access).
- **Network Check**: `docker network ls` (Verifies the `inception` bridge network).
