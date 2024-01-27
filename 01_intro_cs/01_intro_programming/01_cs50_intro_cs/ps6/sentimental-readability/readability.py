def main():
    # Prompt the user for a text
    text = input("Text: ")

    # Count letters in text
    letter_num = count_letters(text)

    # Count words in text
    word_num = count_words(text)

    # Count sentences in text
    sentence_num = count_sentences(text)

    # Calculate Coleman-Liau index
    index = calculate_index(letter_num, word_num, sentence_num)

    # Print output
    pr_grade(index)


def count_letters(text):
    count_letter = 0

    for i in range(len(text)):
        letter = text[i].upper()
        if ord(letter) >= 65 and ord(letter) <= 90:
            count_letter += 1

    return count_letter


def count_words(text):
    count_word = 1

    for i in range(len(text)):
        if ord(text[i]) == 32:
            count_word += 1

    return count_word


def count_sentences(text):
    count_sentence = 0

    for i in range(len(text)):
        if ord(text[i]) == 46 or ord(text[i]) == 33 or ord(text[i]) == 63:
            count_sentence += 1

    return count_sentence


def calculate_index(letter_num, word_num, sentence_num):
    L = letter_num / word_num * 100
    S = sentence_num / word_num * 100

    return int(round(0.0588 * L - 0.296 * S - 15.8))


def pr_grade(index):
    if (index < 1):
        print("Before Grade 1")
    elif (index >= 16):
        print("Grade 16+")
    else:
        print(f"Grade {index}")


if __name__ == "__main__":
    main()
