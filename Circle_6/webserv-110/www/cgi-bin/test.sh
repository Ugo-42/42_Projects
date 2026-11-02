#!/bin/bash

# Required CGI header
echo "Content-Type: text/html"
echo ""

echo "<html><body>"
echo "<h1>Hello from Shell CGI!</h1>"

echo "<h2>Environment</h2>"
echo "<pre>"
env
echo "</pre>"

echo "<h2>Request Method</h2>"
echo "<p>$REQUEST_METHOD</p>"

echo "<h2>Query String</h2>"
echo "<p>$QUERY_STRING</p>"

echo "<h2>Body</h2>"
echo "<pre>"
cat -
echo "</pre>"

echo "</body></html>"
