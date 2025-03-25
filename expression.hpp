// expression.hpp
#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <memory>
#include <complex>
#include <string>
#include <sstream>
#include <iostream>

// Предполагаемые объявления необходимых типов и классов
enum class NodeType {
    number, variable, Add, Minus, Multiply, Division, Pow, Sin, Cos, Exp, Ln
};

template<typename T>
struct Node {
    NodeType type_of_var;
    T value;
    std::string variable;
    std::shared_ptr<Node<T>> left;
    std::shared_ptr<Node<T>> right;

    Node(T val_new);
    Node(std::string var_new);
    Node(NodeType type_new, std::shared_ptr<Node<T>> left_new, std::shared_ptr<Node<T>> right_new);
};

template<typename T>
class Expression {
public:
    std::shared_ptr<Node<T>> root;

    Expression(std::shared_ptr<Node<T>>& head);
    Expression(T value);
    Expression(std::string variable);
    Expression(const Expression& other);
    Expression& operator=(const Expression& other);
    Expression(Expression&& other) noexcept;
    Expression& operator=(Expression&& other) noexcept;
    ~Expression();

    Expression operator+(Expression& other);
    Expression operator-(Expression& other);
    Expression operator*(Expression& other);
    Expression operator/(Expression& other);
    Expression operator^(Expression& other);
    Expression Sin();
    Expression Cos();
    Expression Ln();
    Expression Exp();

    std::shared_ptr<Node<T>> CopyTree(const std::shared_ptr<Node<T>>& head);
    std::string Help_Expression_To_String(std::shared_ptr<Node<T>>& head);
    std::string ExpressionToString();
    std::shared_ptr<Node<T>> Diffiriention_help(std::shared_ptr<Node<T>>& head);
    std::shared_ptr<Node<T>> StringToExpression(std::string& some_str);

    Expression Diffiriention();
};

// Добавляем объявления тестовых функций:
template<typename T>
void TestCopyTree();

template<typename T>
void TestHelp_Expression_To_String();

template<typename T>
void TestExpression_To_String();

template<typename T>
void TestDiffiriention_help();

template<typename T>
void TestDiffiriention();

#endif // EXPRESSION_HPP
