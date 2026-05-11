#获取鼠标选中的文本
# 发送给大模型
# 将大模型的回复
# 显示在上位机和对应的文本上

import time

from openai import OpenAI
import sys
import os
sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from main import data_text
print(f"当前全局变量 data_text: {data_text}")
deepseek_api="sk-6ceda58ad1e847ad9682988d218c8aa3"
client = OpenAI(api_key=deepseek_api, base_url="https://api.deepseek.com")

# 使用data_text作为用户消息
messages = [
    {"role": "system", "content": "你是一个AI助手，帮助用户优化代码。以下是用户选中的文本内容，请根据这些内容提供优化建议和改进方案。"},
    {"role": "user", "content": f"以下是我选中的内容，请先帮我分析并给出优化建议"}
    ]
response = client.chat.completions.create(
    model="deepseek-chat",
    messages=messages
)
assistant_message = response.choices[0].message
print(f"DeepSeek回复: {assistant_message.content}")
# 加入到消息列表中
messages.append(assistant_message)

# 先配置对应的AI代码优化的提示词，有AI优化，AI翻译，AI总结等功能
while True:
    #用户输入
    user_input = input("请输入您的问题或需要优化的代码: ")
    if user_input.lower() == "exit":
        break
    messages.append({"role": "user", "content": user_input})
    response = client.chat.completions.create(
        model="deepseek-chat",
        messages=messages
    )
    assistant_message = response.choices[0].message
    print(f"DeepSeek回复: {assistant_message.content}")
    messages.append(assistant_message)
    time.sleep(0.5)
    


