import numpy as np
import argparse

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("nrows", type=int)
    parser.add_argument("ncols", type=int)
    parser.add_argument("prefix", type=str)
    args = parser.parse_args()

    x = np.random.randn(args.nrows, args.ncols).astype(np.float64)
    x.T.tofile(f"{args.prefix}_input.bin") # transpose so that it is easier to read
    sum = np.sum(x, axis=1)
    sum.tofile(f"{args.prefix}_target.bin")