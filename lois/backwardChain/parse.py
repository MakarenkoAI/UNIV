import re

FactPattern = r"[A-Z]+([1-9][0-9]*)*={(<[a-z]+([1-9][0-9]*)*,(0(\.\d+)?|1(\.0+)?)>)(?:,<[a-z]+([1-9][0-9]*)*,(0(\.\d+)?|1(\.0+)?)>)*}|{}"
RulePattern = r"[A-Z]+([1-9][0-9]*)*={(<<[a-z]+([1-9][0-9]*)*,[a-z]+([1-9][0-9]*)*>,(0(\.\d+)?|1(\.0+)?)>)(?:,<<[a-z]+([1-9][0-9]*)*,[a-z]+([1-9][0-9]*)*>,(0(\.\d+)?|1(\.0+)?)>)*}|{}"
file_name = 'input.txt'

def parse():
    usedFactNames = set()
    fact_list = []
    rule_list = []
    
    with open(file_name, 'r') as file:
        content = file.readlines()

        for line in content:
            line = line.strip()
            line = re.sub(r',0>', ',0.0>', line)
            line = re.sub(r',1>', ',1.0>', line)
            usedVariableNames = []
            match = re.fullmatch(FactPattern, line)
            if match:
                fact_name = match.group().split('=')[0].strip()
                if fact_name in usedFactNames:
                    print(f"Fact name '{fact_name}' is already used. Skipping...")
                    continue

                usedFactNames.add(fact_name)

                values = re.findall(r"<([a-z]+([1-9][0-9]*)*),((?:0\.\d+)|(?:1(?:\.0+)?))>", match.group())

                result = [fact_name, [[value[0], float(value[2])] for value in values]]
                fact_list.append(result)
            else:
                match = re.fullmatch(RulePattern, line)

                if match:
                     rule_name = match.group().split('=')[0].strip()
               
                     if rule_name in usedFactNames:
                        print(f"Fact name '{rule_name}' is already used. Skipping...")
                        continue

                     usedFactNames.add(rule_name)

                     values = re.findall(r"<<([a-z]+([1-9][0-9]*)*),([a-z]+([1-9][0-9]*)*)>,((?:0\.\d+)|(?:1(?:\.0+)?))>", match.group())

                     result = [rule_name, [[value[0],value[2], float(value[4])] for value in values]]
                     rule_list.append(result)
                else:
                    print(f"Line '{line}' is NOT in the correct format.")
                    
    return [fact_list, rule_list]
