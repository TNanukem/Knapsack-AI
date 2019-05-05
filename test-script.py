# This python scripts runs all the 800 test cases and creates an .csv output to
# be analized.

import os

file = open("out.csv", "w")
file.write("case_test, size, search_type,count,time,ids,right_answer\n")
file.close()

file = open("out.csv", "r+")
for i in range(801):
    os.system("./analysis tests/{}-test.txt >> out.csv".format(i))

file.close()
