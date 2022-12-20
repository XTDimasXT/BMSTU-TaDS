#!/bin/sh
dot -Tpng list_graph.dot -o graph_list.png
gio open graph_list.png