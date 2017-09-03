import sys
keys = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./"
s = ""
for line in sys.stdin:
	for c in line:
		if c == " ":
			s += " "
		elif c == "\n":
			s += "\n"
		else:
			s += keys[keys.index(c) - 1]
print(s, end="")
