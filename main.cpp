#include "Parser.hpp"


int main() {
	std::string    mdFilepath, htmlFilepath;     //  输入与输出文件名

	mdFilepath	 = ".//file//test.md";
	htmlFilepath = ".//file//out.html";

	Parser parser(mdFilepath);
	parser.parsing();
	parser.display();

	return 0;
}