#include <Physics/Collider/CircleCollider.h>
#include <Physics/Collider/PolygonCollider.h>
#include <gtest/gtest.h>
#include <memory>

TEST(Physics, CollisionWithCircles) {
    auto collider1 = Altseed::CircleCollider::Create();
    auto collider2 = Altseed::CircleCollider::Create();
    collider1->AddRef();
    collider2->AddRef();
    collider1->SetPosition(Altseed::Vector2F(100, 100));
    collider1->SetRadius(250);
    collider2->SetPosition(Altseed::Vector2F(400, 500));
    collider2->SetRadius(350);
    EXPECT_TRUE(collider1->GetIsCollidedWith(collider2));
    collider1->Release();
    collider2->Release();
}

TEST(Physics, CollisionWithPolygons) {
    auto collider1 = Altseed::PolygonCollider::Create();
    auto collider2 = Altseed::PolygonCollider::Create();

    collider1->AddRef();
    collider2->AddRef();

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

    vertexes1->AddRef();
    vertexes2->AddRef();

    collider1->SetVertexes(vertexes1);
    collider1->SetPosition(Altseed::Vector2F(100, 100));
    collider2->SetVertexes(vertexes2);
    collider2->SetPosition(Altseed::Vector2F(200, 150));
    EXPECT_TRUE(collider1->GetIsCollidedWith(collider2));

    vertexes1->Release();
    vertexes2->Release();
    collider1->Release();
    collider2->Release();
}