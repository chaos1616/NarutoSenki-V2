import re
import os

source = """
"""

match = r'void Hero::(\w+)\(\)\n{(.*)}\n*void'

results = source.split("""}

void""")

for result in results:
    match = re.search(r'Hero::(.*)\(', result, re.I)
    if match is None:
        continue
    path = os.path.dirname(__file__)+'/'+match[1]+'.hpp'
    with open(path, 'a') as fs:
        result = result.replace(match[0][:-1], 'void '+match[1]+"_Impl::performRule") +'}\n'
        if result[0] == ' ':
            result = '\n'+result[1:]
        fs.write(result)
    print(result, '}\n\n', sep='')
