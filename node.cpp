//
// Created by Ivan Fekete on 17.10.2020.
//

#include "node.h"

EmptyNode::EmptyNode() {}

bool EmptyNode::Evaluate(const Date& date, const string& event) const {
    return true;
}


LogicalOperationNode::LogicalOperationNode(const LogicalOperation& operation, const shared_ptr<Node>& left, const shared_ptr<Node>& right)
    : operation(operation), left(left), right(right) {}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
    bool leftValue = left->Evaluate(date, event);
    bool rightValue = right->Evaluate(date, event);
    return operation == LogicalOperation::And
    ? leftValue && rightValue
    : leftValue || rightValue;
}


template<typename T> bool compare(const Comparison cmp, const T& value1, const T& value2) {
    if (cmp == Comparison::Equal) {
        return value1 == value2;
    }
    if (cmp == Comparison::NotEqual) {
        return value1 != value2;
    }
    if (cmp == Comparison::Less) {
        return value1 < value2;
    }
    if (cmp == Comparison::Greater) {
        return value1 > value2;
    }
    if (cmp == Comparison::LessOrEqual) {
        return value1 <= value2;
    }
    if (cmp == Comparison::GreaterOrEqual) {
        return value1 >= value2;
    }

    return false;
}

EventComparisonNode::EventComparisonNode(const Comparison& cmp, const string& valueToCompareWith)
        : cmp(cmp), valueToCompareWith(valueToCompareWith) {}

bool EventComparisonNode::Evaluate(const Date& date, const string& event) const {
    return compare<string>(cmp, event, valueToCompareWith);
}

DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& valueToCompareWith)
        : cmp(cmp), valueToCompareWith(valueToCompareWith) {}

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const {
    return compare<Date>(cmp, date, valueToCompareWith);
}