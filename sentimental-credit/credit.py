from cs50 import get_int

while True:
    num = get_int("Number: ")
    if num > 0:
        break

digits = len(str(num))
first_two_digits = int(str(num)[:2])
sum = 0
tmp_num = num

for i in range(digits):
    tmp = tmp_num % 10
    if (i + 1) % 2 != 0:
        sum += tmp
    else:
        tmp *= 2
        if tmp > 9:
            sum += tmp % 10
            sum += tmp // 10
        else:
            sum += tmp
    tmp_num //= 10

if sum % 10 == 0:
    if digits == 15 and (first_two_digits == 34 or first_two_digits == 37):
        print("AMEX")
    elif digits == 16 and 50 < first_two_digits < 56:
        print("MASTERCARD")
    elif (digits == 13 or digits == 16) and 39 < first_two_digits < 50:
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")
