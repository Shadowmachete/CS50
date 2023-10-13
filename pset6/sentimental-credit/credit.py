# TODO
number = 0

while number < 1:
    number = input("number: ")
    try:
        number = int(number)
    except:
        number = 0
number = str(number)
checksum = 0
for i in range(len(number), ):
    if i % 2 == 1:
        checksum += 2 * number[i];