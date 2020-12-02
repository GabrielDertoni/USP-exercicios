import timeit
import numpy as np
import sys
from tqdm import tqdm
from string import ascii_uppercase, ascii_lowercase, digits

n = 10000

values = []
keys = []
for i in tqdm(range(n)):
    values.append("".join(list(np.random.choice(list(ascii_lowercase + ascii_uppercase + digits), np.random.randint(10, 266)))))
    keys.append("".join(list(np.random.choice(list(ascii_lowercase + ascii_uppercase + digits), np.random.randint(10, 522)))))

print("FINISHED GENERATING DATA")

def bench():
    global values, keys, n
    d = dict();
    for i in range(n):
        d[keys[i]] = values[i]

    print("size is: ", sys.getsizeof(d))

print(timeit.timeit(lambda: bench(), number=1))
