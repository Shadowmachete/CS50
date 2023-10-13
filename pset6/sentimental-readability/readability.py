# TODO
def count_letters(text):
    count = 0
    for i in text:
        if ord(i) >= 65 and ord(i) <= 122:
            count += 1
    return count

def count_words(text):
    count = 0
    for i in range(len(text)-1):
        if (text[i+1] == ' ' or text[i+1] == '.' or text[i+1] == ',' or text[i+1] == '!') and (text[i] != ' ' and text[i] != '.' and text[i] != ',' and text[i] != '!'):
            count += 1
    return count

def count_sentences(text):
    count = 0
    for i in text:
        if i == '.' or i == '!' or i == '?':
            count += 1
    return count

text = (input("Text: ")).strip()
numLetters = count_letters(text)
numWords = count_words(text)
numSentences = count_sentences(text)
L = (numLetters * 100.0) / numWords
S = (numSentences * 100.0) / numWords
grade = (0.0588 * L) - (0.296 * S) - 15.8
if (grade < 1):
    print("Before Grade 1")
elif (grade >= 16):
    print("Grade 16+")
else:
    print(f"Grade {int(round(grade))}")
