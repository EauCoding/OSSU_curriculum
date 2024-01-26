while True:
    try:
        height = int(input("Height: "))

        if height >= 1 and height <= 8:
            break
    except ValueError:
        pass

for i in range(height):
    print(f"{' ' * (height - i - 1)}{'#' * (i + 1)}  {'#' * (i + 1)}")
