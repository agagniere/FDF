# FDF
Wireframe rendering of heightmaps.

![C/C++ CI](https://github.com/agagniere/FDF/workflows/C/C++%20CI/badge.svg?branch=conanless)

## Dependencies

### System packages

Install these packages via your favorite package manager

Required to compile on Linux:
* __libx11-dev__
* __libxext-dev__
* __libxpm-dev__

Optional:
* __help2man__ to generate man pages
* __ghostscript__ to generate pdf documentation
* __gnuplot__ to render benchmark report

### Submodules

```bash
git submodule update --init
```

## Build

```bash
make
```
It will run the MinilibX `./configure` and compile the whole project.

## Documentation

### View the help
```
./fdf.exe --help
```

### Read the help as a man page
```
make man
man ./doc/fdf.1
```

### Read the help as a PDF
```
make pdf
xdg-open doc/fdf.pdf
```

## Benchmark

```
python -m benchmark
xdg-open benchmark_mars_transform.png
xdg-open benchmark_mars_draw.png
```

```
$ python -m benchmark --help
usage: __main__.py [-h] [--map MAP] [--prefix PREFIX] [--folder FOLDER]
                   [--width WIDTH] [--height HEIGHT] [--iterations ITERATIONS]
                   [-j JOBS]

Run benchmarks and draw graphs

options:
  -h, --help            show this help message and exit
  --map MAP             Input file to render
  --prefix PREFIX       Prefix for the graph images
  --folder FOLDER       Folder where to put temporary files
  --width WIDTH         Width of the image to render
  --height HEIGHT       Height of the image to render
  --iterations ITERATIONS
                        Number of times to render the same image
  -j JOBS, --jobs JOBS  Number of parallel jobs when compiling

```

## Disclaimer
Beware as it is absolutely __NOT__ compliant to the 42 norm.
