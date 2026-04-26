#pragma once

#include <string>
#include <vector>

namespace aura::network {

    class AuraConnector {
    public:
        AuraConnector();
        ~AuraConnector();

        // Connects Aura Engine to an external system process (like a Camera App)
        bool EstablishConnection(const std::string& targetPackage);

        // Grants "Freedom" to engine files by virtualizing access paths
        void UnlockResourceAccess();
        void SyncFrameStream();
        float GetLinkQuality() const;

    private:
        bool ValidatePackage(const std::string& pkg);
        void OpenIPCChannel();
        
        bool m_IsConnected;
        std::string m_ActivePackage;
    };

} // namespace aura::network
