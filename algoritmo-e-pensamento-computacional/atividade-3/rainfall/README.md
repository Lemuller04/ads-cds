# RainTracker3000

RainTracker3000 is a C program that simulates rainfall tracking across multiple fictional neighborhoods. The program generates randomized rainfall data and allows the user to view the information in monthly averages and and annual summaries displayed as simple ASCII graphs.

This project was developed as part of an academic assignment, with emphasis on modular design, the use of arrays, loops, and functions, and a clean separation between data handling, program control, and display logic.

## Features

- Randomized data generation: Automatically fills daily rainfall values for 12 months × 30 days per neighborhood.
- Configurable neighborhoods: Neighborhood names are stored in a single array, making it easy to add, remove, or modify tracked neighborhoods.
- Average rainfall calculations:
- Monthly averages (per neighborhood).
- Annual averages (per neighborhood).
- Text-based graphs: Displays rainfall data visually using proportional bars.
- Simple menu system: Users can navigate between annual and monthly views or exit the program.

## Usage

Compile the program (example using GCC):

```bash
gcc src/*.c -Iinclude -o raintracker
```

Run the executable:

```bash
./raintracker
```


Follow the on-screen menus to:

- View annual rainfall averages by neighborhood.
- View monthly rainfall averages.
- Stop the program.

## Project Structure

```bash
.
├── include/
│   ├── data.h         # Data definitions and constants
│   ├── display.h      # Output formatting and graph printing
│   └── control_flow.h # Menu and program flow
├── src/
│   ├── data.c         # Data generation and calculations
│   ├── display.c      # Console output and ASCII graphs
│   ├── control_flow.c # Menu logic and user input handling
│   └── main.c         # Program entry point
└── README.md
```

## Configuration

Neighborhoods are defined in src/control_flow.c in the neighborhood_names array:

```c
char neighborhood_names[][50] = {
    "Jardim Bela Vista",
    "Belford Roxo",
    "Leblon"
};
```

⚠️ If you add, remove, or edit names, you must also update the constant NEIGHBORHOODS_TRACKED in include/data.h so the program loops match the array size.

### Example:

```c
#define NEIGHBORHOODS_TRACKED 3
```

## Limitations

- Rainfall data is entirely randomized; this program is not intended for real meteorological analysis.
- Each month is fixed at 30 days for simplicity.
- Graphs are displayed using ASCII characters only.

## Author

Developed by Leonardo Müller de Lima, 2025.
