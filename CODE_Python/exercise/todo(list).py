import sys

def show_todos(todos):
    if todos == []:
        print("暂无待办")
    else:
        for i in range(len(todos)):
            print(f"{i+1}:{todos[i]}")
    input("按任意键继续...")
    sys.stdin.flush()

def show_menu():
    print("=== 待办管理系统 ===")
    print("1. 查看所有待办")
    print("2. 添加待办")
    print("3. 删除待办")
    print("4. 退出")

def add_todos(todos):
    while True:
        work = input("请输入待办事项：").strip()
        if work:
            todos.append(work)
            print(f"已添加事项:{work}")
            break
        else:
            print("待办事项不能为空")
    input("按任意键继续...")
    sys.stdin.flush()

def delete_todos(todos):
    if not todos:
        print("没有待办可删除")
        input("按任意键继续...")
        sys.stdin.flush()
    else:
        while True:
            try:
                num =int(input("请输入要删除的目标序号："))
                break
            except ValueError:
                print("请输入正确的数字！！！")
        if 1<=num<=len(todos):
            data = todos[num-1]
            todos.pop(num-1)
            print(f"已删除序号{num}的{data}")
            input("按任意键继续...")
            sys.stdin.flush()
        else:
            print("不存在该序号...")
            print("请重新输入...")
            input("按任意键继续...")
            sys.stdin.flush()
            return delete_todos(todos)

def main():
    todos=[]
    while True:
        show_menu()
        users_choice = input("请输入您的选择:")
        if users_choice == "1":
            show_todos(todos)
        elif users_choice == "2":
            add_todos(todos)
        elif users_choice == "3":
            delete_todos(todos)
        elif users_choice == "4":
            print("程序已结束...")
            break
        else:
            print("请输入正确的选项!!!")
            input("按任意键继续...")
            sys.stdin.flush()


if __name__ == "__main__":
    main()
