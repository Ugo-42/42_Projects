*This project has been created as part of the 42 curriculum by ugwentzi*

---

## Inception

### Description

Inception is a project about learning how to use Docker.<br>
The goal is to create 3 containers and make them work together using Docker Compose.

The 3 containers are:
- Nginx: a web server that will serve the content of the website.
- MySQL: a database that will store the data of the website.
- WordPress: an easy way to create a website from templates.

---

### Project description

#### **Virtual Machines vs Docker:**
* **The Problem:** VMs are "heavy," requiring a full OS and a hypervisor, leading to slow boot times and massive resource waste.
* **The Inception Way:** We use **Docker**, which shares the host's Linux kernel. This allows our containers to spin up in seconds and consume significantly fewer resources compared to a traditional VM.

---

#### **Secrets vs Environment Variables:**
* **The Danger:** Hardcoding passwords in a `Dockerfile` or `nginx.conf` is a security "critical failure." If your code is pushed to a repository, your credentials are leaked.
* **The Inception Way:** We use **Environment Variables** (stored in a `.env` file). This keeps sensitive data outside the container images, ensuring that secrets are only injected at runtime and never baked into the build.

---

#### **Docker Network vs Host Network:**
* **The Risk:** Using the `host` network exposes every container port directly to the internet, creating a massive security vulnerability.
* **The Inception Way:** We utilize a **Bridge Network**. This creates a private, internal "intercom system" where WordPress can talk to MariaDB, but the outside world can *only* see Nginx through Port 443.

---

#### **Docker Volumes vs Bind Mounts:**
* **The Struggle:** Bind mounts are tied to specific host paths and often cause "Permission Denied" nightmares when moving between different systems.
* **The Inception Way:** We use **Named Docker Volumes**. This allows Docker to handle the storage lifecycle. Your data persists even if the container is destroyed, while the management remains portable and clean within the Docker ecosystem.

---

### Instructions

| Command                    | Description                                        |
|----------------------------|----------------------------------------------------|
| `make` / `make all`        | Fully initialize and start the project.            |
| `make up`                  | Start all containers.                              |
| `make down`                | Stop and remove running containers.                |
| `make restart`             | Restart containers (`down` then `up`).             |
| `make clean`               | Stop containers and remove unused docker resources.|
| `make fclean`              | Remove all local data and Docker resources.        |
| `make re`                  | Rebuild and restart everything.                    |
| `make nuclear_docker_nuke` | Me after seeing 403 forbidden when trying to access the site 💥​|

---

Once the project is up and running, you can access the website at `http://localhost:8080`.

---

### Resources

Most help came from this tutorial: `https://tuto.grademe.fr/inception/`<br>
Ai was used mostly for package names + conflicts resolution between debian vs alpine.
And to help with building and refining the documentation files.
