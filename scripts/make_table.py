import re

inp_filepath = 'results.txt'
out_filepath = 'table.txt'


with open(inp_filepath, 'r') as f:
    data = f.read()

data = [x.split('\n') for x in data.split('==Done==')]

struct_names = []
bench_names = []

results = []

for i,lines in enumerate(data):
    if len(lines) < 3:
        continue
    if lines[0] == '':
        lines = lines[1:]
    if i == 0:
        repCount = int(re.findall("\s*(\d*)\D*", lines[1])[0])
    name = re.findall("=+ (.*)\s+=+.*", lines[0])[0].rstrip()
    struct_names.append(name)
    lines = lines[2:]

    struct_results = []

    n = 0
    while (n+3) < len(lines):
        # print(lines[n])
        if i == 0:
            bench_names.append(re.findall("=== (.*) ===", lines[n])[0])
        
        total_time, rep_time = re.findall("^Time elapsed: ([\d\.]+)ms \(1 rep ~= (\d+)us\).*", lines[n+1])[0]
        checksum = int(re.findall("checksum: (\d+).*", lines[n+2])[0])

        struct_results.append((total_time, rep_time, checksum))

        n += 4
    results.append(struct_results)

# print("RepCount: ", repCount)
# print(bench_names)
# print(struct_names)
# print(results)

with open(out_filepath, 'w') as f:
    header = [*struct_names, " CHECKSUM "]
    sep = f"{'-'*25} | " + " | ".join([f"{'-'*14}" for x in header]) + "|\n"

    f.write(f"{' --- ':^25s} | " + " | ".join([f"{x:14s}" for x in header]) + "|\n")
    f.write(sep)

    # b_len = max([len(x) for x in bench_names])

    for i, name in enumerate(bench_names):
        t_total, t_rep, checksum = list(zip(*[x[i] for x in results]))
        # f.write()
        cs = "Y" if all([x == checksum[0] for x in checksum]) else 'N'
        f.write(f"{name:25s} | " + " | ".join([f"{x:>12s}ms" for x in t_total]) + f" | {cs:^14s}" + "|\n")
    
    f.write(sep)
    f.write('Times are in [ms]\n')
    f.write(f'rep count: {repCount}\n')
