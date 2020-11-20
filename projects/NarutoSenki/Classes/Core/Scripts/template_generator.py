import os

temp = '''#pragma once
#include "Hero.hpp"

class %s : public Hero
{
    void perform()
    {
    %s
    }
};
'''

root = os.path.dirname(__file__)
src = root+'/AI.hpp'
print("Hpp source ->", src)

names = []
with open(src, 'r') as fs:
    names = fs.readlines()

for name in names:
    if name == '' or not name.startswith('#include'):
        continue
    name = name.split(' ')[1].replace('"', '').replace('\n', '')
    print(name)

    path = os.path.join(root, name)
    if os.path.exists(path):
        print("Exit file ->", path)
        continue
    else:
        class_name = name.replace('.hpp', '')
        with open(path, 'w') as fs:
            # fs.write(temp % (class_name, class_name, ''))
            fs.write(temp % class_name, '')
