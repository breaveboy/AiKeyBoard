from PySide6.QtCore import QObject, Signal
from openai import OpenAI
# 提示词
SystemPrompt1 = {
 
    "CODE_OPTIMIZATION": {
      "title": "代码优化",
      "system_role": "你是一位拥有20年经验的资深嵌入式全栈工程师，精通Clean Code和算法优化。请对用户提供的代码进行深度分析，识别冗余逻辑、性能瓶颈和不规范写法。",
      "user_prefix": "请分析并优化以下代码。要求：1.提供优化后的代码；2.详细说明修改点；3.分析优化后的时间与空间复杂度变化：\n\n"
    },
    "AUXILIARY_UNDERSTANDING": {
      "title": "辅助理解",
      "system_role": "你是一位极具耐心的技术导师，擅长化繁为简。请用通俗易懂的语言解释复杂的逻辑，帮助初学者快速掌握核心原理。",
      "user_prefix": "请像讲课一样解释这段代码。要求：先概述主要功能，再分步骤拆解核心逻辑，最后说明涉及的关键技术或设计模式：\n\n"
    },
    "ERROR_ANALYSIS": {
      "title": "报错分析",
      "system_role": "你是一位精通全栈开发的调试专家，拥有极强的Bug定位能力。请根据用户提供的报错信息和代码段，准确指出问题的根本原因。",
      "user_prefix": "请诊断以下报错。要求：1.详细解释错误原因；2.给出具体的修复代码方案；3.提供预防此类错误的编程建议：\n\n"
    },
    "DOC_COMMENT": {
      "title": "文档注释",
      "system_role": "你是一位严谨的技术文档工程师。请为用户提供的代码添加高质量、标准化的文档注释。",
      "user_prefix": "请为以下代码添加注释。要求：1.遵循该编程语言的标准文档规范（如JSDoc, Google Python Style等）；2.包含功能、参数、返回值及可能抛出的异常说明：\n\n"
    }
}
SystemPrompt = {

    "CODE_OPTIMIZATION": {
        "system_role": "你是资深工程师，擅长代码优化。",
        "user_prefix": "优化代码，并输出：\n【代码】\n【修改点】\n【复杂度】\n\n"
    },

    "AUXILIARY_UNDERSTANDING": {
        "system_role": "你是技术讲师，擅长讲解代码。",
        "user_prefix": "解释代码：\n【功能】\n【流程】\n【关键点】\n\n"
    },

    "ERROR_ANALYSIS": {
        "system_role": "你是调试专家。",
        "user_prefix": "分析报错：\n【原因】\n【修复】\n【建议】\n\n"
    },

    "DOC_COMMENT": {
        "system_role": "你负责写代码注释。",
        "user_prefix": "添加标准注释（含参数/返回/异常）：\n\n"
    }
}


# ================= AI 助手类 =================
class DeepSeekAssistant(QObject):
    ai_response_signal = Signal(str)

    def __init__(self, api_key,base_url):
        super().__init__()
        """
        初始化 AI 助手
        :param api_key: DeepSeek API Key
        :param base_url: DeepSeek API Base URL
        """
        self.client = OpenAI(api_key=api_key, base_url=base_url)
        # 默认代码优化角色
        self.default_prompt=SystemPrompt["CODE_OPTIMIZATION"]
        self.current_prompt = self.default_prompt
        self.messages = [
            {
                "role": "system", 
                "content": str(self.default_prompt) #字符串
            }
        ]
    
    # 切换用户角色
    def change_prompt(self, prompt):
        """
        切换用户角色
        :param prompt: 新的提示词
        """
        self.current_prompt = prompt
        self.messages = [
            {
                "role": "system", 
                "content": str(prompt) #字符串
            }
        ]
        
    def ask_ai(self, user_content):
        """
        发送消息给 AI 并发出信号
        """
        print(f"\n[AI 正在思考中...]")
        # 检查当前提示词是否包含 user_prefix
        if hasattr(self, 'current_prompt') and 'user_prefix' in self.current_prompt:
            user_content = self.current_prompt['user_prefix'] + user_content
        # 否则使用默认提示词的 user_prefix
        elif 'user_prefix' in self.default_prompt:
            user_content = self.default_prompt['user_prefix'] + user_content
        
        self.messages.append({"role": "user", "content": user_content})
        
        try:
            response = self.client.chat.completions.create(
                model="deepseek-chat",
                messages=self.messages,
                stream=True  # 启用流式输出
            )
            
            full_response_content = ""
            for chunk in response:
                if chunk.choices and chunk.choices[0].delta.content is not None:
                    content = chunk.choices[0].delta.content
                    full_response_content += content
                    self.ai_response_signal.emit(content)  # 每次接收到内容就发出信号
            
            # 将完整的回复存入历史以保持上下文
            self.messages.append({"role": "assistant", "content": full_response_content})
            
        except Exception as e:
            error_message = f"\n[错误] API 调用失败: {e}"
            print(error_message)
            self.ai_response_signal.emit(error_message)