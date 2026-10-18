# LibokeParser

A lightweight C parser for `.liboke` files. LibokeParser is part of **Careoke**, a karaoke game written in pure C.

Careoke uses the `.liboke` file format, short for *Library of Careoke*, to store user data, application settings, and karaoke track information.

## Reference

### Getting Started

The best way to get started is to look at [`example.liboke`](example.liboke). It contains example data demonstrating how a `.liboke` file is written.

You can also look at [`src/example.c`](src/example.c) to see how LibokeParser is used.

### File Structure

The `.liboke` file format is inspired by assembly. It organizes data into sections, allowing different types of information to be stored in a single file.

### Standards

A `.liboke` file must start with `[gameliboke]` and must end with `[DONE]`

#### 1. Sections

A `.liboke` file can contain multiple sections. Each section has a specific purpose and holds its corresponding data.

A section starts with `\0\` and ends with `\1\`.

Currently, there are two types of sections:

- **Settings:** Stores configuration data.
- **Card:** Stores karaoke track data.

Refer to `example.liboke` for the exact syntax and structure of each section.

#### 2. Comments

Comments allow you to add notes to a `.liboke` file without treating them as data.

Lines beginning with `!` are used for comments.

For example:

```text
! This is a comment
```

Comments are useful for explaining configuration values or documenting the purpose of a card.

#### 3. Settings

The Settings section stores configuration values used by Careoke.

The available settings include:

| Setting | Description |
|---|---|
| `master_sound` | Master sound configuration |
| `background_sound` | Background sound configuration |
| `background_color` | Background color configuration |
| `default_config` | Default config file(.liboke) |

The expected value format depends on the setting. Refer to `example.liboke` for examples of how these values are represented.

#### 4. Cards

Cards represent karaoke tracks in Careoke. Each card stores information about a track, including its title, duration, score, and associated media files.

The card data includes the following fields:

| Field | Description |
|---|---|
| `TITLE` | The title of the karaoke track |
| `LENGTH` | The track's duration |
| `SCORE` | Lat played score |
| `VOCAL_PATH` | Path to the vocal audio file |
| `MP3_PATH` | Path to the music audio file |
| `LRC_PATH` | Path to the lyrics file(lrc) |

The exact representation of these fields follows the `.liboke` file format. Use `example.liboke` as the reference when creating your own cards. or `AddNewCard()` function can be used for this.

## Using LibokeParser

LibokeParser provides functions for validating reading and writing `.liboke` files.

### Include the Header

Include the parser header in your C source file:

```c
#include "path/to/this/library/headers/parser.h"
```

### Basic Example

The following example demonstrates the basic workflow:

```c
#include "parser.h"
#include <stdio.h>

#define EXAMPLE "example.liboke"

int main(void)
{
    Deck cards = {0};
    Settings sett = {0};

    if (ValidateOke(EXAMPLE))
    {
        printf("Invalid file detected\n");
        return 1;
    }

    ReadOKEData(EXAMPLE, &cards, &sett);

    return 0;
}
```

### Available Functions

| Function | Purpose |
|---|---|
| `ValidateOke()` | Validates a `.liboke` file before parsing |
| `ReadOKEData()` | Reads file data into a `Deck` and `Settings` structure |

read `headers/parser.h` for all the other function declarations and their expected arguments and their work.

## Building

Build the example Parser with make!

```sh
make all
```

and run with 

```sh
make run
```

Refer to the Makefile for the available build targets and compiler options.

## Contributing

Contributions, bug reports, and suggestions are welcome.

When submitting changes, please keep the implementation consistent with the existing code and ensure that changes to the file format are reflected in the documentation and example file.
If AI is used, please don't add unnecessary optimization and complexities as the code is suppose to be simple

## License

LibokeParser is distributed under the MIT License. See [`LICENSE`](LICENSE) for the full license text.
