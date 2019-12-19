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

timestamps = [10, 100, 1000, 10000, 100000, 1000000, 10000000]

data = [sortwrapper(n) for n in timestamps]

df = pd.DataFrame(data, index=timestamps, columns=['multy','single', 'm/s'])
print(df)

