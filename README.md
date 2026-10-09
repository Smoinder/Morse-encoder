# Morse Code Translator

A console program in C that translates text to Morse code and back. Encoding uses a lookup table. Decoding walks a binary tree: a dot moves to one child, a dash to the other, and the node where a letter's code ends holds that letter.

## Features

- **Encode**: Latin letters (case-insensitive) and digits 0–9 to Morse
- **Decode**: Morse back to Latin letters and digits
- **Input**: type text in the console or read it from a text file
- **Reference**: print the Morse table for A–Z

## Building

You need a C compiler such as GCC, Clang or MSVC.

```sh
gcc main.c -o morse
```

## Usage

Run `./morse` (or `morse.exe` on Windows) and pick an option from the menu:

```
1.To code Latin to Morse
2.To decode from Morse to Latin
3.To see the table of Latin - Morse
4.Exit
```

Options 1 and 2 then ask whether to read from a file or from the console. For a file, enter its path. Only the first line of the file is read.

### Morse format

The program writes Morse in this format and expects the same format when decoding:

- `.` and `-` for dots and dashes
- one space between letters
- two spaces between words

```
SOS HELLO  =  ... --- ...  .... . .-.. .-.. ---
```

### Limitations

- Input is limited to 99 characters.
- Encoding ignores characters other than letters, digits and spaces, such as punctuation.
- Decoded text is in uppercase.

## Documentation

- [Specification.pdf](Specification.pdf): the project specification
- [User manual.pdf](User%20manual.pdf): the user manual
