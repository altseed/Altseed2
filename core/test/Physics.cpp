#include <Physics/Collider/CircleCollider.h>
#include <Physics/Collider/PolygonCollider.h>
#include <gtest/gtest.h>
#include <memory>

TEST(Physics, Collision) {
    std::shared_ptr<Altseed::CircleCollider> collider1 = Altseed::MakeAsdShared<Altseed::CircleCollider>();
    std::shared_ptr<Altseed::CircleCollider> collider2 = Altseed::MakeAsdShared<Altseed::CircleCollider>();
    collider1->AddRef();
    collider2->AddRef();
    collider1->SetPositoin(Altseed::Vector2F(100, 100));
    collider1->SetRadius(250);
    collider2->SetPositoin(Altseed::Vector2F(400, 500));
    collider2->SetRadius(350);
    EXPECT_TRUE(collider1->GetIsCollidedWith(collider2));
    collider1->Release();
    collider2->Release();
}