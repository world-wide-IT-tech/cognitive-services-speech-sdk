#pragma once
#include <list>
#include "ispxinterfaces.h"
#include "interface_helpers.h"
#include "recognizer.h"


namespace CARBON_IMPL_NAMESPACE() {


class CSpxIntentRecognizer : public CSpxRecognizer, public ISpxIntentRecognizer
{
public:

    CSpxIntentRecognizer();
    ~CSpxIntentRecognizer();

    SPX_INTERFACE_MAP_BEGIN()
        SPX_INTERFACE_MAP_ENTRY(ISpxObjectWithSite)
        SPX_INTERFACE_MAP_ENTRY(ISpxObjectInit)
        SPX_INTERFACE_MAP_ENTRY(ISpxSessionFromRecognizer)
        SPX_INTERFACE_MAP_ENTRY(ISpxNamedProperties)
        SPX_INTERFACE_MAP_ENTRY(ISpxRecognizerEvents)
        SPX_INTERFACE_MAP_ENTRY(ISpxRecognizer)
        SPX_INTERFACE_MAP_ENTRY(ISpxIntentRecognizer)
    SPX_INTERFACE_MAP_END()

    // --- ISpxObjectInit (overrides) ---
    void Init() override;

    // --- ISpxIntentRecognizer ---
    void AddIntentTrigger(const wchar_t* intentId, std::shared_ptr<ISpxTrigger> trigger) override;


private:

    CSpxIntentRecognizer(CSpxIntentRecognizer&&) = delete;
    CSpxIntentRecognizer(const CSpxIntentRecognizer&) = delete;
    CSpxIntentRecognizer& operator=(CSpxIntentRecognizer&&) = delete;
    CSpxIntentRecognizer& operator=(const CSpxIntentRecognizer&) = delete;

    void InitTriggerService();

    std::list<std::shared_ptr<ISpxTrigger>> m_triggers;
    std::weak_ptr<ISpxIntentTriggerService> m_triggerService;
};


} // CARBON_IMPL_NAMESPACE
