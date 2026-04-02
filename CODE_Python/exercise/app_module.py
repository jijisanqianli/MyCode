todos=[]

def judge_done(todo):
    if todo["done"]==False:
        return "[ ]"
    if todo["done"]==True:
        return "[√]"

def show_todos(todos):
    if todos == []:
        return "暂无待办"
    else:
        return todos

def change_done(todos,index):
    if not todos:
        return "暂无待办"
    else:
        try:
            num=int(index)
        except:
            return "数据错误"
        if 1<=num<=len(todos):
            if todos[num-1]["done"]==True:
                todos[num-1]["done"]=False
            else :
                todos[num-1]["done"]=True
                return "修改成功"
        else:
            return "不存在序号"

def add_todos(todos,work_input):
    work = work_input.strip()
    if work:
        todo = {
            "title": work,
            "done": False,
        }
        todos.append(todo)
        return f"已添加事项:{work}"
    else:
        return "待办事项不能为空"

def delete_todos(todos,index):
    if not todos:
        return "暂无待办"
    else:
        try:
            num=int(index)
        except:
            return "数据错误"
        if 0<=num<len(todos):
            todos.pop(num)
            return "删除成功"
        else:
            return "不存在索引"