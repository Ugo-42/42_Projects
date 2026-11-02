#!/usr/bin/env python3

import os
import sys

print("Content-Type: text/html")
print()

print("<html><body>")
print("<h1>POST CGI</h1>")

method = os.environ.get("REQUEST_METHOD", "")
length = os.environ.get("CONTENT_LENGTH", "0")

print(f"<p>Method: {method}</p>")
print(f"<p>Content-Length: {length}</p>")

try:
    content_length = int(length)
except ValueError:
    content_length = 0

# Read EXACT number of bytes (important)
body = sys.stdin.read(content_length)

print("<h2>Body</h2>")
print("<pre>")
print(body)
print("</pre>")

print("</body></html>")
