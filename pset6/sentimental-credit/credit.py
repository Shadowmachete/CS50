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
    if i % 2 == 0:
        checksum += 2 * int(number[i])
    else:
        checksum += int(number[i])

if (checksum % 10 == 0) && (len(number) > )