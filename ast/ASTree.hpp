#pragma once
#include <vector>
#include <string>
#include <optional>
#include <iostream>

namespace AST
{

bool validate(const std::string& s);
std::optional<struct Node> generateTree(std::string s);

struct Node : protected std::vector<Node>
{
	int value;

	Node(int value) : value(value) {}

	void add_child(int value);

	Node& fst_child();
	const Node& fst_child() const;

	Node& snd_child();
	const Node& snd_child() const;

	bool exec() const;

	friend void printTree(const Node& node, int tab = 0)
	{
		std::cout << std::string(tab, ' ') << char(node.value) << '\n';
		if (node.empty())
			return;
		if (node.size() == 2)
		{
			printTree(node.fst_child(), tab + 4);
			printTree(node.snd_child(), tab + 4);
		}
		else printTree(node.fst_child(), tab + 4);
	}
};

} // namespace AST
