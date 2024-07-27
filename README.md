# LZ77 Encoder

This project implements a simple LZ77 compression algorithm. The code compresses a given string by searching for the longest match between the look-ahead buffer and the search buffer, and then encodes this match using a tuple of the form `<offset, length, character>`.

## Files

- `LZ77encoder.cpp`: The main implementation file containing the LZ77 encoder.
- `LZ77encoder.h`: The header file (not provided in the original code snippet, assumed to contain function declarations and any necessary includes).

## How to Use

### Compilation

To compile the `LZ77encoder.cpp` file, use the following command in your terminal:

```bash
g++ -o LZ77encoder LZ77encoder.cpp
```

### Execution

To run the compiled executable, use the following command:

```bash
./LZ77encoder
```

### Input

Modify the `test` string within the code to the text you want to compress. For example:

```cpp
string test = "abracadabrad";
```

### Output

The compressed data will be written to a file named `compressed_file.txt` in the following format:
- Tuples of the form `<offset,length,character>` will be written with a `|` separator.
- For example, `3,4a|5,2b|c|` where `3,4a` indicates an offset of 3, a length of 4, and a character `a`.

The total compressed file size in bytes will be displayed in the console.

## Functions

### `void lab_upd()`

Updates the look-ahead buffer from the original text.

### `void buf_upd()`

Updates the search buffer and the look-ahead buffer with the match found.

### `void seq_sb()`

Searches the search buffer to find the longest match of the look-ahead buffer. This function also writes the compressed data to `compressed_file.txt`.

### `void encoder()`

The main function which calls the other functions in the correct order: `lab_upd`, `seq_sb`, `buf_upd`, and then `lab_upd` again until the look-ahead buffer is empty.

## Example

Given the input string `"abracadabrad"`, the compression process might produce an output file `compressed_file.txt` with the following content:

```
3,4a|5,2b|c|
```

## Notes

- Ensure the `test` string is correctly set in the code before running the encoder.
- The current implementation is for educational purposes and might need further optimizations for production use.

## License

This project is open-source and available for use under the MIT License.
