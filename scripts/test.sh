#!/usr/bash
valgrind \
--leak-check=full \
--show-reachable=yes \
--error-limit=no \
--suppressions=./scripts/supp/minimal-sdl2.supp \
--suppressions=./scripts/supp/sdl2-texture.supp \
--suppressions=./scripts/supp/minimal-sdl2-ttf-window.supp \
--suppressions=./scripts/supp/ubuntu-desktop.supp \
--suppressions=./scripts/supp/ubuntu-desktop2.supp \
--suppressions=./scripts/supp/ubuntu-desktop3.supp \
--suppressions=./scripts/supp/ubuntu-desktop4.supp \
--suppressions=./scripts/supp/ubuntu-desktop5.supp \
./tpclient
