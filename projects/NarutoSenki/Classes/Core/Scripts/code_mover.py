import re
import os

source = """

"""

match = r'\"{(.*)}\n*void'

results = source.split('__begin ')[1:]

root = os.path.dirname(__file__)
src = root+'/'
newroot = root[:-2]+'Core/Shinobi/'

for result in results:
    _list = result.split('\n', 1)
    name = _list[0]
    body = _list[1]

    file = newroot + name + '.hpp'
    print(file, '[ %s ]' % os.path.exists(file))

    data = '''\n\tvoid setClone()
%s
''' % body

    with open(file, 'r') as fs:
        lines = fs.readlines()
        lines[-1] = data+lines[-1]
        print(lines[-1])
        data = lines
    with open(file, 'w') as fs:
        fs.writelines(data)
