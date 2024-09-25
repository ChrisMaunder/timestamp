# Timestamp - A utility to change a files "Modified" time.

A simple utility to change a file - or multiple files - "Modified" time.




![timestamp.png](https://raw.githubusercontent.com/ChrisMaunder/timestamp/master/docs/assets/timestamp.png)

## Introduction

Working with a team of programmers in different time zones can be fun, but it can also cause major problems when files from different time zones get mixed and matched. The latest update to a new version of a file may have a date earlier than someone elses old version, meaning it won't be recompiled, or, a new file may have a date later than others meaning DevStudio repeatedly wants to recompile everything. 

The solution to this is: 

1. Get everyone to set their computer to the same time. This may work for some, but can be extremely inconvenient to others, or
2. Re-stamp the time on your files before sending them off to your colleagues.

I chose the latter, which meant I had to come up with a way to restamp file times. Enter TimeStamp. 

This is as basic a "Touch" program as you'll find. Just enter in the offset in days, hours and minutes (positive will push file times into the future, negative into the past), select your files, then hit "Go". Simple. 

Each file selected (either a single file or a complete directory tree) has it's "Last Modified" time set to the current time plus the offset that you choose. 

The program remembers the last offset you've set, the last 10 files and directories you've stamped, and it's last screen location. 

## Thanks to:

- Chris Losinger - Drop Edit
- Vladimir Kvashin, Girish Bharadwaj and Lars Klose - Directory picker class
- Davide Calibro - Flat buttons

## History

- 15 July 2009 - Added ability to set file times relative to the original file's time. Also compiles in VC9.
