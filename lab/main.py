import matplotlib.pyplot as plt

def draw_the_curve():
    file = open('PAR.txt')  # 打开文档
    data = file.readlines()  # 读取文档数据
    linkrate = []  # 新建列表，用于保存第一列数据
    ave_lat = []  # 新建列表，用于保存第二列数据
    throughput = []

    for num in data:
        # split用于将每一行数据用空格分割成多个对象
        # 取分割后的第0列，转换成float格式后添加到linkrate列表中
        linkrate.append(float(num.split(' ')[0]))
        # 取分割后的第2列，转换成float格式后添加到ave_lat列表中
        ave_lat.append(float(num.split(' ')[1]))
        # 取分割后的第4列，转换成float格式后添加到throughput列表中
        throughput.append(float(num.split(' ')[2]))

    plt.figure()
    plt.title('ave_lat')
    plt.plot(linkrate, ave_lat, color='green', label='ave_lat')
    plt.xlabel('linkrate')
    plt.ylabel('ave_lat')
    plt.legend()  # 显示图例
    plt.savefig('ave_lat.jpg')

    plt.figure()
    plt.title('throughput')
    plt.plot(linkrate, throughput, color='red', label='throughput')
    plt.xlabel('linkrate')
    plt.ylabel('throughput')
    plt.legend()  # 显示图例
    plt.savefig('throughput.jpg')


    plt.show()

def draw_the_curve2():
    file = open('PARNoVirChn.txt')  # 打开文档
    data = file.readlines()  # 读取文档数据
    linkrate = []  # 新建列表，用于保存第一列数据
    ave_lat = []  # 新建列表，用于保存第二列数据
    throughput = []

    for num in data:
        # split用于将每一行数据用空格分割成多个对象
        # 取分割后的第0列，转换成float格式后添加到linkrate列表中
        linkrate.append(float(num.split(' ')[0]))
        # 取分割后的第2列，转换成float格式后添加到ave_lat列表中
        ave_lat.append(float(num.split(' ')[1]))
        # 取分割后的第4列，转换成float格式后添加到throughput列表中
        throughput.append(float(num.split(' ')[2]))

    plt.figure()
    plt.title('ave_lat')
    plt.plot(linkrate, ave_lat, color='green', label='ave_lat')
    plt.xlabel('linkrate')
    plt.ylabel('ave_lat')
    plt.legend()  # 显示图例
    plt.savefig('ave_lat2.jpg')

    plt.figure()
    plt.title('throughput')
    plt.plot(linkrate, throughput, color='red', label='throughput')
    plt.xlabel('linkrate')
    plt.ylabel('throughput')
    plt.legend()  # 显示图例
    plt.savefig('throughput2.jpg')


    plt.show()


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    draw_the_curve()
    draw_the_curve2()
