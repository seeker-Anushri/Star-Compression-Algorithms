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

# Simple LZ78 Compressor

This project implements a basic LZ78 compression algorithm in Python. The script reads a text file, compresses the content using LZ78, and writes the compressed data to an output file.

## Files

- `compressor.py`: The main implementation file containing the LZ78 compression algorithm.
- `freq17_320ver.txt`: The input text file to be compressed (ensure this file is in the same directory as the script).
- `freq17_com.txt`: The output file where the compressed data will be written.

## How to Use

### Execution

To run the script, use the following command:

```bash
python compressor.py
```

### Input

The script reads from a file named `freq17_320ver.txt`. Make sure this file contains the text you want to compress.

### Output

The compressed data will be written to a file named `freq17_com.txt`.

## Functions

### `compress(data)`

Compresses the input data using the LZ78 algorithm.
- **Parameters**: `data` (str) - the input string to be compressed.
- **Returns**: A list of tuples, where each tuple represents a dictionary index and a character.

### `add_zeros(code, nbr)`

Adds leading zeros to a binary string to ensure it has the specified length.
- **Parameters**: 
  - `code` (str) - the binary string.
  - `nbr` (int) - the desired length of the binary string.
- **Returns**: The binary string with leading zeros.

### `to_bits(data, h=False)`

Converts the compressed data to a binary string format.
- **Parameters**: 
  - `data` (list) - the compressed data.
  - `h` (bool) - flag to include delimiters in the output.
- **Returns**: A binary string representing the compressed data.

### Main Script

The script reads the input file, compresses the content, and writes the compressed data to the output file. It also prints the first character of the compressed data to the console.

```python
if __name__ == '__main__':
    with open('freq17_320ver.txt', 'r') as content_file:
        content = content_file.read()
    
    comp_data = compress(content)
    comp_data = str(comp_data)
    f = open("freq17_com.txt", "w+")
    print(comp_data[3])
    for i in range(len(comp_data)):
        # To ignore [ , '
        if comp_data[i] != "[" and comp_data[i] != "," and comp_data[i] != "'" and comp_data[i] != " ":
            f.write(comp_data[i])
```

## Example

Given the content of `freq17_320ver.txt` as `"abracadabra"`, the compression might produce the following output in `freq17_com.txt`:

```
[0, 'a'][0, 'b'][0, 'r'][1, 'c'][1, 'd'][2, 'b'][4, 'r'][0, '']
```

## Notes

- Ensure the `freq17_320ver.txt` file is in the same directory as the script.
- The current implementation is for educational purposes and might need further optimizations for production use.
- The script writes a simplified representation of the compressed data to the output file, which may not be in a standard compressed format.


