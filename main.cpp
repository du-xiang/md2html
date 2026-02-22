#include "Parser.hpp"

bool display(const Node& n) {
    for(size_t i=0; i<n.layer; i++) {
        std::cout << "    ";
    }
    std::cout << '|' << n.contents;
    std::cout << std::endl;

    if(!n.children.empty()) { 
        for(auto s=n.children.cbegin(); s!=n.children.cend(); s++) { 
            display(*s);
        }
    }

    return true;
}

int main() {
	std::string    mdFilepath, htmlFilepath;     //  输入与输出文件名

	mdFilepath	 = ".//file//test.md";
	htmlFilepath = ".//file//out.html";

	Parser parser(mdFilepath);
	auto rootNode = parser.parsing();
	display(rootNode);

	return 0;
}