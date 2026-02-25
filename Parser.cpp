#include "Parser.hpp"

Node Parser::parsing() {
    if(!m_file.is_open()) {
        throw std::runtime_error("File not opened");
    }

    std::string line;
    while (std::getline(m_file, line))
    {   // 使用每行首字符对块类型进行初步筛查
        if(line.empty()) {
            spaceLine = true;
        } else {
            int spaceCount = 0;         // 判断第一个非空格字符起始位置，也可视为空格数统计
            while(line[spaceCount] == ' ') {
                spaceCount++;
            }

            bolckSwitch(line, spaceCount, rootNode);
            spaceLine = false;
        }
    }

    return rootNode;
}

bool Parser::bolckSwitch(std::string& line, int& p, Node& n) {
    switch(line[p]) {
        case '#': is_header(line, rootNode); break;
        case '|': ; break;
        case '1': ; break;
        case '+': ; break;
        case '-': ;
        case '*': is_Horizontal_line(line, rootNode); break;
        case '>': is_quota(line, rootNode); break;
        case '`': is_code_block(line, rootNode); break;
        case '$': is_math_block(line, rootNode); break;
        default : is_paragraph(line, rootNode);
    }
    return true;
}

bool Parser::is_paragraph(std::string& line, Node& n) {
    if(spaceLine || 
            (!n.children.empty() && n.children.back().nodeType != NodeType::paragraph)) {
        Node node;
        node.set_node_type(NodeType::paragraph);
        node.set_node_layer(n.layer+1);
        node.set_node_contents("paragraph");
        // todo: 行内处理
        rootNode.children.push_back(std::move(node));
    } else {
        // todo：添加进上一个paragraph Node结点
    }

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
    Node node;
    node.set_node_layer(n.layer+1);
    node.set_node_type(NodeType::quote);

    int quotaCount = 1;         // 统计有多少个引用字符
    while(line[quotaCount] == '>') {
        quotaCount++;
    }
    node.set_node_level(quotaCount);
    node.set_node_contents("quota/"+std::to_string(quotaCount));

    // 判断上一行是否是空行
    // 如果是空行则直接进行插入操作
    if(spaceLine) {
        node.set_node_layer(n.layer+1);
        n.children.push_back(std::move(node));
    } else {
        // 迭代判断Node的children末尾元素是否匹配
        // 匹配则插入合适位置
        // 不匹配则新建node
        Node* tmpNode = &rootNode;
        while(!(*tmpNode).children.empty()) {
            if((*tmpNode).children.back().nodeType != NodeType::quote) {
                (*tmpNode).children.push_back(std::move(node));
                break;
            } else if((*tmpNode).children.back().level >= quotaCount) {
                // 情况一：  情况二：
                // >>>>      >>>
                // >>        >>>
                // todo：添加进content中
                break;
            } else {
                node.set_node_layer(node.layer+1);
                tmpNode = &((*tmpNode).children.back());
            }
        }
        if((*tmpNode).children.empty()) { 
            (*tmpNode).children.push_back(std::move(node));
        }
    }

    return true;
}

bool Parser::is_Horizontal_line(std::string& line, Node& n) {
    // 以“-”、“*”开头的行可能为分隔符或无序列表或普通段落
    bool isHL = true;                               // 判断是否是分隔符
    for(int pos=1; pos<line.size(); pos++) {
        if(line.at(pos) != line.at(0) && line.at(pos) != ' ') {
            isHL = false;                           // 只要出现一个不是空格且不与开始字符相同
        }                                           // 即不可能是分隔符
    }

    if(isHL) {
        Node node;
        node.set_node_layer(n.layer+1);
        node.set_node_type(NodeType::horizontalLine);
        node.set_node_contents("horizontalLine");
        n.children.push_back(std::move(node));
    } else {
        if(line.at(1) == ' ') {
            // 无序列表
        } else {
            // 以*开始的普通段落
        }
    }

    return true;
}
