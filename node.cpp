#include "node.h"

template<typename T>
bool compare(Comparison cmp, const T& a, const T& b) {
	switch (cmp)
	{
	case Comparison::Less:
		return a < b;

	case Comparison::LessOrEqual:
		return a <= b;

	case Comparison::Greater:
		return a > b;

	case Comparison::GreaterOrEqual:
		return a >= b;

	case Comparison::Equal:
		return a == b;

	case Comparison::NotEqual:
		return a != b;
	}

	throw invalid_argument("Invalid comparison operator");
}
bool EmptyNode::Evaluate(const Date& date, const string& event) const {
	return true;
}

DateComparisonNode::DateComparisonNode(Comparison cmp, const Date& date) : cmp_(cmp), date_(date) {}
EventComparisonNode::EventComparisonNode(Comparison cmp, const string& event) : cmp_(cmp), event_(event) {}

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const {
	return compare(cmp_, date, date_);
}


bool EventComparisonNode::Evaluate(const Date& date, const string& event) const {
	return compare(cmp_, event, event_);
}

LogicalOperationNode::LogicalOperationNode(LogicalOperation lo, shared_ptr<Node> left, shared_ptr<Node> right) : 
	lo_(lo), left_(left), right_(right){}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
	switch (lo_)
	{
	case Or:
		return left_->Evaluate(date, event) || right_->Evaluate(date, event);
	case And:
		return left_->Evaluate(date, event) && right_->Evaluate(date, event);
	default:
		throw invalid_argument("invalid logical operation");
		break;
	}
}
