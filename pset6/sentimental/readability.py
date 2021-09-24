from cs50 import get_string


def main():
    s = get_string("Text: ")
    
    s_count = s.count(".") + s.count("?") + s.count("!")
    w_count = len(s.split(" "))
    c_count = 0
    for c in s:
        if c.isalpha():
            c_count += 1
    L = (c_count / w_count) * 100
    S = (s_count / w_count) * 100
    grade = int(round((0.0588 * L) - (0.296 * S) - 15.8, 0))
    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


if __name__ == "__main__":
    main()
