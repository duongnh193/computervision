#!/bin/sh
echo -ne '\033c\033]0;Test GDE\a'
base_path="$(dirname "$(realpath "$0")")"
"$base_path/ShooterAI.x86_64" "$@"
