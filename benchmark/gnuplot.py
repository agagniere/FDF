import sys


class Target:
    def __init__(self, title, filename, expr, style):
        self.filename = filename
        self.expr = expr
        self.style = style
        self.title = title

    def __str__(self):
        return f"\"{self.filename}\" using ({self.expr}) with {self.style} title '{self.title}'"


def render_graph(graph :dict, targets :list, limits = '[:][:]', file = sys.stdout):
    for key, value in graph.items():
        if isinstance(value, list):
            print('set', key, *value, file=file)
        elif isinstance(value, str):
            print('set', key, f"'{value}'", file=file)
        else:
            print('set', key, value, file=file)
    print('plot', limits, ', '.join(map(str, targets)), file=file)
