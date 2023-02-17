import numpy as np
import argparse

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("nrows", type=int)
    parser.add_argument("ncols", type=int)
    args = parser.parse_args()

    x = np.random.randn(args.nrows, args.ncols).astype(np.float64)
    x.T.tofile("input.bin") # transpose so that it is easier to read
    sum = np.sum(x, axis=1)
    sum.tofile("target.bin")