#include <Physics/Collider/CircleCollider.h>
#include <Physics/Collider/RectangleCollider.h>
#include <Physics/Collider/PolygonCollider.h>
#include <gtest/gtest.h>
#include <memory>

TEST(Physics, CollisionWithCircles) {
    auto collider1 = Altseed::MakeAsdShared<Altseed::CircleCollider>();
    auto collider2 = Altseed::MakeAsdShared<Altseed::CircleCollider>();
    collider1->SetPosition(Altseed::Vector2F(100, 100));
    collider1->SetRadius(250);
    collider2->SetPosition(Altseed::Vector2F(400, 500));
    collider2->SetRadius(350);
    EXPECT_TRUE(collider1->GetIsCollidedWith(collider2));
}

TEST(Physics, CollisionWithRectangles) {
    auto collider1 = Altseed::MakeAsdShared<Altseed::RectangleCollider>();
    auto collider2 = Altseed::MakeAsdShared<Altseed::RectangleCollider>();
    collider1->SetPosition(Altseed::Vector2F(50, 50));
    collider1->SetSize(Altseed::Vector2F(200, 200));
    collider2->SetPosition(Altseed::Vector2F(200, 200));
    collider1->SetSize(Altseed::Vector2F(240, 180));
    EXPECT_TRUE(collider1->GetIsCollidedWith(collider2));
}

TEST(Physics, CollisionWithPolygons) {
    auto collider1 = Altseed::MakeAsdShared<Altseed::PolygonCollider>();
    auto collider2 = Altseed::MakeAsdShared<Altseed::PolygonCollider>();

    auto vertexes1 = Altseed::MakeAsdShared<Altseed::Vector2FArray>();
    vertexes1->Resize(4);
    vertexes1->GetVector()[0] = Altseed::Vector2F(-100, -100);
    vertexes1->GetVector()[1] = Altseed::Vector2F( 100, -100);
    vertexes1->GetVector()[2] = Altseed::Vector2F( 100,  100);
    vertexes1->GetVector()[3] = Altseed::Vector2F(-100,  100);

    auto vertexes2 = Altseed::MakeAsdShared<Altseed::Vector2FArray>();
    vertexes2->Resize(4);
    vertexes2->GetVector()[0] = Altseed::Vector2F(-120, -90);
    vertexes2->GetVector()[1] = Altseed::Vector2F( 120, -90);
    vertexes2->GetVector()[2] = Altseed::Vector2F( 120,  90);
    vertexes2->GetVector()[3] = Altseed::Vector2F(-120,  90);

    collider1->SetVertexes(vertexes1);
    collider1->SetPosition(Altseed::Vector2F(100, 100));
    collider2->SetVertexes(vertexes2);
    collider2->SetPosition(Altseed::Vector2F(200, 150));
    EXPECT_TRUE(collider1->GetIsCollidedWith(collider2));
}