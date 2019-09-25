#include <Core.h>
#include <Graphics/Texture2D.h>
#include <IO/File.h>
#include <gtest/gtest.h>
#include <string>

namespace asd = altseed;

TEST(Texture2D, Base) {
    EXPECT_TRUE(asd::Core::Initialize(u"test", 640, 480, asd::CoreOption()));

    // pack files
    EXPECT_TRUE(asd::File::GetInstance()->Pack(u"TestData/IO/", u"TestData/IO/pack.pack"));

    // add package
    EXPECT_TRUE(asd::File::GetInstance()->AddRootPackage(u"TestData/IO/pack.pack"));

    // load texture, and compare no-package and package without password
    asd::Texture2D* test = nullptr;
    EXPECT_NE(test = asd::Texture2D::Load(u"TestData/IO/AltseedPink.png"), nullptr);
    asd::Texture2D* testPack = nullptr;
    EXPECT_NE(testPack = asd::Texture2D::Load(u"AltseedPink.png"), nullptr);
    EXPECT_EQ(test->GetSize(), testPack->GetSize());
    asd::Texture2D* nonImage = nullptr;
    EXPECT_EQ(nonImage = asd::Texture2D::Load(u"test.txt"), nullptr);
    asd::Texture2D* notExist = nullptr;
    EXPECT_EQ(notExist = asd::Texture2D::Load(u"not_exsist.png"), nullptr);

    // cache test
    asd::Texture2D* testCache = nullptr;
    EXPECT_NE(testCache = asd::Texture2D::Load(u"TestData/IO/AltseedPink.png"), nullptr);
    EXPECT_EQ(test, testCache);

    asd::Core::Terminate();
}

// TODO: add async test case
// TEST(File, StaticFileAsync) {
//    EXPECT_TRUE(asd::Core::Initialize(u"test", 640, 480, asd::CoreOption()));
//
//    // pack files
//    EXPECT_TRUE(asd::File::GetInstance()->Pack(u"TestData/IO/", u"TestData/IO/pack.pack"));
//
//    // add package
//    EXPECT_TRUE(asd::File::GetInstance()->AddRootPackage(u"TestData/IO/pack.pack"));
//
//    asd::Core::Terminate();
//}