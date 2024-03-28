#include "PhysicsSystem.h"
#ifdef DEBUG
#include <SDL.h>
#endif

void PhysicsSystem::Update(float deltaTime){
    updatePositions(deltaTime);

    resolveCollisions(deltaTime);
}

void PhysicsSystem::updatePositions(float deltaTime){
    for(std::set<Entity>::iterator entity = entities.begin(); entity != entities.end(); entity++){
        auto &transform = ecsManager.getComponent<TransformComponent>(*entity);
        auto &rigidbody = ecsManager.getComponent<PhysicsComponent>(*entity);
        
        auto collider = ecsManager.getComponent<Collider *>(*entity);

        transform.x += rigidbody.velocity.x * deltaTime;
        transform.y += rigidbody.velocity.y * deltaTime;

        //update collider before testing bounds collisions
        collider->updatePosition(transform);
    }
}

void PhysicsSystem::resolveCollisions(float deltaTime){
    for(std::set<Entity>::iterator entity = entities.begin(); entity != entities.end(); entity++){
    
    auto &transform = ecsManager.getComponent<TransformComponent>(*entity);
    auto &rigidbody = ecsManager.getComponent<PhysicsComponent>(*entity);
    
    auto collider = ecsManager.getComponent<Collider *>(*entity);

    // --- TODO - this is just brute force. Need to implement grid or quadtree system
    for(std::set<Entity>::iterator otherEntity = std::next(entity, 1); otherEntity != entities.end(); otherEntity++)/*(auto &otherEntity : entities)*/{
        if (entity != otherEntity){
            auto otherCollider = ecsManager.getComponent<Collider *>(*otherEntity);
            if(collider->isColliding(*otherCollider)){

                //get surface normal vector of collision
                Vector2 collisionNorm = collider->getSurfaceNormalOfCollision(*otherCollider);
                
                //---- TODO - back up positions along negative normalized velocities until no longer colliding
                auto &otherTransform = ecsManager.getComponent<TransformComponent>(*otherEntity);
                auto &otherRigidbody = ecsManager.getComponent<PhysicsComponent>(*otherEntity);

                //---- TODO - should this handle an optional value from normalized
                // instead of relying on normalized to send (0,0) in case of 0 velocity?

                //--- TODO - try to scale this based on the ratio of the magnitudes
                Vector2 v1Norm = Vector2::normalized(-rigidbody.velocity);// * deltaTime;
                Vector2 v2Norm = Vector2::normalized(-otherRigidbody.velocity);// * deltaTime;
                
                //reverse 25% at a time until not colliding anymore
                float reversePercentage = 1;//.25;
                int reverseIteration = 1;

                //reverse object movements until they don't collide anymore
                do {
                    //--- TODO - maybe...try to calculate exact impact time and rewind to that point
                    //get walls of each collider

                    // w1 - v1t = w2 - v2t
                    // w1 - w2 = v1t - v2t
                    // w1 - w2 = t(v1 - v2)
                    // t = (w1 - w2) / (v1 - v2)

                    //calculate amount of time to reverse
                    //float impactTime = ()


                    transform.x -= rigidbody.velocity.x * (deltaTime * reversePercentage);
                    transform.y -= rigidbody.velocity.y * (deltaTime * reversePercentage);
                    collider->updatePosition(transform);

                    otherTransform.x -= otherRigidbody.velocity.x * (deltaTime * reversePercentage);
                    otherTransform.y -= otherRigidbody.velocity.y * (deltaTime * reversePercentage);
                    otherCollider->updatePosition(otherTransform);
                    
                    reverseIteration++;
                    //if(reverseIteration > 4) break; //should be a max of 4 because that would undo frame entirely, but break just in case

                } while(collider->isColliding(*otherCollider));
                
                #ifdef DEBUG
                    if(transform.x > 900 || transform.x < -100 || transform.y < -100 || transform.y > 700){
                        //if transform of either object in collision is absurd
                    }
                    if((abs(rigidbody.velocity.x) > 500) || abs(rigidbody.velocity.y) > 500 || abs(otherRigidbody.velocity.x) > 500 || abs(otherRigidbody.velocity.y) > 500){
                        //if velocity of either object in collision is absurd
                    }
                    #endif // DEBUG
                //https://gamedev.stackexchange.com/questions/136073/how-does-one-calculate-the-surface-normal-in-2d-collisions
                {/*
                //get distance between centers of objects
                Vector2 center = collider->getCenter();
                Vector2 otherCenter = otherCollider->getCenter();
                Vector2 distanceVector = center - otherCenter;
                //get x extent of object 1
                float ex = otherCollider->extentX();
                //get unit vector of x axis ---- TODO - currently doesn't work for rotated objects
                Vector2 ux = Vector2::normalized(Vector2(ex, 0));
                
                //project distance vector onto ux to find distance along x axis to center of object 2
                float dx = Vector2::dotProduct(distanceVector, ux);
                //if dx > ex, this means the center of object 2 is farther from the center
                //of object 1 than the wall, and therefore the collision is happening
                // along that wall. Also check in the negative for opposite wall.
                //if not either of these, collision is happening along a wall parallel to ux
                //and dx tells you how far from center of object 1 the collision is
                if(dx > ex){
                    dx = ex;
                }
                if(dx < -ex){
                    dx = -ex;
                }

                //same for y axis as above for x
                float ey = otherCollider->extentY();
                Vector2 uy = Vector2::normalized(Vector2(0, ey));
                float dy = Vector2::dotProduct(distanceVector, uy);
                if(dy > ey){
                    dy = ey;
                }
                if(dy < -ey){
                    dy = -ey;
                }

                //calculate closest point p on object 1 to center of object 2
                Vector2 collisionPoint = otherCenter + dx*ux + dy*uy;

                //calculate surface vector norm for collision by
                Vector2 collisionNorm = Vector2::normalized(center - collisionPoint);
                
                }*/}

                //solve for k, the scale factor of the impulse to be applied
                //https://gamemath.com/book/dynamics.html#collision_response
                Vector2 relativeVelocity = otherRigidbody.velocity - rigidbody.velocity;
                
                //calculate new velocities for both objects
                //don't calculate new velocity if object is kinematic
                if(!rigidbody.isKinematic){
                    float k1 = ((rigidbody.elasticity + 1) * (Vector2::dotProduct(relativeVelocity, collisionNorm))) / ((1 / rigidbody.mass + 1 / otherRigidbody.mass) * Vector2::dotProduct(collisionNorm, collisionNorm));
                    rigidbody.velocity = rigidbody.velocity + ((k1 * collisionNorm) / rigidbody.mass);
                }
                if(!otherRigidbody.isKinematic){
                    float k2 = ((otherRigidbody.elasticity + 1) * (Vector2::dotProduct(relativeVelocity, collisionNorm))) / ((1 / rigidbody.mass + 1 / otherRigidbody.mass) * Vector2::dotProduct(collisionNorm, collisionNorm));
                    otherRigidbody.velocity = otherRigidbody.velocity - ((k2 * collisionNorm) / otherRigidbody.mass);
                }

                //update positions to correct for the amount reversed and new velocities
                /*transform.x += rigidbody.velocity.x * deltaTime * (reversePercentage * (4 - reverseIteration));
                transform.y += rigidbody.velocity.y * deltaTime * (reversePercentage * (4 - reverseIteration));

                otherTransform.x += rigidbody.velocity.x * deltaTime * (reversePercentage * (4 - reverseIteration));
                otherTransform.y += rigidbody.velocity.y * deltaTime * (reversePercentage * (4 - reverseIteration));
                */
               
                #ifdef DEBUG
                    if(transform.x > 900 || transform.x < -100 || transform.y < -100 || transform.y > 700){
                        //if transform of either object in collision is absurd
                    }
                    if((abs(rigidbody.velocity.x) > 700) || abs(rigidbody.velocity.y) > 700 || abs(otherRigidbody.velocity.x) > 700 || abs(otherRigidbody.velocity.y) > 700){
                        //if velocity of either object in collision is absurd
                    }
                    if(rigidbody.velocity.x == 0 && rigidbody.velocity.y == 0 && otherRigidbody.velocity.x == 0 && otherRigidbody.velocity.y == 0){
                        //if both velocities are zero and objects are stuck together
                    }
                #endif // DEBUG
            }
        }
    }

    //re-update collider after resolving bounds collisions
    collider->updatePosition(transform);
}
}