# MP3 Tag Reader and Editor in C

A command-line based MP3 Tag Reader and Editor developed using C programming language.

## Features

- View MP3 metadata
- Edit MP3 tags
- Read Title, Artist, Album, Year, Genre, and Comment
- Modify selected MP3 tags
- ID3v2 tag parsing
- Command-line execution

## Technologies Used

- C Language
- File Handling
- Binary File Processing
- Structures
- Modular Programming
- MP3 ID3 Tag Parsing

## How to Run

### Compile

```bash
gcc main.c view.c edit.c -o mp3
```

### View MP3 Tags

```bash
./mp3 -v song.mp3
```

### Edit MP3 Title

```bash
./mp3 -e -t "New Title" song.mp3
```

### Edit Artist

```bash
./mp3 -e -a "Artist Name" song.mp3
```

## Project Structure

```bash
.
├── main.c
├── view.c
├── edit.c
├── view.h
├── edit.h
├── types.h
└── song.mp3
```

## Concepts Used

- MP3 ID3 Metadata
- Binary File Parsing
- Endian Conversion
- File Manipulation
- Command Line Arguments
- Dynamic Memory Allocation

## Future Improvements

- GUI support
- Playlist support
- Batch editing
- Cover image extraction

## Author

Surya Bhargav
