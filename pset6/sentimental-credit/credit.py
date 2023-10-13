# TODO
number = 0

while number < 1:
    number = input("number: ")
    try:
        number = int(number)
    except:
        number = 0