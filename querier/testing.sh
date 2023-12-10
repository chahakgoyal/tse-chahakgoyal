#!/bin/bash

#invalid queries
./querier ~/cs50-dev/shared/tse/output/letters-2 ~/cs50-dev/shared/tse/output/letters-2.index

#invalid pageDirectory
./querier ~/cs50-dev/shared/tse/output/letters-4 ~/cs50-dev/shared/tse/output/letters-2.index

#invalid index file
./querier ~/cs50-dev/shared/tse/output/letters-2 ~/cs50-dev/shared/tse/output/letters-4.index

#incorrect number of arguments
./querier

#valid queries
./querier ~/cs50-dev/shared/tse/output/letters-2 ~/cs50-dev/shared/tse/output/letters-2.index

#valgrind queries
valgrind ./querier ~/cs50-dev/shared/tse/output/letters-2 ~/cs50-dev/shared/tse/output/letters-2.index
