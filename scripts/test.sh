#!/usr/bash
valgrind --leak-check=full --show-reachable=yes --error-limit=no --suppressions=./scripts/supp/minimal-sdl2.supp --suppressions=./scripts/supp/sdl2-texture.supp ./tpclient

