import sys

line = input().split()
rule_count = int(line[0])
def_action = line[1]

rules = [(0, 0, def_action)]

def ip2num(ip):
    res = 0
    s = ip.split(".")
    for i in range(len(s)):
        res <<= 8
        res += int(s[i])
    return res

for _ in range(rule_count):
    line = input()
    rule = line.split()
    ip_desc = rule[0].split("/")
    
    ip = ip2num(ip_desc[0])
    subnet = 32 - int(ip_desc[1])
    action = rule[1]
    
    rules.insert(0, (ip >> subnet, subnet, action))
    
for ip in map(ip2num, sys.stdin):
    found = False
    for rule in rules:
        subnet = rule[1]
        if (ip >> subnet) == rule[0]:
            print(rule[2])
            found = True
            break
    if not found:
        print(def_action)