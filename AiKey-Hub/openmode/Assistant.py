import time
import os
import sys
from openai import OpenAI

class DeepSeekAssistant:
    def __init__(self, api_key, initial_code=""):
        """
        初始化 AI 助手
        :param api_key: DeepSeek API Key
        :param initial_code: 初始选中的代码或文本
        """
       
        self.client = OpenAI(api_key=api_key, base_url="https://api.deepseek.com")
        # 初始化消息列表（上下文管理）
        self.messages = [
            {
                "role": "system", 
                "content": "你是一个AI助手，专门负责代码优化、翻译和总结。请根据用户提供的文本给出专业的改进建议。"
            }
        ]
        
        # 如果有初始选中的文本，立即将其作为第一个任务放入上下文
        if initial_code:
            self.messages.append({
                "role": "user", 
                "content": f"以下是我选中的内容，请先帮我分析并给出优化建议：\n\n{initial_code}"
            })

    def get_total_messages(self, user_content=None):
        """
        核心方法：传入新消息，返回总的消息列表
        :param user_content: 用户输入的字符串。如果是第一次运行且不传参数，则针对初始代码进行分析。
        :return: 完整的 messages 列表
        """
        # 1. 如果有新输入，则添加到对话历史
        if user_content:
            self.messages.append({"role": "user", "content": user_content})
        
        # 2. 调用模型获取回复
        try:
            response = self.client.chat.completions.create(
                model="deepseek-chat",
                messages=self.messages
            )
            
            # 3. 获取助手回复并存入历史
            assistant_msg = response.choices[0].message
            # 兼容处理：将助手消息对象转为字典存入列表
            self.messages.append({
                "role": "assistant", 
                "content": assistant_msg.content
            })
            
        except Exception as e:
            error_msg = f"API调用失败: {str(e)}"
            print(error_msg)
            # 将错误信息也存入列表，方便上位机显示
            self.messages.append({"role": "assistant", "content": error_msg})

        # 4. 返回总的消息列表
        return self.messages

            
            

   