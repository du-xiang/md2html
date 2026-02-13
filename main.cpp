#include "Parser.hpp"

std::string getMdFilepath()
{
	// 输入需要处理的文件
	std::string mdFilepath;

	std::cout << "# 输入.md文件名\n# 非当前目录下则需要带路径\n文件名: ";
	while (std::cin >> mdFilepath)
	{
		// 取输入的文件名后缀进行比较
		std::string temp = mdFilepath.substr(mdFilepath.length() - 3, mdFilepath.length());
		if (temp != ".md")
		{
			system("clear");
			std::cout << "文件类型错误(应以.md结尾)" << std::endl;
			std::cout << "# 输入.md文件名\n# 非当前目录下则需要带路径\n文件名: ";
		}
		else
			break;
	}
	system("clear");

	return mdFilepath;
}

std::string getHtmlFilepath()
{
	// 输入需要处理的文件
	std::string htmlFilepath;

	std::cout << "# 输入.html文件名\n文件名: ";
	while (std::cin >> htmlFilepath)
	{
		// 取输入的文件名后缀进行比较
		std::string temp = htmlFilepath.substr(htmlFilepath.length() - 5, htmlFilepath.length());
		if (temp != ".html")
		{
			system("clear");
			std::cout << "文件类型错误(应以.html结尾)" << std::endl;
			std::cout << "# 输入.html文件名\n文件名: ";
		}
		else
			break;
	}
	system("clear");

	return htmlFilepath;
}



int main() {
	// markdownParser mdParser;                    				//  获取解析器类
	std::string    mdFilepath, htmlFilepath;     				//  输入与输出文件名

	//mdFilepath   = getMdFilepath();             				//  获取 markdown 文件名
	//htmlFilepath = getHtmlFilepath();           				//  获取 html 文件名
	// test
	mdFilepath	 = ".//file//test.md";
	htmlFilepath = "file//out.html";

	//mdParser.parser(mdFilepath,htmlFilepath); 					//  开始转换
	Parser parser(mdFilepath);
	parser.parsing();
	parser.display();

	return 0;
}