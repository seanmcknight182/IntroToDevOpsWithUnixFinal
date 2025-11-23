#!/bin/bash
#parses data for main, throws it all in a .txt that is deleted after main is done
#yes, there are better ways to do this, I DO NOT CARE
#Sincerilly, sean mcknight

curl https://www.tntech.edu/engineering/programs/csc/faculty-and-staff.php -o thepage.txt

tr '\n' ' ' < thepage.txt \
  | grep -oP '(?<=<h4><strong>).*?(?=</strong>)|(?<=<h3>).*?(?=</h3>)' \
  | sed 's/&nbsp;//g; s/<br>//g; s/,.*//' \
  | tr 'A-Z' 'a-z' \
  | sed -E 's/^(md |s )+//' \
  | sort \
  > names.txt     

#Danke Chatgpt.
#grep was a pain, but now we can advance.
