import random 

dna_base = ['A', 'C', 'G', 'T']

def create_file_text(i):
    f = open("text_{}.txt".format(i), 'w+')
    for i in range(0, (i+1)*20000):
        rand = random.randint(0, 3)
        text = dna_base[rand]
        f.write(text)
    f.close()

def generate_text():
    for i in range(0, 51):
        print("creating text_{}.txt ....".format(i))
        create_file_text(i)

def create_file_pattern(i):
    fin = open("text_{}.txt".format(i))
    fout = open("pattern_{}.txt".format(i), 'w+')

    for j in range(0, 2):
        fin.seek(random.randint(0, (i+1)*20000))
        pattern = fin.read(8)
        fin.seek(0)
        
        res = [pattern[k: l] for k in range(0, len(pattern)) for l in range(k+5+1, len(pattern) + 1)]
        for pattern in res:
            fout.write(pattern)
            fout.write("\n")

def generate_pattern():
    for i in range(0, 51):
        print("creating pattern_{}.txt ....".format(i))
        create_file_pattern(i)

if __name__ == "__main__":
    generate_text()
    generate_pattern()