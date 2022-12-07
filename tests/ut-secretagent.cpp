// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <gtest/gtest.h>
#include "dsecretagent.h"
#include "fakeDBus/networkmanagerservice.h"
#include "fakeDBus/secretagentservice.h"

DNETWORKMANAGER_USE_NAMESPACE

class TestDSecretAgent : public testing::Test
{
public:
    static void SetUpTestCase()
    {
        m_nm = new FakeNetworkManagerService();
        m_fakeService = new FakeSecretAgentService();
        m_sa = new DSecretAgent();
    }

    static void TearDownTestCase()
    {
        delete m_sa;
        delete m_fakeService;
        delete m_nm;
    }

    void SetUp() override {}
    void TearDown() override {}

    static inline DSecretAgent *m_sa{nullptr};
    static inline FakeSecretAgentService *m_fakeService{nullptr};
    static inline FakeNetworkManagerService *m_nm{nullptr};
};

TEST_F(TestDSecretAgent, secrets)
{
    auto ret = m_sa->secrets({}, {}, {}, {}, DSecretAgent::SecretFlags{1});
    if (!ret)
        qWarning() << ret.error();
    EXPECT_EQ(true, m_fakeService->m_getSecretTrigger);
}

TEST_F(TestDSecretAgent, cancelSecrets)
{
    auto ret = m_sa->cancelSecrets(2, "");
    if (!ret)
        qWarning() << ret.error();
    EXPECT_EQ(true, m_fakeService->m_cancelGetSecretTrigger);
}

TEST_F(TestDSecretAgent, saveSecret)
{
    auto ret = m_sa->saveSecret({}, 2);
    if (!ret)
        qWarning() << ret.error();
    EXPECT_EQ(true, m_fakeService->m_saveSecretTrigger);
}

TEST_F(TestDSecretAgent, deleteSecret)
{
    auto ret = m_sa->deleteSecret({}, 2);
    if (!ret)
        qWarning() << ret.error();
    EXPECT_EQ(true, m_fakeService->m_deleteSecretTrigger);
}
