# addqt2vs
将vs工程转化为qt工程(注入qt属性)

## 使用说明(user guide)
支持单工程、多工程(按目录递归)，详情可在命令行模式下输入“addqt2vs -h”查看使用帮助

## 三方库（third party）
- boost，170版本，暂支持vc140版本
- pugixml

## 废弃声明
将vs转Qt项目应属于构建框架的支持功能（如cmake已经有具体方案），且随着Vs的更新需要适配，所以不再维护及更新。