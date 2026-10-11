# 手册重建

构建数据以`catalog.json`为发布版快照：包含完整板子、独立例题、接口、复杂度、来源与实际用例。原始生成模块仅用于维护某个知识点；执行生成模块后需重新核实内容，不能盲目覆盖全部目录。

## 本地重建

需要Python 3.12、g++（C++17）、ReportLab、pypdf、Pillow、Poppler。排版使用Windows的仿宋、黑体与Consolas；其他平台请在build_pdf.py中指定可用的中文及等宽字体。

```text
python verify_all.py
python verify_templates.py
python verify_random.py
python build_pdf.py
python verify_pdf.py
```

从本目录运行上述命令。`verify_pdf.py`可用环境变量PDFTOPPM指定pdftoppm路径。渲染图在`tmp/pdfs`，PDF在`output/pdf`。

代码片段需组合模板编译。`combined_body`保存各例题经过变体修改后的实际依赖。`format_code.py`需要clang-format；样例验证对非唯一输出题不会盲目与官方示例逐字比较。

发布版的验证结果在`验证摘要.json`，没有写入机器的绝对临时路径。原站核实索引在`verified_sources.json`；缓存文件留在本地工作目录，不上传。
