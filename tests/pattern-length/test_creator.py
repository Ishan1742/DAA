import random 

dna_base = ['A', 'C', 'G', 'T']

def create_file_text():
    f = open("text_0.txt", 'w+')
    for i in range(0, 500000):
        rand = random.randint(0, 3)
        text = dna_base[rand]
        f.write(text)
    f.close()

def generate_text():
    print("creating text_0.txt ....")
    create_file_text()

def create_file_pattern(i):
    fin = open("text_0.txt")
    fout = open("pattern_{}.txt".format(i), 'w+')

    for j in range(0, 100):
        fin.seek(max(0, random.randint(0, 200000) - 200))
        pattern = fin.read((i+1)*2)
        fin.seek(0)
        
        fout.write(pattern)
        fout.write("\n")

def generate_pattern():
    for i in range(2, 51):
        print("creating pattern_{}.txt ....".format(i))
        create_file_pattern(i)

if __name__ == "__main__":
    generate_text()
    generate_pattern()