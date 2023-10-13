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
for i in range(-1, -len(number)-1, -1):
    print(i, checksum, number[i])
    if i % 2 == 0:
        checksum += 2 * int(number[i])
    else:
        checksum += int(number[i])

if (checksum % 10 == 0) and (len(number) >= 13) and (len(number) <= 18):
    firstTwo = number[0:2]
    if first[0] == '4':
        print("VISA")
    elif firstTwo == '34' or firstTwo == '37':
        print("AMEX")
    elif firstTwo == '51' or firstTwo == '52' or firstTwo == '53' or firstTwo == '54' or firstTwo == '55':
        print("MASTERCARD")
    else:
        print("INVALID")
else:
    print("INVALID")