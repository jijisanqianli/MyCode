import sys

def judge_done(item):
    if item["done"]==False:
        return "[ ]"
    if item["done"]==True:
        return "[√]"

def show_todos(todos):
    if todos == []:
        print("暂无待办")
    else:
        for i in range(len(todos)):
            print(f"{i+1}:"+judge_done((todos[i]))+f" {(todos[i])['title']}")
    input("按任意键继续...")
    sys.stdin.flush()

def change_done(todos):
    if not todos:
        print("没有待办可修改")
        input("按任意键继续...")
        sys.stdin.flush()
    else:
        while True:
            try:
                num =int(input("请输入要修改的目标序号："))
                break
            except ValueError:
                print("请输入正确的数字！！！")
        if 1<=num<=len(todos):
            print("该项为: "+judge_done((todos[num-1]))+f" {(todos[num-1])['title']}")
            print("是否进行修改? 1.是 2.否")
            while True:
                your_choice=input("请输入您的选项:")
                if your_choice=="1":
                    if todos[num-1]["done"]==True:
                        todos[num-1]["done"]=False
                    else:
                        todos[num-1]["done"]=True
                    print(f"目前该项为:{todos[num-1]['title']} {judge_done((todos[num-1]))}")
                    break
                elif your_choice=="2":
                    break
                else:
                    print("请输入正确选项！！！")
                    input("按任意键继续...")
                    sys.stdin.flush()
            input("按任意键继续...")
            sys.stdin.flush()
        else:
            print("不存在该序号...")
            print("请重新输入...")
            input("按任意键继续...")
            sys.stdin.flush()
            return change_done(todos)


def show_menu():
    print("=== 待办管理系统 ===")
    print("1. 查看所有待办")
    print("2. 添加待办")
    print("3. 删除待办")
    print("4. 修改待办完成情况")
    print("5. 退出")

def add_todos(todos):
    while True:
        work = input("请输入待办事项：").strip()
        if work:
            item = {
                "title": work,
                "done": False,
            }
            todos.append(item)
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
        if 1 <= num <= len(todos):
            print("该项为: " + judge_done((todos[num - 1])) + f" {(todos[num - 1])['title']}")
            print("是否进行删除? 1.是 2.否")
            while True:
                your_choice = input("请输入您的选项:")
                if your_choice == "1":
                    todos.pop(num-1)
                    print("该项已经删除")
                    break
                elif your_choice == "2":
                    break
                else:
                    print("请输入正确选项！！！")
                    input("按任意键继续...")
                    sys.stdin.flush()
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
            change_done(todos)
        elif users_choice == "5":
            print("程序已结束...")
            break
        else:
            print("请输入正确的选项!!!")
            input("按任意键继续...")
            sys.stdin.flush()


if __name__ == "__main__":
    main()