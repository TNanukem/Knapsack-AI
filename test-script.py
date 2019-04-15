import os

for i in range(4):
    os.system("./main < tests/{}-test.txt >> out.txt".format(i))
