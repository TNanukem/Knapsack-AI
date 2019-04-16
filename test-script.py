# Este script em python gera o cabeçalho do arquivo .csv usado na análise
# e também roda o nosso analisador para o número de caso de testes que nós temos.

import os

file = open("out.csv", "w")
file.write("size, search_type,count,time,ids,right_answer\n")
file.close()

file = open("out.csv", "r+")
for i in range(5):
    os.system("./analysis tests/{}-test.txt >> out.csv".format(i))

file.close()
