#pragma once

#include <iostream>
#include <vector>

enum class NodeType {
    document,       // 根节点
    paragraph,      // 段落
    header,         // 标题
    codeBlock,      // 代码块
    mathBlock,      // 数学块
    quote,          // 引用
    listContainer,  // 列表容器
    orderList,      // 有序列表
    unorderList,    // 无序列表
    lineBreak,      // 分割线
};

class Node {
private:

public:
    NodeType nodeType;
    std::string contents;
    std::vector<Node> children;

    Node() = default;
    Node(NodeType type);
    ~Node() = default;
    bool set_node_type(NodeType type);
    bool set_node_contents(std::string c);

};

inline Node::Node(NodeType type) {
    nodeType = type;
}

inline bool Node::set_node_type(NodeType type) {
    nodeType = type;
    return true;
}

inline bool Node::set_node_contents(std::string c) {
    contents = c;
    return true;
}