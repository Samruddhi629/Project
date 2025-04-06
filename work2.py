import numpy as np

f=open("py.txt","r")
data=f.read()

data_lower=data.lower()

words=data_lower.split()
word_number = {}
word_count = {}
number_word = []


for word in words:
    if word not in word_number:
        word_number[word] = len(word_number) + 1
        word_count[word] = 0  
    word_count[word] += 1
    
    number_word.append(word_number[word])


number_word1 = np.array(number_word)
print(number_word1)

print("Word | Number | Frequency")
for word in word_number:
    print(f"{word} | {word_number[word]} | {word_count[word]}")

