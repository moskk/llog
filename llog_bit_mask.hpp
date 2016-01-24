#ifndef LLOG_BIT_MASK_HPP
#define LLOG_BIT_MASK_HPP

// абстрактное битовое поле
template<typename underlying_t, typename value_t, underlying_t dflt>
class bit_mask
{
public:

    bit_mask(){}
    bit_mask(value_t v):val(v){}
    bit_mask(const bit_mask& v):val(v.val){}
    inline bit_mask& operator = (const bit_mask& v){val = v.val;return *this;}
    inline bit_mask& operator = (const value_t& v){val = v;return *this;}

    // установить все установленные биты из переданного поля
    inline bit_mask& operator + (const bit_mask& v){val |= v.val;return *this;}

    // сбросить все биты, установленные в переданном поле
    inline bit_mask& operator - (const bit_mask& v){val &= !v.val;return *this;}

    // есть ли совпадающие установленные биты в двух полях
    inline bool operator () (const bit_mask& v) const {return val&v.val;}

    // установлен ли данный бит
    inline bool operator () (value_t v) const {return val&v;}
protected:
    underlying_t val = dflt;
};

#endif // LLOG_BIT_MASK_HPP
