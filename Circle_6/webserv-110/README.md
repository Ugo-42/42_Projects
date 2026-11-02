*This project has been developed as part of the 42 curriculum by ugwentzi and vvalenti.*

---

### Description
Webserv is a minimal HTTP server implemented in C++98.

It reproduces the core behavior of real-world web servers:
- Listening for incoming client connections
- Parsing and interpreting HTTP requests
- Generating and sending appropriate HTTP responses

---

### Browser–Server Interaction Example
```
Browser → HTTP Request → Webserv → HTTP Response → Browser → Page Rendering
```

---

Servers such as NGINX and Apache are full-featured HTTP servers.

In contrast, Webserv is intentionally simplified:
- Focused on core HTTP mechanics
- Not optimized for performance or production use
- Designed for learning and understanding server fundamentals

---

### Instructions

- Compilation
```bash
make # or `make all`
```

- Execution
```bash
./webserv [config_file]
```
If no configuration file is provided, the default configuration file is used: `./conf/default.conf`

---

### Connecting to the Server

- Using a web browser:
  Navigate to:
```
http://<IP>:<PORT>
```
Example:
```
http://localhost:8080
```

---

- Using curl:
```bash
curl -X <METHOD> http://<IP>:<PORT>/<PATH>
```
Example:
```bash
curl -X GET http://localhost:8080/index.html
```

---

- Using telnet:
```bash
telnet <IP> <PORT>
```
Example:
```bash
telnet localhost 8080
```

Then manually send an HTTP request:
```
GET /index.html HTTP/1.1
Host: localhost:8080
```

---

### Resources
The following resources were used to design and implement the project:
- https://hackmd.io/@fttranscendance/H1mLWxbr_#Types-de-r%C3%A9ponses
- https://nginx.org/en/docs/beginners_guide.html
- https://cplusplus.com/

Artificial intelligence tools were used selectively:
- To clarify concepts
- To assist with debugging
- To help structure certain parts of the project

However, the primary focus remained on understanding and implementing the system independently.
