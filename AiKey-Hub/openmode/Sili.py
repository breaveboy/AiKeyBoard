from openai import OpenAI
import sys

# 优化API客户端配置
client = OpenAI(
    api_key="sk-xsyhjjdjfgvulkockkvwfyyazswtsgrxsefjhykirhbdwsxh",
    base_url="https://api.siliconflow.cn/v1",
    timeout=15,  # 全局超时15秒
    max_retries=2  # 最多重试2次
)

# 使用更快的轻量级模型
response = client.chat.completions.create(
    model="Qwen/Qwen2.5-7B-Instruct",  # 更轻量级的模型，响应快
    messages=[
        {"role": "system", "content": "你是一个有用的助手"},
        {"role": "user", "content": "你好，请介绍一下你自己"}
    ],
    stream=True,
    temperature=0.7,
    top_p=0.9,
    max_tokens=512  # 限制响应长度，减少生成时间
)

# 实时打印流式响应
for chunk in response:
    if chunk.choices[0].delta.content:
        print(chunk.choices[0].delta.content, end='', flush=True)
        
print()  # 输出换行