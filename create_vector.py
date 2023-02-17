import numpy as np
import argparse

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("nrows", type=int)
    parser.add_argument("ncols", type=int)
    args = parser.parse_args()

    x = np.random.randn(args.nrows, args.ncols)
    np.savetxt("input.tsv", x, delimiter="\t")