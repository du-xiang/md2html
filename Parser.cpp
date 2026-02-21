#include "Parser.hpp"

Node Parser::parsing() {
    if(!m_file.is_open()) {
        throw std::runtime_error("File not opened");
    }

    std::string line;
    while (std::getline(m_file, line))
    {   // 使用每行首字符对块类型进行初步筛查
        if(line.empty()) {
            // 空行跳过
        } else {
            switch(line[0]) {
                case '#': is_header(line, rootNode); break;
                case '-': ; break;
                case '+': ; break;
                case '1': ; break;
                case '|': ; break;
                case '>': is_quota(line, rootNode); break;
                case '`': is_code_block(line, rootNode); break;
                case '$': is_math_block(line, rootNode); break;
                default : is_paragraph(line, rootNode);
            }
        }
    }

    return rootNode;
}

bool Parser::is_paragraph(std::string& line, Node& n) {
    Node node;

    node.set_node_type(NodeType::paragraph);
    node.set_node_layer(n.layer+1);
    node.set_node_contents("paragraph");
    // todo: 行内处理
    rootNode.children.push_back(std::move(node));

    return true;
}

bool Parser::is_header(std::string& line, Node& n) {
    Node node;
    node.set_node_layer(n.layer+1);
    size_t pos = line.find(' ');

    std::string prefix(pos, '#');
    if(line.substr(0, pos) == prefix) {
        node.set_node_type(NodeType::header);
        node.set_node_level(pos);
        node.set_node_contents("header/"+std::to_string(pos));
        // todo: 行内处理
        n.children.push_back(std::move(node));
    } else {
        is_paragraph(line, n);
    }

    return true;
}

bool Parser::is_code_block(std::string& line, Node& n) {
    std::vector<std::string> progLang = {"cpp","python","java"};

    if(line.substr(0, 3) == "```") {
        Node node;
        node.set_node_layer(n.layer+1);
        node.set_node_type(NodeType::codeBlock);
        node.set_node_contents("codeBlock");

        std::string codeLine;
        std::getline(m_file, codeLine);
        while(codeLine.substr(0, 3) != "```" && !m_file.eof()) {
            Node codeLineNode;
            codeLineNode.set_node_layer(node.layer+1);
            codeLineNode.set_node_type(NodeType::codeLine);
            codeLineNode.set_node_contents("codeLine");
            node.children.push_back(std::move(codeLineNode));
            std::getline(m_file, codeLine);
        }

        rootNode.children.push_back(std::move(node));
    } else {
        is_paragraph(line, n);
    }

    return true;
}

bool Parser::is_math_block(std::string& line, Node& n) {
    if(line.substr(0, 2) == "$$") { 
        Node node;
        node.set_node_layer(n.layer+1);
        node.set_node_type(NodeType::mathBlock);
        node.set_node_contents("mathBlock");

        std::string mathLine;
        std::getline(m_file, mathLine);
        while(mathLine.substr(0, 2) != "$$" && !m_file.eof()) { 
            Node mathLineNode;
            mathLineNode.set_node_layer(node.layer+1);
            mathLineNode.set_node_type(NodeType::mathLine);
            mathLineNode.set_node_contents("mathLine");
            node.children.push_back(std::move(mathLineNode));
            std::getline(m_file, mathLine);
        }

        n.children.push_back(std::move(node));
    } else {
        is_paragraph(line, n);
    }

    return true;
}

bool Parser::is_quota(std::string& line, Node& n) {
    return true;
}
