#include <BaseObject.h>
#include <Core.h>
#include <gtest/gtest.h>

#include <thread>

#include "TestHelper.h"

TEST(BaseObject, Basic) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::None);
    EXPECT_TRUE(config != nullptr);

    EXPECT_TRUE(Altseed2::Core::Initialize(u"test", 640, 480, config));
    auto defaultObjectCount = Altseed2::Core::GetInstance()->GetBaseObjectCount();

    auto baseObject = new Altseed2::BaseObject();
    EXPECT_EQ(Altseed2::Core::GetInstance()->GetBaseObjectCount(), defaultObjectCount + 1);

    int32_t coreRef = 0;

    EXPECT_EQ(baseObject->GetRef(), 1 + coreRef);
    baseObject->AddRef();
    EXPECT_EQ(baseObject->GetRef(), 2 + coreRef);
    baseObject->Release();
    EXPECT_EQ(baseObject->GetRef(), 1 + coreRef);
    baseObject->Release();

    // call gc
    Altseed2::Core::GetInstance()->DoEvent();

    EXPECT_EQ(Altseed2::Core::GetInstance()->GetBaseObjectCount(), defaultObjectCount);

    Altseed2::Core::Terminate();
}

TEST(BaseObject, Async) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::None);
    EXPECT_TRUE(config != nullptr);
    EXPECT_TRUE(Altseed2::Core::Initialize(u"test", 640, 480, config));

    auto baseObject = new Altseed2::BaseObject();

    std::thread thread1([baseObject]() -> void {
        for (int i = 0; i < 5000; i++) {
            baseObject->AddRef();
        }
    });

    std::thread thread2([baseObject]() -> void {
        for (int i = 0; i < 5000; i++) {
            baseObject->AddRef();
        }
    });

    thread1.join();
    thread2.join();

    int32_t coreRef = 0;

    EXPECT_EQ(baseObject->GetRef(), 10001 + coreRef);

    for (int i = 0; i < 10001; i++) {
        baseObject->Release();
    }

    // call gc
    Altseed2::Core::GetInstance()->DoEvent();

    Altseed2::Core::Terminate();
}

TEST(BaseObject, DisposeInOtherThreadAfterTerminate) {
    auto config = Altseed2TestConfig(Altseed2::CoreModules::None);
    EXPECT_TRUE(config != nullptr);
    EXPECT_TRUE(Altseed2::Core::Initialize(u"test", 640, 480, config));

    auto baseObject = new Altseed2::BaseObject();

    Altseed2::Core::Terminate();

    std::thread thread1([baseObject]() -> void { baseObject->Release(); });

    thread1.join();
}
