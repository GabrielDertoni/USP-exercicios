import argparse
import numpy as np
from matplotlib import pyplot as plt

def parse_args():
    parser = argparse.ArgumentParser(description="Takes the mean value from file.")

    parser.add_argument("filepaths", nargs='+',
                        help="The file path to take average on.")
    parser.add_argument("-s", nargs='+', dest="sizes", type=int,
                        help="The sizes of the inputs in the order of the files.")
    args = parser.parse_args()
    return args

def main():
    args = parse_args()
    means = []
    for path in args.filepaths:
        contents = open(path).read()
        lines = list(filter(lambda x: len(x) > 0, contents.split("\n")))
        times = np.array(list(map(lambda x: float(x.split(" ")[1]), lines)), dtype=np.float32)
        means.append(np.mean(times))
        print(means[-1])

    if args.sizes is not None and len(args.sizes) == len(args.filepaths):
        plt.plot(np.array(args.sizes, dtype=np.float32), means)
        plt.show()

if __name__ == '__main__':
    main()
