#include "NOPFramework.h"

struct NOPSensor
{
    inline static std::atomic<int> counter{ 0 };
    NOP::SharedAttribute<bool> atIsRead{ NOP::BuildAttribute(false) };
    NOP::SharedAttribute<bool> atIsActivated{ NOP::BuildAttribute(false) };
    NOP::SharedPremise prIsActivated{ NOP::BuildPremise<bool>(atIsActivated, true, NOP::Equal()) };
    NOP::SharedPremise prIsNotRead{ NOP::BuildPremise<bool>(atIsRead, false, NOP::Equal()) };
    NOP::SharedRule rlSensor{ NOP::BuildRule(
        NOP::BuildCondition(CONDITION(*prIsActivated && *prIsNotRead), prIsActivated, prIsNotRead),
        NOP::BuildAction(NOP::BuildInstigation([&]() { this->Read(); this->Deactivate(); ++NOPSensor::counter; }))
    )
    };
    void Read() const { atIsRead->SetValue(true); }
    void Activate() const { atIsActivated->SetValue(true); atIsRead->SetValue(false); }
    void Deactivate() const { atIsActivated->SetValue(false); }
};