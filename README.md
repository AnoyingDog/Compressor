# Compressor
#### A simple Video compressor
<hr>

A simple C program I wrote in my free time to remove the need for an online video compressor.
It works by calculating the bitrate by using the desired file size and the video length, then passing said information to [FFmpeg](https://github.com/FFmpeg/FFmpega) to compress it.

## How to Build
Building works by running the install.sh included in the repo which simply compiles the program and moves it to /usr/bin/compressor

## Usage
Run compressor while passing in the input file, desired file size in MB, the Audiobitrate and the output file
As example:

```
compressor input.mp4 10 128 output.mp4
```
