#!/usr/bin/env bash

find . -type f -printf '%A@ %p\n' | sort -r