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
bash benchmark.sh maps/mars.fdf tmp_folder my_image_name
xdg-open my_image_name.png
```

## Disclaimer
Beware as it is absolutely __NOT__ compliant to the 42 norm.
