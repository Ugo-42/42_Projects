#!/usr/bin/perl

print "Content-Type: text/html\n\n";

print "<html><body>";
print "<h1>Hello from Perl CGI!</h1>";

print "<h2>Environment</h2><pre>";
foreach my $key (sort keys %ENV) {
    print "$key=$ENV{$key}\n";
}
print "</pre>";

print "<h2>Request Method</h2>";
print "<p>$ENV{'REQUEST_METHOD'}</p>";

print "<h2>Query String</h2>";
print "<p>$ENV{'QUERY_STRING'}</p>";

print "<h2>Body</h2><pre>";
while (<STDIN>) {
    print $_;
}
print "</pre>";

print "</body></html>";
