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
        bool endFlag = false;                   // 判断是否成功读取到了代码块末尾标志
        while(std::getline(m_file, codeLine)) { 
            if(codeLine.substr(0, 3) != "```") { 
                Node codeLineNode;
                codeLineNode.set_node_layer(node.layer+1);
                codeLineNode.set_node_type(NodeType::codeLine);
                codeLineNode.set_node_contents("codeLine");
                node.children.push_back(std::move(codeLineNode));
            } else { 
                endFlag = true;
                break;
            }
        }

        if(endFlag) { 
            rootNode.children.push_back(std::move(node));
        } else {
            // todo：将代码块中的内容重新解析
        }
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
        bool endFlag = false;
        while(std::getline(m_file, mathLine)) { 
            if(mathLine.substr(0, 2) != "$$") { 
                Node mathLineNode;
                mathLineNode.set_node_layer(node.layer+1);
                mathLineNode.set_node_type(NodeType::mathLine);
                mathLineNode.set_node_contents("mathLine");
                node.children.push_back(std::move(mathLineNode));
            } else {
                endFlag = true;
                break;
            }
        }

        if(endFlag) { 
            n.children.push_back(std::move(node)); 
        } else {
            // tode：将数学块中的内容重新解析
        }
    } else {
        is_paragraph(line, n);
    }

    return true;
}

bool Parser::is_quota(std::string& line, Node& n) {
    return true;
}
