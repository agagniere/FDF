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
bash benchmark.sh maps/mars.fdf tmp_folder my_image_name.png
xdg-open my_image_name.png
```

## Disclaimer
Beware as it is absolutely __NOT__ compliant to the 42 norm.
