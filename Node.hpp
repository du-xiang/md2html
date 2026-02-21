#pragma once

#include <iostream>
#include <vector>

enum class NodeType {
    document,       // 根节点
    paragraph,      // 段落
    header,         // 标题
    codeBlock,      // 代码块
    codeLine,       // 代码行
    mathBlock,      // 数学块
    mathLine,       // 数学行
    quote,          // 引用
    listContainer,  // 列表容器
    orderList,      // 有序列表
    unorderList,    // 无序列表
    lineBreak,      // 分割线
};

class Node {
private:

public:
    NodeType nodeType;          // 结点类型
    std::string contents;       // 结点包含的文本内容
    size_t layer;         // 结点在解析树中的层数（从0开始）
    size_t level;         // 存放标题、列表、引用的层级
    std::vector<Node> children; // 存放此结点包含的下层子结点

    Node() = default;
    Node(NodeType type);
    ~Node() = default;
    bool set_node_type(NodeType type);
    bool set_node_layer(size_t l);
    bool set_node_level(size_t l);
    bool set_node_contents(std::string c);

};

inline Node::Node(NodeType type) {
    nodeType = type;
}

inline bool Node::set_node_type(NodeType type) {
    nodeType = type;
    return true;
}

inline bool Node::set_node_layer(size_t l) {
    layer = l;
    return true;
}

inline bool Node::set_node_level(size_t l) {
    level = l;
    return true;
}

inline bool Node::set_node_contents(std::string c) {
    contents = c;
    return true;
}
