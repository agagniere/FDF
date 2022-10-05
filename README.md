# FDF
Wireframe rendering of heightmaps.

![C/C++ CI](https://github.com/agagniere/FDF/workflows/C/C++%20CI/badge.svg?branch=master)

## Dependencies

Dependencies are handled by Conan.

However I did not push my packages in conancenter, so they must be created locally

### Create packages in local cache
```bash
git submodule update --init
for folder in vendor/Libft vendor/MinilibX vendor/HLM
do
    (cd $folder && conan create .)
done
```

### Finally

For this exmaple, we will disable the use of dynamic libraries. Such options can be set in a conan profile for reusability
```bash
conan install . --options libft:shared=False --options minilibx:shared=False --build missing
```

## Build

```bash
make
```

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
