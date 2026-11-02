#!/usr/bin/env ruby
require 'io/console'
require 'zlib'

# ************************************************************************** #
#                               CONFIGURATION                                #
# ************************************************************************** #

COLOR_PALETTE = [
  [230, 134, 39], [250, 246, 248], [213, 102, 23],
  [117, 49, 11], [240, 199, 135], [233, 172, 93],
  [242, 215, 175], [119, 50, 11]
].freeze

EXPLOSION_INTENSITY = 100
INITIAL_SLEEP = 0.10
MIN_SLEEP = 0.0001
DECAY_RATE = 0.0010
POST_FRAMES = 10
POST_LOOP_COUNT = 5

# ************************************************************************** #
#                         TERMINAL & SCREEN UTILITIES                        #
# ************************************************************************** #

def terminal_size
  IO.console.winsize
end

def hide_cursor
  print "\e[?25l"
end

def show_cursor
  print "\e[?25h\e[0m"
end

def paint_random_pixel(rows, cols)
  r, g, b = COLOR_PALETTE.sample
  print "\e[#{rand(1..rows)};#{rand(1..cols)}H\e[48;2;#{r};#{g};#{b}m \e[0m"
end

def paint_black_pixel(rows, cols)
  print "\e[#{rand(1..rows)};#{rand(1..cols)}H\e[48;2;0;0;0m \e[0m"
end

# ************************************************************************** #
#                        ANIMATION & DRAWING LOGIC                           #
# ************************************************************************** #

def draw_frame(frame, rows, cols)
  lines = frame.split("\n")

  row_offset = [(rows - lines.size) / 2, 0].max
  max_w = lines.map { |l| l.gsub(/\e\[.*?m/, '').length }.max || 0
  col_offset = [(cols - max_w) / 2, 0].max

  lines.each_with_index do |line, i|
    r = row_offset + i + 1 + rand(-1..1)
    c = col_offset + 1 + rand(-1..1)
    print "\e[#{r};#{c}H#{line}"
  end
end

def sleep_time(index)
  [INITIAL_SLEEP - (index * DECAY_RATE), MIN_SLEEP].max
end

def load_frames(path)
  Zlib::GzipReader.open(path) { |gz| gz.read }.split("\x03")
rescue StandardError => e
  abort("Error reading file: #{e.message}")
end

# ************************************************************************** #
#                                EXECUTION                                   #
# ************************************************************************** #

def run(path)
  frames = load_frames(path)
  hide_cursor

  frames.each_with_index do |frame, i|
    rows, cols = terminal_size

    EXPLOSION_INTENSITY.times { paint_random_pixel(rows, cols) }
    draw_frame(frame, rows, cols)

    sleep sleep_time(i)
  end

  post_frames = frames.last(POST_FRAMES)
  POST_LOOP_COUNT.times do
    post_frames.each do |frame|
      rows, cols = terminal_size

      EXPLOSION_INTENSITY.times { paint_random_pixel(rows, cols) }
      draw_frame(frame, rows, cols)

      sleep MIN_SLEEP
    end
  end

  rows, cols = terminal_size
  total_cells = rows * cols * 10

  total_cells.times do
    paint_black_pixel(rows, cols)
    sleep MIN_SLEEP
  end

  print "\e[2J"
  text = "Cleanup is almost done..."
  n = text.length
  max_delay = 0.18
  min_delay = 0.02

  loop do
    n.times do |i|
      output = text.chars.map.with_index do |char, idx|
        idx == i ? "\e[0;93m#{char}\e[33m" : char
      end.join

      print "\e[1;1H\e[1;33m#{output}\e[0m"

      progress = i.to_f / [n - 1, 1].max
      current_delay = min_delay + (max_delay - min_delay) * (1 - Math.sin(Math::PI * progress))
      
      sleep current_delay
    end
  end
ensure
  show_cursor
end

# ************************************************************************** #
#                               ENTRY POINT                                  #
# ************************************************************************** #

abort("Usage: #{$0} <file.ascii>") if ARGV.empty?

run(ARGV[0])

rows, cols = terminal_size
print "\e[#{rows - 1};#{cols}H"
