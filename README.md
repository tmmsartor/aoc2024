Advent of Code 2024 problems solved with C++.

## Usage

## Input data

Download input data and possible solution in `<data_dir>` of choice.
The code expect input and solution data stored as `<data_dir>/NN/<case>/input`, i.e.:
* `./data/05/user1/input`
* `./data/06/user1/input`
* `./data/06/test/input`
* `./data/06/test/sol`
In this example `<data_dir>` is `./data/` and `<case_data_dir>` is `./data/06/test/` or similar.
The solution file is a two lines file with solution string for each part.

### C++
* build: `cmake -B build && cmake --build build`
* run all: `./build/src/main <data_dir>`
* run day n: `./build/src/main <case_data_dir> [log level]`


###  Typescript

* run and build: `tsc; node dist/01/main.js`
NB: Only first 6 days are solve also with Typescript
