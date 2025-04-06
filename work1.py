import numpy as np

f=open("py.txt","r")
data=f.read()

data_lower=data.lower()

words=data_lower.split()

word_number={}               #{"hello":1}
number_word=[]               #[1]

for word in words:                            
    if word not in word_number:                #check if word is already there
        word_number[word]=len(word_number)+1   #len gives no of key value pair
    number_word.append(word_number[word])      #[1,2,3,4,5] appending each value
        
number_word1=np.array(number_word)

print(words)

print("Words to Numbers", number_word1)
        

