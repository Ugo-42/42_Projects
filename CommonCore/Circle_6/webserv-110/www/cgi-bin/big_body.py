#!/usr/bin/env python3

import os
import sys

print("Content-Type: text/html")
print("")

print("<html><body>")
print("<h1>Hello from Python CGI!</h1>")

print("<h2>Environment</h2><pre>")
for key in sorted(os.environ.keys()):
    print(f"{key}={os.environ[key]}")
print("</pre>")

print("<h2>Request Method</h2>")
print(f"<p>{os.environ.get('REQUEST_METHOD', '')}</p>")

print("<h2>Query String</h2>")
print(f"<p>{os.environ.get('QUERY_STRING', '')}</p>")

print("<h2>Body</h2><pre>")

for line in sys.stdin:
    print(line, end="")

print("</pre>")

print("</body></html>")

while True:
    print("I EAT RAM AT BREAKFAST")
