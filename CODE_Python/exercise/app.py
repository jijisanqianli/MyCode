from flask import Flask,request
import app_module
from app_module import add_todos,delete_todos

app = Flask(__name__)

@app.route('/todos', methods=['GET'])
def return_todos():
    return {"todos": app_module.todos}

@app.route('/todos', methods=['POST'])
def insert_todos():
    data = request.get_json()
    if data is None:
        return {"error": "请发送 JSON 数据"}, 400
    work_input = data.get("work", "")
    result = add_todos(app_module.todos, work_input)
    return {"message": result}, 201

@app.route('/todos/<int:index>', methods=['GET'])
def get_todo_by_index(index):
    if 0 <= index < len(app_module.todos):
        return {"todo": app_module.todos[index]}
    else:
        return {"error": "待办事项不存在"}, 404

print("模块加载成功，当前待办:", app_module.todos)

@app.route('/todos/<int:index>', methods=['DELETE'])
def delete_todo_by_index(index):
    result = delete_todos(app_module.todos,index)
    return {"message": result}, 201

if __name__ == '__main__':
    app.run(debug=True)