import os
from pathlib import Path

_env_path = Path(__file__).with_name(".env")

# 判断路径是否存在
if _env_path.exists():
    for line in _env_path.read_text().splitlines():
        line = line.strip()
        if not line or line.startswith("#") or "=" not in line:
            continue
        key, value = line.split("=", 1)
        os.environ[key.strip()] = value.strip()

# 获取环境变量
key_api=os.getenv("DEEPSEEK_API_KEY","")
base_url=os.getenv("DEEPSEEK_BASE_URL","https://api.deepseek.com")
if not key_api:
    raise RuntimeError("缺少 DEEPSEEK_API_KEY，请在 AiKey-Hub/.env 中配置")

