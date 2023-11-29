from PIL import Image


def process(filename):
    img = Image.open(filename)
    ans = []
    for row in range(4):
        starty = row * 8
        for block in range(10):
            part = []
            x = block * 6
            for col in range(6):
                d = 0
                y = starty
                for i in range(8):
                    pixel = img.getpixel((x,y))
                    if pixel[0] < 128:
                        d += 1
                    d *= 2 # this is basically bitshift right
                    y += 1
                x += 1
                part.append('0x' + format(d//2, '02x'))
            ans.append(part)
    return ans

data = [[],[],[],[]]
for i in range(1,4):
    filename = f'hk{i}r.jpg'
    ans = process(filename)
    data[0] += ans[0:10]
    data[1] += ans[10:20]
    data[2] += ans[20:30]
    data[3] += ans[30:40]

for i, item in enumerate(data):
    print(f'\n\n{i}: {len(item)}')
    for j in item:
        print(", ".join(j)+',')
