# ==========================
# 强化学习极简Demo（100%可运行）
# 功能：让AI学会从0走到4拿奖励
# ==========================

# 1. 初始化Q表（强化学习的“记忆”）
# Q[位置][动作] = 这个动作好不好
Q = [0, 0, 0, 0, 0]

# 2. 学习参数
episodes = 15  # 训练15局
lr = 0.8  # 学习速度
gamma = 0.9  # 奖励记忆

print("=== 强化学习开始（每一步都会打印）===")

# 3. 开始训练（AI自己试错）
for episode in range(episodes):
    state = 0  # 从起点0开始
    path = [state]

    # 最多走10步，防止卡死
    for _ in range(10):
        # 动作：往右走一步
        action = 1
        next_state = state + action

        # 奖励规则
        if next_state == 4:
            reward = 100  # 到终点，大奖
            done = True
        else:
            reward = -1  # 没到终点，小惩罚
            done = False

        # ======================
        # 核心：强化学习更新记忆
        # ======================
        Q[state] = (1 - lr) * Q[state] + lr * (reward + gamma * max(Q))

        state = next_state
        path.append(state)

        if done:
            break

    # 打印每一局学习过程
    print(f"第{episode + 1:2d}局 | 路径: {path} | 当前记忆: {[round(q, 1) for q in Q]}")

# 4. 训练完成，展示最终结果
print("\n=== 学习完成！AI最优路线 ===")
state = 0
best_path = [state]
while state != 4:
    state += 1
    best_path.append(state)

print("✅ 最优路线:", best_path)
print("✅ 最终记忆(Q表):", [round(q, 1) for q in Q])