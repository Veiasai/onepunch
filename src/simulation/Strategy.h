#pragma once

namespace simulator
{
class BaseStrategy
{
public:
    explicit BaseStrategy();
    virtual ~BaseStrategy();

    virtual void onUnderlyingChanged() = 0;
    virtual void onOptionChanged() = 0;

protected:
    void buyUnderlying();
    void sellUnderlying();
    void buyOption();
    void sellOption();
};

} // namespace simulator
