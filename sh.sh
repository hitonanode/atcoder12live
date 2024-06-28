set -eu

g++-14 -Wfatal-errors -Wall -Wextra -g -O2 -std=c++20 -DHITONANODE_LOCAL main.cpp -o a.out
cat in/$1.txt | ./a.out | pbcopy
