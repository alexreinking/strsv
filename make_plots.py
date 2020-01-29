import sys
import csv
from collections import defaultdict
import matplotlib.pyplot as plt


def load_results(file):
    with open(file) as f:
        seen_headers = False
        for row in csv.reader(f):
            if seen_headers:
                _, solver, n = tuple(f'{row[0]}///'.split('/')[:3])
                n, stat = tuple(f'{n}__'.split('_')[:2])
                if not stat or stat == 'mean':
                    yield solver, int(n), float(row[-1])
            else:
                # The Google Benchmark printer includes irrelevant stuff
                seen_headers = (row[0] == 'name')


def parse_results(file):
    d = defaultdict(lambda: ([], []))
    for solver, n, t in load_results(file):
        d[solver][0].append(n)
        d[solver][1].append(t)
    return d


def main():
    for file in sys.argv[1:]:
        results = parse_results(file)
        for solver, (n, y) in results.items():
            plt.plot(n, y, label=solver)

    plt.xlabel('problem size (n)')
    plt.ylabel('FLOPS')
    plt.title("strsv scaling")
    plt.legend()

    plt.savefig('chart.png')
    plt.show()


if __name__ == '__main__':
    main()
