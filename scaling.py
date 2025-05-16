import pandas as pd
import matplotlib.pyplot as plt


# Load the data from CSV
df = pd.read_csv("strong_scaling_results.csv")



# Plotting the results with error bars
plt.figure(figsize=(8, 6))
for size in df['size'].unique():
    # Get the first value of 'time_base_case' for the current 'size' group
    df_size = df[df['size'] == size].copy()
    group_avg = df_size.groupby('n_threads').agg(
        avg_time_parallel=('time_parallel', 'mean'),
        std_time_parallel=('time_parallel', 'std'),
    ).reset_index()
    base_case_time = group_avg['avg_time_parallel'].iloc[0]
    
    # Normalize 'time_parallel' and 'time_base_case' by the first value of 'time_base_case' for the group
    df_size['speedup_parallel'] = base_case_time / df_size['time_parallel']
    df_size = df_size.groupby('n_threads').agg(
        avg_speedup_parallel=('speedup_parallel', 'mean'),
        std_speedup_parallel=('speedup_parallel', 'std'),
    ).reset_index()
    df_size['ideal_speedup'] = df_size['n_threads']
    plt.errorbar(df_size['n_threads'], df_size['avg_speedup_parallel'],
                 yerr=df_size['std_speedup_parallel'], fmt='-o', label=f'n = {size}')

plt.plot(df['n_threads'], df['n_threads'], linestyle='--', color='grey',label='Ideal speedup')
# Customize the plot
plt.title('Speedup vs. Number of Threads',fontsize=20)
plt.xlabel('Number of Threads', fontsize=16)
plt.ylabel('Speedup',fontsize=16)
plt.xticks(fontsize=15)
plt.yticks(fontsize=15)
plt.legend(fontsize=15)
plt.xscale('log',base=2)
plt.yscale('log', base=2)
plt.grid(True)
plt.tight_layout()

# Show the plot
plt.savefig("strong_scaling.png")
plt.savefig("strong_scaling.eps")