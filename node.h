#pragma once
#include "date.h"
#include <string>
#include <memory>

using namespace std;


enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation {
    And,
    Or
};


class Node {
public:
    virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

class EmptyNode : public Node {
public:
    EmptyNode();

    virtual bool Evaluate(const Date& date, const string& event) const override;
};

class LogicalOperationNode: public Node {
public :
    LogicalOperationNode(const LogicalOperation& operation, const shared_ptr<Node>& left, const shared_ptr<Node>& right);

    virtual bool Evaluate(const Date& date, const string& event) const override;

private:
    const LogicalOperation operation;
    const shared_ptr<Node> left;
    const shared_ptr<Node> right;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison& cmp, const string& valueToCompareWith);

    virtual bool Evaluate(const Date& date, const string& event) const override;

private:
    const Comparison cmp;
    const string valueToCompareWith;
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(const Comparison& cmp, const Date& valueToCompareWith);

    virtual bool Evaluate(const Date& date, const string& event) const override;

private:
    const Comparison cmp;
    const Date valueToCompareWith;
};