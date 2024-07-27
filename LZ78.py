# LZ78 implementation
# Université de Fribourg, Suisse
# AUTHOR: Noé Zufferey - noe.zufferey@gmail.com
# CREATION: april 2018 
# USAGE: python3 LZ78.py '<string to encode>'

import sys

def compress(data):
    comp_data = []
    dictionnary = ['']
    word = ''
    i = 0
    for char in data:
        i += 1
        word += char
        if not word in dictionnary:
            dictionnary.append(word)
            comp_data.append([dictionnary.index(word[:-1]), word[-1]])
            word = ''
        elif i == len(data):
            comp_data.append([dictionnary.index(word)])
            word = ''
    return comp_data

def add_zeros(code, nbr):
    pre = ''
    i = 0
    while i < nbr - len(code):
        pre += '0'
        i += 1
    return pre + code

def to_bits(data, h=False):
    len_ind = 1
    result = ''
    first_round = True
    for word in data:
        if not first_round:
            pre = add_zeros(bin(word[0])[2:], len_ind)
            result += pre
            len_ind = len(pre)
            if h and (word[1] != '') : result += ','
        else:
            first_round = False
        
        next_char = add_zeros(bin(ord(word[1]))[2:], 8) if not (word[1] == '') else ''
        result += next_char
        if h : result += '|'
    return result

if __name__ == '__main__':
    with open('freq17_320ver.txt', 'r') as content_file:
        content = content_file.read()
    
    comp_data = compress(content)
    comp_data = str(comp_data)
    f= open("freq17_com.txt","w+")
    print(comp_data[3])
    for i in range(len(comp_data)):
        #To ignore [ , '
        
        if comp_data[i] != "[":
            if comp_data[i] != ",":
                if comp_data[i] != "'":
                    if comp_data[i] != " ":
                        f.write(comp_data[i])
    #print(comp_data)
    #print(to_bits(comp_data, True))
    #print(to_bits(comp_data))
