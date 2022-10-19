#include "ASTree.hpp"

namespace ast {

tree& tree::add_child(tree& other)
{
	emplace_back(other);
	return *this;
}

tree& tree::add_child(int value)
{
	emplace_back(value);
	return *this;
}

/*
tree& tree::add_two(int v1, int v2)
{
	emplace_back(v1);
	emplace_back(v2);
	return *this;
}

tree& tree::add_two(tree& fst, tree& snd)
{
	emplace_back(fst);
	emplace_back(snd);
	return *this;
}
*/

tree& tree::fst_child()
{
	return front();
}

const tree& tree::fst_child() const
{
	return front();
}

tree& tree::snd_child()
{
	return back();
}

const tree& tree::snd_child() const
{
	return back();
}

bool tree::exec() const
{
	switch (value)
	{
		case '!': return !fst_child().exec();
		case '&': return fst_child().exec() && snd_child().exec();
		case '|': return fst_child().exec() || snd_child().exec();
		case '^': return fst_child().exec() != snd_child().exec();
		case '>': if (!fst_child().exec())
					  return true;
				  return snd_child().exec();
		case '=': return fst_child().exec() == snd_child().exec();
	}
	return value == '1';
}

std::string treeToString(const tree& tree, std::string acc)
{
	acc = char(tree.value) + acc;
	std::string fst, snd;
	switch (tree.size())
	{
		case 1: fst = treeToString(tree.fst_child());
				return fst + acc;
		case 2: fst = treeToString(tree.snd_child());
				snd = treeToString(tree.fst_child());
				return fst + snd + acc;
	}
	return acc;
}

// tree& tree::operator= (const tree& other)
// {
// 	value = other.value;
// 	assign(other.begin(), other.end());
// 	return *this;
// }

bool operator== (const tree& lhs, const tree& rhs)
{
	if (lhs.empty() && rhs.empty() && lhs.value == rhs.value)
		return true;
	if (rhs.value == placeholder)
		return true;
	if (lhs.value != rhs.value || lhs.size() != rhs.size())
		return false;
	if (lhs.size() == 1 && rhs.size() == 1)
		return lhs.fst_child() == rhs.fst_child();
	return lhs.fst_child() == rhs.fst_child() && lhs.snd_child() == rhs.snd_child();
}

void tree::printValue(const std::string& pref, char value, bool isRight)
{
	static const auto resetColor = [] { return "\033[0m"; };
	static const auto chooseColor = []()
	{
		static auto i = 0u;
		static const std::string colors[] = { "\033[1;32m", "\033[1;33m", "\033[1;31m", "\033[1;35m" };
		return colors[i++ % 4];
	};
	// std::cout << prefix << (isRight ? "⦦ " : "⦧ " )
	std::cout << pref
			  << (isRight ? "⦧ " : "⦦ " )
			  << chooseColor()
			  << '\'' << char(value) << '\''
			  << resetColor() << '\n';
}

/*
void Node::printValue(const std::string& prefix, char value, bool isRight)
{
	static const auto resetColor = [] { return "\033[0m"; };
	static const auto chooseColor = []()
	{
		static auto i = 0u;
		static const std::string colors[] = { "\033[1;32m", "\033[1;33m", "\033[1;31m", "\033[1;35m" };
		return colors[i++ % 4];
	};
	std::cout << prefix << (isRight ? "⦧ " : "⦦ " )
	// std::cout << prefix << (isRight ? "⦦ " : "⦧ " )
			  << chooseColor() << '\'' << char(value) << '\'' << resetColor() << '\n';
}
*/

/*
void tree::printValue(int tab, char value)
{
	static const auto resetColor = [] { return "\033[0m"; };
	static const auto chooseColor = [](int tab)
	{
		static const char* colors[] = { "\033[1;36m", "\033[1;34m", "\033[1;33m", "\033[1;32m", "\033[1;35m" };
		return colors[tab % 5];
	};
	std::cout << chooseColor(tab)
			  << std::string(tab, ' ')
			  << char(value)
			  << resetColor() << '\n';
}
*/

} // namespace ast

/*
template <>
struct std::hash<ast::tree>
{
	size_t operator() (const ast::tree& node) const
	{
		switch (node.size())
		{
			case 0: return (std::hash<int>()(node.value) % 3) << 1;
			case 1: return ((std::hash<int>()(node.value) % 3) << 1)
						 ^ (std::hash<int>()(node.fst_child().value) % 3 << 1);
			case 2: return ((std::hash<int>()(node.value) % 3) << 1)
						 ^ (std::hash<int>()(node.fst_child().value) % 3 << 1)
						 ^ (std::hash<int>()(node.snd_child().value) % 3
 << 1);
		}
		return std::string::npos;
	}
};
*/
