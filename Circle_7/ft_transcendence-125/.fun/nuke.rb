#!/usr/bin/env ruby

$stderr.sync = true

pin = rand(1000..9999).to_s
warn "\e[31mWARNING: About to nuke everything Docker related.\e[0m"
warn "Nuke code: \e[32m#{pin}\e[0m"
print "Enter nuke code to confirm: "

if gets.chomp != pin
  warn "\e[31mCode mismatch. Aborting.\e[0m"
  exit 1
end

warn "\e[31mCode accepted. Launch sequence initiated...\e[0m"
3.downto(1) do |i|
  print "\r\e[33mDetonation in #{i}s... \e[0m"
  sleep 0.33
end

exit 0
