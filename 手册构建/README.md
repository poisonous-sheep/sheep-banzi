# 手册重建与维护

发布版以`catalog.json`为内容快照，按模板型、思维型、混合型组织。普通DP使用函数题解；原模板、原例题与v1手册保留。

## 重建当前合订版

需要Python 3.12+、支持C++17的g++、ReportLab、pypdf、Pillow、Poppler。字体为Windows仿宋、黑体、Consolas；跨平台在`pdf_layout.py`替换字体，`verify_pdf.py`可用环境变量`PDFTOPPM`指定渲染器。

在本目录执行：

```text
python verify_all.py
python verify_templates.py
python verify_random.py
python verify_training.py
python build_training_pdf.py
python verify_pdf.py
python verify_files.py
```

PDF在仓库`output/pdf`，全页渲染、联系图及代表页面在`tmp/pdfs`；需实际查看图片确认排版。测试产物在本地`.work_review`，不上传。

`full_code`保存函数版验证组合程序；`display_code`在需要SCC、Mobius、Comb等已有依赖时省略重复定义，源文件和README注明组合方式。模板型的`combined_body`保存例题变体。`verify_files.py`核对实际交付文件与编译程序及所有相对链接。

`training_notes.py`保存人工推导，修改后同步catalog相应字段。`make_training_docs.py`按实际验证记录生成索引；本地存在旧盘点清单时额外核对原笔记哈希。

## 历史脚本

原生成模块、`build_pdf.py`和旧整理脚本是v1流程，不要批量运行`regenerate.py`、`finalize.py`、`make_docs.py`覆盖v2。

`upgrade_training.py`仅为本次迁移脚本，需要维护者保存的v1 catalog快照与clang-format。日常维护直接修改当前catalog、推导与对应源文件，再运行上述检查。

公开验证摘要为`验证摘要.json`，原题核实记录为`verified_sources.json`。本地验证不等于在线AC；本版没有在线提交。
