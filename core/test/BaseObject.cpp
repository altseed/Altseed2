#include <BaseObject.h>
#include <Core.h>
#include <gtest/gtest.h>
#include <thread>

TEST(BaseObject, Basic) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"test", 640, 480, Altseed::CoreOption()));
    auto defaultObjectCount = Altseed::Core::GetInstance()->GetBaseObjectCount();

    auto baseObject = new Altseed::BaseObject();
    EXPECT_EQ(Altseed::Core::GetInstance()->GetBaseObjectCount(), defaultObjectCount + 1);

    EXPECT_EQ(baseObject->GetRef(), 1);
    baseObject->AddRef();
    EXPECT_EQ(baseObject->GetRef(), 2);
    baseObject->Release();
    EXPECT_EQ(baseObject->GetRef(), 1);
    baseObject->Release();

    EXPECT_EQ(Altseed::Core::GetInstance()->GetBaseObjectCount(), defaultObjectCount);

    Altseed::Core::Terminate();
}

TEST(BaseObject, Async) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"test", 640, 480, Altseed::CoreOption()));

    auto baseObject = new Altseed::BaseObject();

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

    EXPECT_EQ(baseObject->GetRef(), 10001);

    for (int i = 0; i < 10001; i++) {
        baseObject->Release();
    }

    Altseed::Core::Terminate();
}

TEST(BaseObject, DisposeInOtherThreadAfterTerminate) {
    EXPECT_TRUE(Altseed::Core::Initialize(u"test", 640, 480, Altseed::CoreOption()));

    auto baseObject = new Altseed::BaseObject();

    Altseed::Core::Terminate();

    std::thread thread1([baseObject]() -> void { baseObject->Release(); });

    thread1.join();
}
