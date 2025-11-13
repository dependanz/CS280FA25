#ifndef agdemo_value_h
#define agdemo_value_h

enum ValueType {
    VALUE_INT,
    VALUE_REAL,
    VALUE_ERROR
};

class CalcValue {
private:
    ValueType type;
    union {
        long intValue;
        double realValue;
    };

public:
    CalcValue() : type(VALUE_ERROR), intValue(0) {}
    CalcValue(long v) : type(VALUE_INT), intValue(v) {}
    CalcValue(double v) : type(VALUE_REAL), realValue(v) {}

    ValueType getType() const { return type; }
    long getInt() const { return intValue; }
    double getReal() const { return realValue; }

    CalcValue operator+(const CalcValue &other) const {
        if (type == VALUE_ERROR || other.type == VALUE_ERROR) {
            return CalcValue();
        }
        if (type == VALUE_REAL || other.type == VALUE_REAL) {
            double a = (type == VALUE_REAL) ? realValue : (double)(intValue);
            double b = (other.type == VALUE_REAL) ? other.realValue : (double)(other.intValue);
            return CalcValue(a + b);
        } else {
            return CalcValue(intValue + other.intValue);
        }
    }

    friend std::ostream& operator<<(std::ostream &os, const CalcValue &val) {
        switch (val.type) {
            case VALUE_INT:
                os << val.intValue;
                break;
            case VALUE_REAL:
                os << val.realValue;
                break;
            case VALUE_ERROR:
                os << "ERR";
                break;
        }
        return os;
    }
};

#endif