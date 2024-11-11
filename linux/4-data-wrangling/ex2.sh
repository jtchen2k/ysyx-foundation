#!/bin/env bash

cat /usr/share/dict/words | grep -E '(.*a.*){3}[^s]$'

cat /usr/share/dict/words | grep -E '(.*a.*){3}[^s]$' | sed -E 's/(.*?)(..)$/\2/' | uniq -c | sort -nk1r | head -n3