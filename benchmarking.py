import pandas as pd
import matplotlib.pyplot as plt


# Load the data from CSV
br = pd.read_csv("benchmarking/benchmark_recursive.csv", header=None, names=["n", "time"])

bn = pd.read_csv("benchmarking/benchmark_naive.csv", header=None, names=["n", "time"])

bv = pd.read_csv("benchmarking/benchmark_vector.csv", header=None, names=["n", "time"])


# print(br)

plt.figure(figsize=(8,6))

plt.plot(br["n"], br["time"], linestyle='--')
plt.plot(bn["n"], bn["time"], linestyle='--', color='red')
plt.plot(bv["n"], bv["time"], linestyle='--', color='blue')
plt.xlabel('n-th fibonacci number')
plt.ylabel('time [s]')

plt.savefig("benchmarking.png")