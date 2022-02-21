# -*- coding: utf-8 -*-

from scipy.optimize import fsolve
#from math import exp
import os
import sys
import time

# (x-a)^2+(y-b)^2=e^2
# (u-c)^2+(v-d)^2=f^2
# (x-a)*(u-x)+(y-b)*(v-y)=0
# (u-c)*(u-x)+(v-d)*(v-y)=0

def equations(vars):
    global a
    global b
    global c
    global d
    global e
    global f

    x, y, u, v = vars

    eq1 = (x-a)**2+(y-b)**2-e**2
    eq2 = (u-c)**2+(v-d)**2-f**2
    eq3 = (x-a)*(u-x)+(y-b)*(v-y)
    eq4 = (u-c)*(u-x)+(v-d)*(v-y)
    return [eq1, eq2, eq3, eq4]


#file:
'''
x1 y1 x2 y2
x1 y1 x2 y2
x1 y1 x2 y2
x1 y1 x2 y2
'''
def writeToFile(fileName : str, text : str):
    with open(fileName, 'w', encoding="utf-8") as temp:
        temp.write(text)

def rightAround(a : float) -> int:
    if a < 0:
        a = a - 0.5
    else:
        a = a + 0.5
    return int(a)

# python program.py a b c d e f filename
#           0       1 2 3 4 5 6     7
# python pr.py 29 181 41 139 23 13 file

# Какая идея, такой и код... Костыльный=/
if __name__ == "__main__":

    a = int(sys.argv[1])
    b = int(sys.argv[2])
    c = int(sys.argv[3])
    d = int(sys.argv[4])
    e = int(sys.argv[5])
    f = int(sys.argv[6])

    dic = {}

    ri1 = e/2

    ri2 = f/2
    
    x, y, u, v =  fsolve(equations, (a-ri1, b-ri1, c-ri2, d-ri2))
    x = rightAround(x)
    y = rightAround(y)
    u = rightAround(u)
    v = rightAround(v)
    dic[f"{x} {y} {u} {v}"] = [x, y, u, v]

    x, y, u, v =  fsolve(equations, (a-ri1, b-ri1, c-ri2, d+ri2))
    x = rightAround(x)
    y = rightAround(y)
    u = rightAround(u)
    v = rightAround(v)
    dic[f"{x} {y} {u} {v}"] = [x, y, u, v]

    x, y, u, v =  fsolve(equations, (a-ri1, b-ri1, c+ri2, d-ri2))
    x = rightAround(x)
    y = rightAround(y)
    u = rightAround(u)
    v = rightAround(v)
    dic[f"{x} {y} {u} {v}"] = [x, y, u, v]

    x, y, u, v =  fsolve(equations, (a-ri1, b-ri1, c+ri2, d+ri2))
    x = rightAround(x)
    y = rightAround(y)
    u = rightAround(u)
    v = rightAround(v)
    dic[f"{x} {y} {u} {v}"] = [x, y, u, v]

    x, y, u, v =  fsolve(equations, (a-ri1, b+ri1, c-ri2, d-ri2))
    x = rightAround(x)
    y = rightAround(y)
    u = rightAround(u)
    v = rightAround(v)
    dic[f"{x} {y} {u} {v}"] = [x, y, u, v]

    x, y, u, v =  fsolve(equations, (a-ri1, b+ri1, c-ri2, d+ri2))
    x = rightAround(x)
    y = rightAround(y)
    u = rightAround(u)
    v = rightAround(v)
    dic[f"{x} {y} {u} {v}"] = [x, y, u, v]

    x, y, u, v =  fsolve(equations, (a-ri1, b+ri1, c+ri2, d-ri2))
    x = rightAround(x)
    y = rightAround(y)
    u = rightAround(u)
    v = rightAround(v)
    dic[f"{x} {y} {u} {v}"] = [x, y, u, v]

    x, y, u, v =  fsolve(equations, (a-ri1, b+ri1, c+ri2, d+ri2))
    x = rightAround(x)
    y = rightAround(y)
    u = rightAround(u)
    v = rightAround(v)
    dic[f"{x} {y} {u} {v}"] = [x, y, u, v]



    x, y, u, v =  fsolve(equations, (a+ri1, b-ri1, c-ri2, d-ri2))
    x = rightAround(x)
    y = rightAround(y)
    u = rightAround(u)
    v = rightAround(v)
    dic[f"{x} {y} {u} {v}"] = [x, y, u, v]

    x, y, u, v =  fsolve(equations, (a+ri1, b-ri1, c-ri2, d+ri2))
    x = rightAround(x)
    y = rightAround(y)
    u = rightAround(u)
    v = rightAround(v)
    dic[f"{x} {y} {u} {v}"] = [x, y, u, v]

    x, y, u, v =  fsolve(equations, (a+ri1, b-ri1, c+ri2, d-ri2))
    x = rightAround(x)
    y = rightAround(y)
    u = rightAround(u)
    v = rightAround(v)
    dic[f"{x} {y} {u} {v}"] = [x, y, u, v]

    x, y, u, v =  fsolve(equations, (a+ri1, b-ri1, c+ri2, d+ri2))
    x = rightAround(x)
    y = rightAround(y)
    u = rightAround(u)
    v = rightAround(v)
    dic[f"{x} {y} {u} {v}"] = [x, y, u, v]

    x, y, u, v =  fsolve(equations, (a+ri1, b+ri1, c-ri2, d-ri2))
    x = rightAround(x)
    y = rightAround(y)
    u = rightAround(u)
    v = rightAround(v)
    dic[f"{x} {y} {u} {v}"] = [x, y, u, v]

    x, y, u, v =  fsolve(equations, (a+ri1, b+ri1, c-ri2, d+ri2))
    x = rightAround(x)
    y = rightAround(y)
    u = rightAround(u)
    v = rightAround(v)
    dic[f"{x} {y} {u} {v}"] = [x, y, u, v]

    x, y, u, v =  fsolve(equations, (a+ri1, b+ri1, c+ri2, d-ri2))
    x = rightAround(x)
    y = rightAround(y)
    u = rightAround(u)
    v = rightAround(v)
    dic[f"{x} {y} {u} {v}"] = [x, y, u, v]

    x, y, u, v =  fsolve(equations, (a+ri1, b+ri1, c+ri2, d+ri2))
    x = rightAround(x)
    y = rightAround(y)
    u = rightAround(u)
    v = rightAround(v)
    dic[f"{x} {y} {u} {v}"] = [x, y, u, v]

    #x = rightAround(x)
    #y = rightAround(y)
    #u = rightAround(u)
    #v = rightAround(v)

    #time.sleep(3)

    #print(x, y, u, v)
    
    #print(dic)
    S = ""
    S += f"{len(dic)}\n"
    for item in dic:
        S += f"{item}\n"
    writeToFile(sys.argv[7], S)

