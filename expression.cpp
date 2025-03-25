#include "expression.hpp"


void Assert(bool condition) {
    if (condition) {
        std::cout << "OK" << std::endl;
    } else {
        std::cout << "FAIL" << std::endl;
    }
}

template <typename T>
Node<T>::Node(T val_new) {
    type_of_var = NodeType::number;
    value = val_new;
    variable = "";
    left = nullptr;
    right = nullptr;
}

template <typename T>
Node<T>::Node(std::string var_new) {
    type_of_var = NodeType::variable;
    value = T();
    variable = var_new;
    left = nullptr;
    right = nullptr;
}

template <typename T>
Node<T>::Node(NodeType type_new, std::shared_ptr<Node> left_new, std::shared_ptr<Node> right_new) {
    type_of_var = type_new;
    value = T();
    variable = "";
    left = left_new;
    right = right_new;
}

template<typename T>
std::shared_ptr<Node<T>> Expression<T>::CopyTree(const std::shared_ptr<Node<T>>& head) {
    if (!head) {
        return nullptr;
    }

    auto new_head = std::make_shared<Node<T>>(head->type_of_var, CopyTree(head->left), CopyTree(head->right));

    if (head->type_of_var == NodeType::number) {
        new_head->value = head->value;
    } else if (head->type_of_var == NodeType::variable) {
        new_head->variable = head->variable;
    }
    return new_head;
}

template<typename T>
Expression<T>::Expression(std::shared_ptr<Node<T>>& head) {
    root = head;
}

template<typename T>
Expression<T>::Expression(T value) {
    root = std::make_shared<Node<T>>(value);
}

template<typename T>
Expression<T>::Expression(std::string variable) {
    root = std::make_shared<Node<T>>(variable);
}

template<typename T>
Expression<T>::~Expression() = default;

template<typename T>
Expression<T>::Expression(const Expression& other) {
    this->root = CopyTree(other.root);
}



template <typename T>
Expression<T>::Expression(Expression&& other) noexcept {
    this->root = std::move(other.root);
    other.root = nullptr;
}

template<typename T>
Expression<T>& Expression<T>::operator=(const Expression<T>& other) {
    if (this != &other) {
        this->root = CopyTree(other.root);
    }
    return *this;
}

template<typename T>
Expression<T>& Expression<T>::operator=(Expression<T>&& other) noexcept {
    if (this != &other) {
        this->root = std::move(other.root);
        other.root = nullptr;
    }
    return *this;
}


template<typename T>
Expression<T> Expression<T>::operator+(Expression& other) {
    auto new_head = std::make_shared<Node<T>>(NodeType::Add, this->root, other.root);
    return Expression<T>(new_head);
}

template<typename T>
Expression<T> Expression<T>::operator-(Expression& other) {
    auto new_head = std::make_shared<Node<T>>(NodeType::Minus, this->root, other.root);
    return Expression<T>(new_head);
}

template<typename T>
Expression<T> Expression<T>::operator*(Expression& other) {
    auto new_head = std::make_shared<Node<T>>(NodeType::Multiply, this->root, other.root);
    return Expression<T>(new_head);
}

template<typename T>
Expression<T> Expression<T>::operator/(Expression& other) {
    auto new_head = std::make_shared<Node<T>>(NodeType::Division, this->root, other.root);
    return Expression<T>(new_head);
}

template<typename T>
Expression<T> Expression<T>::operator^(Expression& other) {
    auto new_head = std::make_shared<Node<T>>(NodeType::Pow, this->root, other.root);
    return Expression<T>(new_head);
}

template<typename T>
Expression<T> Expression<T>::Sin() {
    auto new_head = std::make_shared<Node<T>>(NodeType::Sin, this->root, nullptr);
    return Expression(new_head);
}

template<typename T>
Expression<T> Expression<T>::Cos() {
    auto new_head = std::make_shared<Node<T>>(NodeType::Cos, this->root, nullptr);
    return new_head;
}

template<typename T>
Expression<T> Expression<T>::Ln() {
    auto new_head = std::make_shared<Node<T>>(NodeType::Ln, this->root, nullptr);
    return new_head;
}

template<typename T>
Expression<T> Expression<T>::Exp() {
    auto new_head = std::make_shared<Node<T>>(NodeType::Exp, this->root, nullptr);
    return new_head;
}

template<typename T>
std::shared_ptr<Node<T>> Expression<T>::StringToExpression(std::string& some_str) {
    if (some_str == "") {
        return nullptr;
    }
    return nullptr;
}

template<typename T>
std::string Expression<T>::Help_Expression_To_String(std::shared_ptr<Node<T>>& head) {
    if (head == nullptr) {
        return "";
    }

    std::ostringstream left_str1, right_str1;
    std::string new_str = "";
    std::string left_str = "";
    std::string middle_str = "";
    std::string right_str = "";
    size_t pos;

    switch (head->type_of_var) {
        case NodeType::number:
            if constexpr (std::is_same_v<T, std::complex<double>>) {
                left_str1 << head->value.real();
                right_str1 << head->value.imag();
                new_str = "(" + left_str1.str() + " + " + right_str1.str() + "i)";

                while ((pos = new_str.find(" + 0i")) != std::string::npos) {
                    new_str.replace(pos, 5, "");
                }
                while ((pos = new_str.find(" - 0i")) != std::string::npos) {
                    new_str.replace(pos, 5, "");
                }
                while ((pos = new_str.find(" + 0")) != std::string::npos) {
                    new_str.replace(pos, 4, "");
                }
                while ((pos = new_str.find(" - 0")) != std::string::npos) {
                    new_str.replace(pos, 4, "");
                }

                if (new_str.front() == '(' && new_str.back() == ')') {
                    new_str = new_str.substr(1, new_str.size() - 2);
                }
            } else {
                left_str = std::to_string(head->value);

                while ((pos = left_str.find("0.00000")) != std::string::npos) {
                    left_str.replace(pos, 7, "");
                }
                while ((pos = left_str.find("00000")) != std::string::npos) {
                    left_str.replace(pos, 5, "");
                }
                while ((pos = left_str.find(".0")) != std::string::npos) {
                    left_str.replace(pos, 2, "");
                }

                if (left_str.front() == '(' && left_str.back() == ')') {
                    left_str = left_str.substr(1, left_str.size() - 2);
                }

                new_str = left_str;
            }

            return new_str;

        case NodeType::variable:
            new_str = head->variable;
            return new_str;

        case NodeType::Add:
            left_str = Help_Expression_To_String(head->left);
            right_str = Help_Expression_To_String(head->right);

            if (left_str == "0") {
                new_str = right_str;
            } else if (right_str == "0") {
                new_str = left_str;
            } else {
                new_str += '(';
                new_str += left_str;
                new_str += ' ';
                new_str += '+';
                new_str += ' ';
                new_str += right_str;
                new_str += ')';
            }

            while ((pos = new_str.find("+ 0 ")) != std::string::npos) {
                new_str.replace(pos, 4, "");
            }
            while ((pos = new_str.find("- 0 ")) != std::string::npos) {
                new_str.replace(pos, 4, "");
            }

            return new_str;

        case NodeType::Minus:
            left_str = Help_Expression_To_String(head->left);
            right_str = Help_Expression_To_String(head->right);

            if (left_str == "0") {
                new_str += '-';
                new_str += right_str;
            } else if (right_str == "0") {
                new_str += left_str;
            } else {
                new_str += '(';
                new_str += left_str;
                new_str += ' ';
                new_str += '-';
                new_str += ' ';
                new_str += right_str;
                new_str += ')';
            }

            while ((pos = new_str.find("+ 0 ")) != std::string::npos) {
                new_str.replace(pos, 4, "");
            }
            while ((pos = new_str.find("- 0 ")) != std::string::npos) {
                new_str.replace(pos, 4, "");
            }

            return new_str;

        case NodeType::Multiply:
            left_str = Help_Expression_To_String(head->left);
            right_str = Help_Expression_To_String(head->right);

            if (left_str == "0" || right_str == "0") {
                new_str = "0";
            } else if (left_str == "1") {
                new_str = right_str;
            } else if (right_str == "1") {
                new_str = left_str;
            } else if (left_str == "-1") {
                new_str += '(';
                new_str += '-';
                new_str += right_str;
                new_str += ')';
            } else if (right_str == "-1") {
                new_str += '(';
                new_str += '-';
                new_str += left_str;
                new_str += ')';
            } else {
                if (((head->left->type_of_var == NodeType::number) && (head->right->type_of_var == NodeType::variable)) || ((head->left->type_of_var == NodeType::variable) && (head->right->type_of_var == NodeType::number))) {
                    new_str += left_str;
                    new_str += right_str;
                } else {
                    new_str += '(';
                    new_str += left_str;
                    new_str += ' ';
                    new_str += '*';
                    new_str += ' ';
                    new_str += right_str;
                    new_str += ')';
                }
            }

            while ((pos = new_str.find("+ 0 ")) != std::string::npos) {
                new_str.replace(pos, 4, "");
            }
            while ((pos = new_str.find("- 0 ")) != std::string::npos) {
                new_str.replace(pos, 4, "");
            }

            return new_str;

        case NodeType::Division:
            left_str = Help_Expression_To_String(head->left);
            right_str = Help_Expression_To_String(head->right);

            if (left_str == "0") {
                new_str = right_str;
            } else if (right_str == "0") {
                new_str = "";
            } else {
                new_str += '(';
                new_str += left_str;
                new_str += ' ';
                new_str += '/';
                new_str += ' ';
                new_str += right_str;
                new_str += ')';
            }

            return new_str;

        case NodeType::Pow:
            left_str = Help_Expression_To_String(head->left);
            right_str = Help_Expression_To_String(head->right);

            if (left_str == "0") {
                new_str = "0";
            } else if (right_str == "0" && (head->left->type_of_var != NodeType::variable)) {
                new_str = "1";
            } else if (right_str == "" && left_str == "") {
                new_str = "";
            } else {
                new_str += '(';
                new_str += left_str;
                new_str += ' ';
                new_str += '^';
                new_str += ' ';
                new_str += right_str;
                new_str += ')';
            }

            return new_str;

        case NodeType::Sin:
            left_str = Help_Expression_To_String(head->left);
            right_str = Help_Expression_To_String(head->right);

            if (left_str == "0" || left_str == "") {
                new_str = "sin";
                new_str += '(';
                new_str += right_str;
                new_str += ')';
            } else if (right_str == "0" || right_str == "") {
                new_str = "sin";
                new_str += '(';
                new_str += left_str;
                new_str += ')';
            } else if (right_str == "" && left_str == "") {
                new_str = "";
            } else {
                new_str = "sin";
                new_str += '(';
                new_str += left_str;
                new_str += ' ';
                new_str += '+';
                new_str += ' ';
                new_str += right_str;
                new_str += ')';
            }

            return new_str;

        case NodeType::Cos:
            left_str = Help_Expression_To_String(head->left);
            right_str = Help_Expression_To_String(head->right);

            if (left_str == "0" || left_str == "") {
                new_str = "cos";
                new_str += '(';
                new_str += right_str;
                new_str += ')';
            } else if (right_str == "0" || right_str == "") {
                new_str = "cos";
                new_str += '(';
                new_str += left_str;
                new_str += ')';
            } else if (right_str == "" && left_str == "") {
                new_str = "";
            } else {
                new_str = "cos";
                new_str += '(';
                new_str += left_str;
                new_str += ' ';
                new_str += '+';
                new_str += ' ';
                new_str += right_str;
                new_str += ')';
            }

            return new_str;

        case NodeType::Exp:
            left_str = Help_Expression_To_String(head->left);
            right_str = Help_Expression_To_String(head->right);

            if (left_str == "0" || left_str == "") {
                new_str = "e";
                new_str += '^';
                new_str += right_str;
            } else if (right_str == "0" || right_str == "") {
                new_str = "e";
                new_str += '^';
                new_str += left_str;
            } else if (right_str == "" && left_str == "") {
                new_str = "";
            } else {
                new_str = "e";
                new_str += '^';
                new_str += left_str;
                new_str += ' ';
                new_str += '+';
                new_str += ' ';
                new_str += right_str;
            }

            return new_str;

        case NodeType::Ln:
            left_str = Help_Expression_To_String(head->left);
            right_str = Help_Expression_To_String(head->right);

            if (left_str == "0" || left_str == "") {
                new_str = "ln";
                new_str += '(';
                new_str += right_str;
                new_str += ')';
            } else if (right_str == "0" || right_str == "") {
                new_str = "ln";
                new_str += '(';
                new_str += left_str;
                new_str += ')';
            } else if (((right_str == "" && left_str == "") || (right_str == "0" && left_str == "0"))) {
                new_str = "";
            } else {
                new_str = "ln";
                new_str += '(';
                new_str += left_str;
                new_str += ' ';
                new_str += '+';
                new_str += ' ';
                new_str += right_str;
                new_str += ')';
            }

            return new_str;

        default:
            return "This type of root is not defined !";
    }
}

template<typename T>
void TestHelp_Expression_To_String() {
    using Complex = std::complex<double>;

    auto new_head1 = std::make_shared<Node<T>>("135x");
    auto new_head2 = std::make_shared<Node<Complex>>(228);

    Expression<T> res1(new_head1);
    Expression<Complex> res2(new_head2);

    auto sup_new_head1 = res1.Help_Expression_To_String(new_head1);
    auto sup_new_head2 = res2.Help_Expression_To_String(new_head2);

    Assert(sup_new_head1 == sup_new_head2);
    Assert(sup_new_head1 != "");
    Assert(sup_new_head2 != "");
    Assert(sup_new_head1 == "135x");
    Assert(sup_new_head2 == "228");
}

template<typename T>
std::string Expression<T>::ExpressionToString() {
    return Help_Expression_To_String(root);
}

template<typename T>
void TestExpression_To_String() {
    using Complex = std::complex<double>;

    auto new_head1 = std::make_shared<Node<T>>("x");
    auto new_head2 = std::make_shared<Node<T>>(5);

    auto new_head3 = std::make_shared<Node<T>>(NodeType::Add, new_head1, new_head2);
    auto new_head4 = std::make_shared<Node<T>>(NodeType::Sin, new_head3, nullptr);

    Expression<T> res1(new_head3);
    Expression<T> res2(new_head4);

    auto new_res1 = res1.ExpressionToString();
    auto new_res2 = res2.ExpressionToString();

    Expression<Complex> four(Complex(17, 0));
    Expression<Complex> x("x");
    Expression<Complex> three_i(Complex(0, 9));

    Expression<Complex> term1 = four * x;
    Expression<Complex> result = term1 + three_i;

    Expression<Complex> result1 = result.Ln();

    Assert(new_res2 == new_res1);
    Assert(new_res1 == "");
    Assert(new_res2 == "");
    Assert(new_res1 == "(x + 5)");
    Assert(new_res2 == "sin((x + 5))");
    Assert(result1.ExpressionToString() == "ln((17x + 9i))");
}

template<typename T>
std::shared_ptr<Node<T>> Expression<T>::Diffiriention_help(std::shared_ptr<Node<T>>& head) {
    if (head == nullptr) {
        return nullptr;
    }

    std::shared_ptr<Node<T>> new_head;
    std::shared_ptr<Node<T>> u, v, du, dv, left_head, right_head, middle_head, dbl_right_head, pointer_one;

    switch (head->type_of_var) {
        case NodeType::number:
            new_head = std::make_shared<Node<T>>(0.0);
            break;

        case NodeType::variable:
            if (head->variable.size() >= 2) {
                auto frac = head->variable.substr(0, head->variable.size() - 1);
                new_head = std::make_shared<Node<T>>(frac);
            } else {
                new_head = std::make_shared<Node<T>>(1.0);
            }
            break;

        case NodeType::Add:
            new_head = std::make_shared<Node<T>>(NodeType::Add, Diffiriention_help(head->left), Diffiriention_help(head->right));
            break;

        case NodeType::Minus:
            new_head = std::make_shared<Node<T>>(NodeType::Minus, Diffiriention_help(head->left), Diffiriention_help(head->right));
            break;

        case NodeType::Multiply:
            u = head->left;
            v = head->right;

            du = Diffiriention_help(u);
            dv = Diffiriention_help(v);

            left_head = std::make_shared<Node<T>>(NodeType::Multiply, du, v);
            right_head = std::make_shared<Node<T>>(NodeType::Multiply, u, dv);

            new_head = std::make_shared<Node<T>>(NodeType::Add, left_head, right_head);
            break;

        case NodeType::Division:
            u = head->left;
            v = head->right;

            if ((std::abs(v->value) < 1e-10) && v->variable == "" && v->left == nullptr && v->right == nullptr) {
                break;
            }

            du = Diffiriention_help(u);
            dv = Diffiriention_help(v);

            left_head = std::make_shared<Node<T>>(NodeType::Multiply, du, v);
            right_head = std::make_shared<Node<T>>(NodeType::Multiply, u, dv);

            middle_head = std::make_shared<Node<T>>(NodeType::Minus, left_head, right_head);
            dbl_right_head = std::make_shared<Node<T>>(NodeType::Multiply, v, v);
            new_head = std::make_shared<Node<T>>(NodeType::Division, middle_head, dbl_right_head);
            break;

        case NodeType::Pow:
            u = head->left;
            v = head->right;

            du = Diffiriention_help(u);

            if (v->type_of_var == NodeType::number) {
                T exponent = v->value;
                left_head = std::make_shared<Node<T>>(exponent - T(1));
                right_head = std::make_shared<Node<T>>(NodeType::Pow, u, left_head);
                dbl_right_head = std::make_shared<Node<T>>(exponent);
                middle_head = std::make_shared<Node<T>>(NodeType::Multiply, dbl_right_head, right_head);
                new_head = std::make_shared<Node<T>>(NodeType::Multiply, du, middle_head);
            } else {
                pointer_one = std::make_shared<Node<T>>(T(1.0));
                left_head = std::make_shared<Node<T>>(NodeType::Minus, v, pointer_one);
                right_head = std::make_shared<Node<T>>(NodeType::Pow, u, left_head);
                middle_head = std::make_shared<Node<T>>(NodeType::Multiply, v, right_head);
                new_head = std::make_shared<Node<T>>(NodeType::Multiply, du, middle_head);
            }
            break;

        case NodeType::Cos:
            u = head->left;
            pointer_one = std::make_shared<Node<T>>(-1.0);

            right_head = std::make_shared<Node<T>>(NodeType::Sin, u, nullptr);

            du = Diffiriention_help(u);
            left_head = std::make_shared<Node<T>>(NodeType::Multiply, du, pointer_one);

            new_head = std::make_shared<Node<T>>(NodeType::Multiply, left_head, right_head);
            break;

        case NodeType::Sin:
            u = head->left;
            right_head = std::make_shared<Node<T>>(NodeType::Cos, u, nullptr);

            du = Diffiriention_help(u);

            new_head = std::make_shared<Node<T>>(NodeType::Multiply, du, right_head);
            break;

        case NodeType::Ln:
            u = head->left;
            pointer_one = std::make_shared<Node<T>>(1.0);

            du = Diffiriention_help(u);

            right_head = std::make_shared<Node<T>>(NodeType::Division, pointer_one, u);

            new_head = std::make_shared<Node<T>>(NodeType::Multiply, du, right_head);
            break;

        case NodeType::Exp:
            u = head->left;

            du = Diffiriention_help(u);

            left_head = std::make_shared<Node<T>>(NodeType::Exp, u, nullptr);
            new_head = std::make_shared<Node<T>>(NodeType::Multiply, du, left_head);
            break;

        default:
            new_head = nullptr;
            break;
    }

    return new_head;
}

template<typename T>
void TestDiffiriention_help() {
    using Complex = std::complex<double>;

    auto new_head1 = std::make_shared<Node<T>>("x");
    auto new_head2 = std::make_shared<Node<T>>(5);

    auto new_head_n = std::make_shared<Node<T>>(NodeType::Sin, new_head1, nullptr);

    auto new_head3 = std::make_shared<Node<T>>(NodeType::Division, new_head1, new_head2);
    auto new_head4 = std::make_shared<Node<T>>(NodeType::Ln, new_head_n, nullptr);

    Expression<T> res1(new_head3);
    Expression<T> res2(new_head4);

    auto w_res1 = res1.Diffiriention_help(new_head3);
    auto w_res2 = res2.Diffiriention_help(new_head4);

    Expression<T> nres1(w_res1);
    Expression<T> nres2(w_res2);

    auto new_res1 = nres1.ExpressionToString();
    auto new_res2 = nres2.ExpressionToString();

    Expression<Complex> four(Complex(17, 0));
    Expression<Complex> x("x");
    Expression<Complex> three_i(Complex(0, 9));

    Expression<Complex> term1 = four * x;
    Expression<Complex> result = term1 + three_i;

    Expression<Complex> result1 = result.Sin();
    Expression<Complex> result2 = result1.Diffiriention();

    Assert(new_res1 == "");
    Assert(new_res2 == "");
    Assert(new_res1 == "(5 / (5 * 5))");
    Assert(new_res2 == new_res1);
    Assert(new_res2 == "(cos(x) * (1 / sin(x)))");
    Assert(result2.ExpressionToString() == "(17 * cos((17x + 9i)))");
}

template<typename T>
Expression<T> Expression<T>::Diffiriention() {
    auto new_root = Diffiriention_help(root);
    root = CopyTree(new_root);
    return *this;
}

template<typename T>
void TestDiffiriention() {
    using Complex = std::complex<double>;

    auto new_head1 = std::make_shared<Node<T>>("x");
    auto new_head2 = std::make_shared<Node<T>>(5);

    auto new_head_n = std::make_shared<Node<T>>(NodeType::Exp, new_head1, nullptr);

    auto new_head3 = std::make_shared<Node<T>>(NodeType::Multiply, new_head1, new_head2);
    auto new_head4 = std::make_shared<Node<T>>(NodeType::Cos, new_head_n, nullptr);

    Expression<T> res1(new_head3);
    Expression<T> res2(new_head4);

    auto w_res1 = res1.Diffiriention();
    auto w_res2 = res2.Diffiriention();

    Expression<T> nres1(w_res1);
    Expression<T> nres2(w_res2);

    auto new_res1 = nres1.ExpressionToString();
    auto new_res2 = nres2.ExpressionToString();

    Expression<Complex> four(Complex(17, 0));
    Expression<Complex> x("x");
    Expression<Complex> three_i(Complex(0, 9));

    Expression<Complex> term1 = four * x;
    Expression<Complex> result = term1 + three_i;

    Expression<Complex> result1 = result.Exp();
    Expression<Complex> result2 = result1.Diffiriention();

    Assert(new_res1 == "");
    Assert(new_res1 == "5");
    Assert(new_res2 == new_res1);
    Assert(new_res2 == "");
    Assert(new_res2 == "((-e^x) * sin(e^x))");
    Assert(result2.ExpressionToString() == "(17 * e^(17x + 9i))");
    Assert(result2.ExpressionToString() == "");
}
template<typename T>
void TestCopyTree() {
    // Простой тест копирования дерева:
    // Создаем выражение из числа.
    Expression<T> expr(T(42));
    // Создаем копию с помощью копирующего конструктора.
    Expression<T> copyExpr(expr);
    // Проверяем, что строковое представление копии совпадает с оригиналом.
    Assert(expr.ExpressionToString() == copyExpr.ExpressionToString());
}

template void TestCopyTree<double>();
template void TestHelp_Expression_To_String<double>();
template void TestExpression_To_String<double>();
template void TestDiffiriention_help<double>();
template void TestDiffiriention<double>();

template class Expression<std::complex<double>>;
