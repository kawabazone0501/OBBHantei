#pragma once

#include "Collider.h"

//Collisionmanagerを作成後、staticを使って作成して、なんちゃってC++方式で改装する

bool IsCollingOBBAndOBB(OBBCollider& collider_01_, OBBCollider& collider_02_);
