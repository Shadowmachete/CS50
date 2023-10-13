# TODO
max_height = 8
height = 0

while height < 1 or height > max_height:
    height = input("Height: ")
    try:
        height = int(height)
    except:
        height = 0

for layer in range(height):
    for _ in range(height - layer - 1):
        print(" ", end = "")
    for _ in range(layer + 1):
        print("#", end = "")
    print("  ", end = "")
    for _ in range(layer + 1):
        print("#", end = "")
    print()