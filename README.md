# Goal
Traverse a matrix searching for the correct path to take

# Description
Read the string parameter being passed, which will represent the movements made in a 5x5 grid of cells starting from the top left position.
The characters in the input string will be entirely composed of: r, l, u, d, ?.
Each of the characters stand for the direction to take within the grid, for example: r = right, l = left, u = up, d = down.
The goal is to determine what characters the question marks should be in order for a path to be created to go from
the top left of the grid all the way to the bottom right without touching previously travelled on cells in the grid.

For example: if the string is "r?d?drdd" then the program should output the final correct string that will allow a path to be formed
from the top left of a 5x5 grid to the bottom right. For this input, the program should therefore return the string rrdrdrdd.
There will only ever be one correct path and there will always be at least one question mark within the input string.

# Examples
## Example 1
`Input: "???rrurdr?"`

`Output: dddrrurdrd`

## Example 2
`Input: "drdr??rrddd?"`

`Output: drdruurrdddd`

# Build

`make`

# Execute
1. Run all tests

`./correct_path -t`

2. Give an input

`./correct_path ???rrurdr?`
