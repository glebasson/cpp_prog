#!/usr/bin/python3
import subprocess
import pandas as pd

def sortwrapper(n):
    args = ("../../build/meson-out/08", str(n))
    popen = subprocess.Popen(args, stdout=subprocess.PIPE)
    popen.wait()
    output = popen.stdout.read()
    m, s = output.decode("utf-8").split()
    return m, s, float(int(s)/int(m))

timestamps = [10, 100, 1000, 10000, 100000, 1000000]

data = [sortwrapper(n) for n in timestamps]

df = pd.DataFrame(data, index=timestamps, columns=['multy','single', 'm/s'])
print(df)

# 4 threads
# 10          1299321      155327  0.119545
# 100         2210905     1683440  0.761426
# 1000        7190045    10298496  1.432327
# 10000      37916686    53352410  1.407096
# 100000    215756707   602014712  2.790248
# 1000000  2202604280  7234255324  3.284410