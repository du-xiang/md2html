#pragma once

#include <fstream>

#include "Node.hpp"


class Parser {
private:
    std::ifstream m_file;

public:
    Node rootNode;
    bool spaceLine;                 // 判断上一行是否是空行

    Parser() = delete;
    Parser(std::string mdFilename);
    ~Parser();
    Node parsing();
    bool bolckSwitch(std::string& line, Node& n);
    bool is_paragraph(std::string& line, Node& n);
    bool is_header(std::string& line, Node& n);
    bool is_code_block(std::string& line, Node& n);
    bool is_math_block(std::string& line, Node& n);
    bool is_quota(std::string& line, Node& n);
    bool is_Horizontal_line(std::string& line, Node& n);

};


inline Parser::Parser(std::string mdFilepath): spaceLine(true) {
    m_file.open(mdFilepath);
    if(!m_file.is_open()) {
        throw std::runtime_error("Cannot open file: " + mdFilepath);
    }

    rootNode.set_node_type(NodeType::document);
    rootNode.set_node_layer(0);
    rootNode.set_node_contents("document");
}

inline Parser::~Parser() {
    if (m_file.is_open()) {
        m_file.close();
    }
}
