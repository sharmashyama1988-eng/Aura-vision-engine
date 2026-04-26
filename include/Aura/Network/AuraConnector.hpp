#pragma once

#include <string>
#include <vector>

namespace aura::network {

    class AuraConnector {
    public:
        AuraConnector();
        ~AuraConnector();

        bool EstablishConnection(const std::string& targetPackage);
        void UnlockResourceAccess();
        void SyncFrameStream();
        float GetLinkQuality() const;

    private:
        bool m_IsConnected;
        std::string m_ActivePackage;
    };

} // namespace aura::network
