

struct Expression
{
    virtual void accept(ExpressionVisitor* visitor)= 0;
};

void accept(ExpressionVisitor* visitor) override
{
    visitor->visit(this);
}

struct ExpressionVisitor
{
    virtual void visit(DoubleExpression* de) = 0;
    virtual void visit(AdditionalExpression* ae) = 0;
};

struct ExpressionPrinter: ExpressionVisitor
{
    ostringstream oss;
    string str() const { return oss.str(); }

    void visit(DoubleExpression* de) override;
    void visit(AdditionalExpression* ae) override;  
};

void ExpressionPrinter::visit(AdditionExpression* ae)
{
    oss << "(";
    ae->left->accept(this);
    oss << "+";
    ae->right->accept(this);
    oss << ")";
}

int main()
{
    auto e =new AddiotionExpression
    {

    };

    ostringstream oss;
    ExpressionPrinter ep;
    ep.visit(e);
    std::cout << ep.str() << std::endl;
};
