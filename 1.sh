#!/bin/bash
echo "# Bloxorz" >> README.md
git init
git add *
git commit -m "first commit"
git remote add origin https://github.com/plssreedhar/Bloxorz.git
git push -u origin master

