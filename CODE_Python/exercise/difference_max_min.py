def difference_max_min(list_nums):
    # 在此处编写代码
    min_num=list_nums[0]
    max_num=list_nums[0]
    for i in list_nums:
        if i>max_num:
            max_num=i
        if i<min_num:
            min_num=i
    return max_num,min_num

# 输入整数，并将其转换为列表
numbers = list(map(int, input().split()))

# 调用函数
print(difference_max_min(numbers))