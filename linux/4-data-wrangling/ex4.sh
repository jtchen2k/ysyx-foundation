#!bin/env bash

journalctl | grep '\[1\]: Startup finished in' | cut -c 1-15 | sort -r | head -n10
