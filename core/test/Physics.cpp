#include <Physics/Collider/CircleCollider.h>
#include <Physics/Collider/PolygonCollider.h>
#include <Physics/Collider/ShapeCollider.h>
#include <gtest/gtest.h>

#include <memory>

TEST(Physics, CollisionWithCircles) {
    auto collider1 = Altseed2::MakeAsdShared<Altseed2::CircleCollider>();
    auto collider2 = Altseed2::MakeAsdShared<Altseed2::CircleCollider>();
    collider1->SetPosition(Altseed2::Vector2F(100, 100));
    collider1->SetRadius(250);
    collider2->SetPosition(Altseed2::Vector2F(400, 500));
    collider2->SetRadius(350);
    EXPECT_TRUE(collider1->GetIsCollidedWith(collider2));
}

TEST(Physics, CollisionWithEdges) {
    auto collider1 = Altseed2::MakeAsdShared<Altseed2::EdgeCollider>();
    auto collider2 = Altseed2::MakeAsdShared<Altseed2::EdgeCollider>();
    collider1->SetPoint1(Altseed2::Vector2F(100, 100));
    collider1->SetPoint2(Altseed2::Vector2F(200, 200));
    collider2->SetPoint1(Altseed2::Vector2F(200, 100));
    collider2->SetPoint2(Altseed2::Vector2F(100, 200));
    EXPECT_TRUE(collider1->GetIsCollidedWith(collider2));
}

TEST(Physics, CollisionWithShapes) {
    auto collider1 = Altseed2::MakeAsdShared<Altseed2::ShapeCollider>();
    auto collider2 = Altseed2::MakeAsdShared<Altseed2::ShapeCollider>();
    auto vs1 = Altseed2::Vector2FArray::Create(4);
    auto vs2 = Altseed2::Vector2FArray::Create(4);

    vs1->GetVector()[0] = Altseed2::Vector2F(0, 0);
    vs1->GetVector()[1] = Altseed2::Vector2F(200, 0);
    vs1->GetVector()[2] = Altseed2::Vector2F(200, 200);
    vs1->GetVector()[3] = Altseed2::Vector2F(0, 200);
    vs2->GetVector()[0] = Altseed2::Vector2F(0, 0);
    vs2->GetVector()[1] = Altseed2::Vector2F(240, 0);
    vs2->GetVector()[2] = Altseed2::Vector2F(240, 180);
    vs2->GetVector()[3] = Altseed2::Vector2F(0, 180);

    collider1->SetPosition(Altseed2::Vector2F(50, 50));
    collider1->SetVertexes(vs1);
    collider2->SetPosition(Altseed2::Vector2F(200, 200));
    collider2->SetVertexes(vs2);
    EXPECT_TRUE(collider1->GetIsCollidedWith(collider2));
}

TEST(Physics, CollisionWithPolygons) {
    auto collider1 = Altseed2::MakeAsdShared<Altseed2::PolygonCollider>();
    auto collider2 = Altseed2::MakeAsdShared<Altseed2::PolygonCollider>();

    auto vertexes1 = Altseed2::MakeAsdShared<Altseed2::Vector2FArray>();
    vertexes1->Resize(4);
    vertexes1->GetVector()[0] = Altseed2::Vector2F(-100, -100);
    vertexes1->GetVector()[1] = Altseed2::Vector2F(100, -100);
    vertexes1->GetVector()[2] = Altseed2::Vector2F(100, 100);
    vertexes1->GetVector()[3] = Altseed2::Vector2F(-100, 100);

    auto vertexes2 = Altseed2::MakeAsdShared<Altseed2::Vector2FArray>();
    vertexes2->Resize(4);
    vertexes2->GetVector()[0] = Altseed2::Vector2F(-120, -90);
    vertexes2->GetVector()[1] = Altseed2::Vector2F(120, -90);
    vertexes2->GetVector()[2] = Altseed2::Vector2F(120, 90);
    vertexes2->GetVector()[3] = Altseed2::Vector2F(-120, 90);

    collider1->SetVertexes(vertexes1);
    collider1->SetPosition(Altseed2::Vector2F(100, 100));
    collider2->SetVertexes(vertexes2);
    collider2->SetPosition(Altseed2::Vector2F(200, 150));
    collider1->SetDefaultIndexBuffer();
    collider2->SetDefaultIndexBuffer();
    EXPECT_TRUE(collider1->GetIsCollidedWith(collider2));
}

TEST(Physics, CollisionWithPolygonsIB) {
    auto collider1 = Altseed2::MakeAsdShared<Altseed2::PolygonCollider>();
    auto collider2 = Altseed2::MakeAsdShared<Altseed2::PolygonCollider>();

    auto vertexes1 = Altseed2::MakeAsdShared<Altseed2::Vector2FArray>();
    vertexes1->Resize(4);
    vertexes1->GetVector()[0] = Altseed2::Vector2F(-100, 0);
    vertexes1->GetVector()[1] = Altseed2::Vector2F(0, -100);
    vertexes1->GetVector()[2] = Altseed2::Vector2F(0, 0);
    vertexes1->GetVector()[3] = Altseed2::Vector2F(-100, 0);

    auto vertexes2 = Altseed2::MakeAsdShared<Altseed2::Vector2FArray>();
    vertexes2->Resize(8);
    vertexes2->GetVector()[0] = Altseed2::Vector2F(10, 10);
    vertexes2->GetVector()[1] = Altseed2::Vector2F(30, 10);
    vertexes2->GetVector()[2] = Altseed2::Vector2F(30, 30);
    vertexes2->GetVector()[3] = Altseed2::Vector2F(10, 30);
    vertexes2->GetVector()[4] = Altseed2::Vector2F(-100, -50);
    vertexes2->GetVector()[5] = Altseed2::Vector2F(-100, -100);
    vertexes2->GetVector()[6] = Altseed2::Vector2F(-50, -100);
    vertexes2->GetVector()[7] = Altseed2::Vector2F(-50, -100);

    collider1->SetVertexes(vertexes1);
    collider1->SetPosition(Altseed2::Vector2F(100, 100));
    collider2->SetVertexes(vertexes2);
    collider2->SetPosition(Altseed2::Vector2F(200, 150));
    collider1->SetDefaultIndexBuffer();

    auto ib = Altseed2::MakeAsdShared<Altseed2::Int32Array>();
    ib->Resize(6);
    ib->GetVector()[0] = 4;
    ib->GetVector()[1] = 5;
    ib->GetVector()[2] = 6;
    ib->GetVector()[3] = 4;
    ib->GetVector()[4] = 6;
    ib->GetVector()[5] = 7;

    collider2->SetBuffers(ib);
    EXPECT_TRUE(collider1->GetIsCollidedWith(collider2));
}