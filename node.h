#pragma once
#include <string>
#include <memory>
#include "date.h"

using namespace std;

enum Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};

enum LogicalOperation
{
	And,
	Or
};

class Node
{
public:
	virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

class EmptyNode : public Node
{
public:
	bool Evaluate(const Date& date, const string& event) const override;
};

class DateComparisonNode : public Node
{
public:
	DateComparisonNode(Comparison cmp, const Date& date);
	bool Evaluate(const Date& date, const string& event) const override;

private:
	const Comparison cmp_;
	const Date date_;
};

class EventComparisonNode : public Node
{
public:
	EventComparisonNode(Comparison cmp, const string& event);
	bool Evaluate(const Date& date, const string& event) const override;
private:
	const Comparison cmp_;
	const string event_;
};

class LogicalOperationNode : public Node
{
public:
	LogicalOperationNode(LogicalOperation lo, shared_ptr<Node> left, shared_ptr<Node> right);
	bool Evaluate(const Date& date, const string& event) const override;
private:
	LogicalOperation lo_;
	const shared_ptr<Node> left_, right_;
};