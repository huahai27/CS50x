from cs50 import get_string


def main():
    text = get_string("Text: ")

    W = compute_words(text)
    L = compute_letters(text) * 100.0 / W
    S = compute_sentences(text) * 100.0 / W

    index = 0.0588 * L - 0.296 * S - 15.8

    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        tmp = round(index)
        print(f"Grade {tmp}")


def compute_letters(text):
    ret = 0
    length = len(text)

    for i in range(length):
        if text[i].isalnum():
            ret += 1

    return ret


def compute_words(text):
    ret = 0
    length = len(text)

    for i in range(length):
        if text[i].isspace():
            ret += 1
    ret += 1

    return ret


def compute_sentences(text):
    ret = 0
    length = len(text)

    for i in range(length):
        if text[i] in [".", "?", "!"]:
            ret += 1

    return ret


main()
