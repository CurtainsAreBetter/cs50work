from cs50 import get_int


def main():
    num = get_int("Number: ")
    if checksum(num):
        print(issuer(num))
    else:
        print("INVALID")


def checksum(cn):
    # turn into string and reverse
    cn = str(cn)[::-1]
    # loop through nums
    mulStr = ''
    adds = 0
    for i in range(len(cn)):
        # if i > 1 and i is odd
        if 0 < i and i % 2 == 1:
            n = int(cn[i]) * 2
            mulStr += str(n)
        else:
            adds += int(cn[i])
    mulSum = sum(map(int, mulStr))
    # 0 means false and we can just return logic statements so why not
    return (not (mulSum + adds) % 2)
    

def issuer(cn):
    cn = str(cn)
    cnl = len(cn)
    start = int(cn[:2])
    if start in [37, 34] and cnl == 15:
        # amex
        return "AMEX"
    elif cnl == 16 and start in range(51, 56):
        # MasterCard
        return "MASTERCARD"
    elif str(start)[0] == "4" and (cnl == 16 or cnl == 13):
        # visa
        return "VISA"
    else:
        # invalid
        return "INVALID"
  
    
if __name__ == "__main__":
    main()
