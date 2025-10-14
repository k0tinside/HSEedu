from math import log2

def Alphabet(d, codes, p):
    N = len(d)
    if N == 1:
        codes[d[0][0]] = p
        # print(f"Присвоим код: {d[0][0]} --> {p}")

    else:
        i = N - 1
        j = 0
        arrL = [d[j]]
        arrR = [d[i]]
        summL = d[j][1]
        summR = d[i][1]
        while j + 1 < i:
            if summL > summR:
                i -= 1
                summR += d[i][1]
                arrR.append(d[i])
            else:
                j += 1
                summL += d[j][1]
                arrL.append(d[j])
        Alphabet(arrL, codes, p + '0')
        Alphabet(arrR, codes, p + '1')

    return codes


def Coding(c, mes):
    n = len(mes)
    setSymbs = set(mes)
    symbsMap = sorted([(el, mes.count(el) / n) for el in setSymbs], key=lambda x: (-x[1], x[0])) # key - частота

    line = ''
    for el in mes:
        line += c[el]

    return line


def Encoding(c, mes):
    reversedCodes = {v: k for k,v in c.items()}
    line = ''
    tmp = ''
    for i in range(len(mes)):
        tmp += mes[i]
        if tmp in reversedCodes:
            line += reversedCodes[tmp]
            tmp = ''

    return line

# символ - вероятность - длина кодового слова

def H(arr):
    return sum([-(p * log2(p)) for s, p, l in arr])

def Dist(arr):
    Hmax = log2(len(arr))
    return ((Hmax - H(arr)) / Hmax)


def Dcode(arr):
    L = sum([p * l for s, p, l in arr])
    return ((L - H(arr)) / L)


with open("input.txt", "r", encoding="windows-1251") as f:
    text = f.read()
    n = len(text)
    setSymbs = set(text)
    symbsArr = sorted([(el, text.count(el) / n) for el in setSymbs], key=lambda x: (-x[1], x[0])) # key - частота
    symbsMap = dict(symbsArr)
    codes = Alphabet(symbsArr, dict(), '')
    general = [(k, symbsMap[k], len(v)) for k,v in codes.items()]
    print(general)


with open("codes.txt", "w", encoding="utf-8") as f:
    for k, v in codes.items():
        if k == '\n':
            display = '\\n'
        elif k == ' ':
            display = '[space]'
        elif k == '\t':
            display = '\\t'
        else:
            display = k
        f.write(f"{display}: {v}\n")

# избыточность кода и источника
with open(f"Dist={str(Dist(general))},Dcode={str(Dcode(general))}.txt", "w", encoding="utf-8") as f:
    f.write(Coding(codes, text))