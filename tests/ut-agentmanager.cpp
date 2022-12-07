// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <gtest/gtest.h>
#include "dagentmanager.h"
#include "fakeDBus/agentmanagerservice.h"
#include "fakeDBus/networkmanagerservice.h"

DNETWORKMANAGER_USE_NAMESPACE

class TestDAgentManager : public testing::Test
{
public:
    static void SetUpTestCase()
    {
        m_nm = new FakeNetworkManagerService();
        m_fakeService = new FakeAgentManagerService();
        m_am = new DAgentManager();
    }

    static void TearDownTestCase()
    {
        delete m_am;
        delete m_fakeService;
        delete m_nm;
    }

    void SetUp() override {}
    void TearDown() override {}

    static inline DAgentManager *m_am{nullptr};
    static inline FakeAgentManagerService *m_fakeService{nullptr};
    static inline FakeNetworkManagerService *m_nm{nullptr};
};

TEST_F(TestDAgentManager, registerAgent)
{
    auto ret = m_am->registerAgent({});
    if (!ret)
        qWarning() << ret.error();
    EXPECT_EQ(true, m_fakeService->m_registerTrigger);
}

TEST_F(TestDAgentManager, unregisterAgent)
{
    auto ret = m_am->unregisterAgent();
    if (!ret)
        qWarning() << ret.error();
    EXPECT_EQ(true, m_fakeService->m_unregisterTrigger);
}

TEST_F(TestDAgentManager, registerWithCapabilities)
{
    auto ret = m_am->registerWithCapabilities({}, NMSecretAgentCapabilities::VPNHints);
    if (!ret)
        qWarning() << ret.error();
    EXPECT_EQ(true, m_fakeService->m_registerWithCapabilitiesTrigger);
}
