def main():
    while True:
        try:
            credit_card_num = int(input("Number: "))
            break
        except ValueError:
            pass

    checksum(credit_card_num)


def checksum(number):
    remainder = number % 10
    quotient = number // 10
    length_card = 1
    even_number = 0
    odd_number = 0

    while quotient > 0:
        if length_card % 2 == 0:
            even_number += doubled_number(remainder)
        else:
            odd_number += remainder

        prev_remainder = remainder
        remainder = quotient % 10
        quotient = quotient // 10
        length_card += 1

    if length_card % 2 == 0:
        even_number += doubled_number(remainder)
    else:
        odd_number += remainder

    checksum_result = even_number + odd_number
    first_two_digit = remainder * 10 + prev_remainder

    check_print(checksum_result, first_two_digit, remainder, length_card)


def doubled_number(remainder):
    double_num = remainder * 2

    if double_num >= 10:
        rem = double_num % 10
        quo = double_num // 10
        double_num = rem + quo

    return double_num


def check_print(checksum_result, first_two_digit, remainder, length_card):
    result = "INVALID"

    if checksum_result % 10 == 0:
        if (length_card == 15) and ((first_two_digit == 34) or (first_two_digit == 37)):
            result = "AMEX"
        elif ((length_card == 13) or (length_card == 16)) and (remainder == 4):
            result = "VISA"
        elif (length_card == 16) and ((first_two_digit >= 51) and (first_two_digit <= 55)):
            result = "MASTERCARD"

    print(f"{result}")


if __name__ == "__main__":
    main()
