#!/bin/sh
dot -Tpng tree.gv -o tree.png
gio open tree.png