import numpy as np

if __name__ == '__main__':
    N = 1000000
    x = np.random.randn(N, 5)
    np.savetxt("input.tsv", x, delimiter="\t")