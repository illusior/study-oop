#pragma once

#include "../std_lib.h"

#include "COperand.h"

class Variable : public Operand
{
public:
	Variable();
	Variable(const Value value);

	Value GetValue() const override;

private:

	Value m_value;
	inline const static Value m_nanValue = std::numeric_limits<Value>::signaling_NaN();
};