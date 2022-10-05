"""
To get a more human-readable help, use:
$ python -m benchmark --help

Note:
To execute this package as a script, one should do:
$ python -m benchmark
and NOT
$ python benchmark
"""

import os
import sys
import argparse
import subprocess
from benchmark import Target, render_graph

if __name__ == '__main__':
    cli_parser = argparse.ArgumentParser(description = 'Run benchmarks and draw graphs')
    cli_parser.add_argument('--map', type = str, default = 'maps/mars.fdf', help = 'Input file to render')
    cli_parser.add_argument('--prefix', type = str, default = 'benchmark_mars', help = 'Prefix for the graph images')
    cli_parser.add_argument('--folder', type = str, default = 'bench_tmp', help = 'Folder where to put temporary files')
    cli_parser.add_argument('--width', type = int, default = 1280, help = 'Width of the image to render')
    cli_parser.add_argument('--height', type = int, default = 720, help = 'Height of the image to render')
    cli_parser.add_argument('--iterations', type = int, default = 512, help = 'Number of times to render the same image')
    cli_parser.add_argument('-j', '--jobs', type = int, default = 4, help = 'Number of parallel jobs when compiling')
    cli_args = cli_parser.parse_args()

    transform_targets = []
    draw_targets = []
    my_env = os.environ.copy()
    subprocess.run(['mkdir', '-p', cli_args.folder], check=True)
    for cflags in ['-O0', '-O2', '-O2 -march=native', '-Ofast -march=native']:
        name = ''.join(filter(str.isalnum, cflags))
        for prefix, suffix, cppflag, command, targets in [('', '', '', ['make', 'clean'], [(transform_targets, 'column(2)/column(1)'), (draw_targets, 'column(4)/column(3)')]),
                                                          ('Simple ', '_simple', '-DSIMPLISTIC_TRANSFORM', ['touch', 'src/transform.c'], [(transform_targets, 'column(2)/column(1)')]),
                                                          ('Naive ', '_naive', '-DDRAWING_ALGO=NAIVE', ['touch', 'src/hooks.c'], [(draw_targets, 'column(4)/column(3)')])]:
            tsv_name = f'{cli_args.folder}/bench_{name}{suffix}.out'
            my_env['CFLAGS'] = cflags
            my_env['CPPFLAGS'] = cppflag
            subprocess.run(command, check=True)
            subprocess.run(['make', 'build', f'-j{cli_args.jobs}'], env=my_env, check=True)
            with open(tsv_name, 'w') as tsv:
                subprocess.run(map(str, ['./fdf.exe', '--width', cli_args.width, '--height', cli_args.height,
                                         '--benchmark', cli_args.iterations, '--output', '/dev/null', cli_args.map]),
                               stdout=tsv, check=True)
            for target, formula in targets:
                target.append(Target(prefix + cflags, tsv_name, formula, 'lines'))

    script_name = f'{cli_args.folder}/render.gnuplot'
    with open(script_name, 'w') as plot_script:
        gnuplot = {}
        gnuplot['xlabel'] = 'Iteration'
        gnuplot['ytics'] = 20
        gnuplot['mytics'] = 4
        gnuplot['terminal'] = ['png', 'size', '2560,1440']

        gnuplot['title'] = 'Comparing transform algorithms and optimization flags'
        gnuplot['ylabel'] = 'Average delay to gnuplot 1 point (ns)'
        gnuplot['output'] = f'{cli_args.prefix}_transform_autozoom.png'
        render_graph(gnuplot, transform_targets, f'[:{cli_args.iterations}][0:]', file=plot_script)
        gnuplot['output'] = f'{cli_args.prefix}_transform.png'
        render_graph(gnuplot, transform_targets, f'[:{cli_args.iterations}][0:120]', file=plot_script)

        gnuplot['title'] = f'Comparing line drawing algorithms and optimization flags, with a resolution of {cli_args.width}x{cli_args.height}'
        gnuplot['ylabel'] = 'Average delay to draw 1 line (ns)'
        gnuplot['output'] = f'{cli_args.prefix}_draw_autozoom.png'
        render_graph(gnuplot, draw_targets, f'[:{cli_args.iterations}][0:]', file=plot_script)
        gnuplot['output'] = f'{cli_args.prefix}_draw.png'
        render_graph(gnuplot, draw_targets, f'[:{cli_args.iterations}][0:240]', file=plot_script)

    subprocess.run(['gnuplot', script_name])
