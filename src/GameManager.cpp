#include "GameManager.h"

GameManager::GameManager(){
    ecsManager.init();
    //entities = new Entity[maxEntities];
    ecsManager.registerComponent<TransformComponent>();
    ecsManager.registerComponent<PhysicsComponent>();
    ecsManager.registerComponent<RenderComponent>();
    ecsManager.registerComponent<Tag>();

    //----- TODO - handle deletion of Collider *s - should gameManager or scene keep array of Collider *s?
    ecsManager.registerComponent<Collider *>();

    renderSystem = ecsManager.registerSystem<RenderSystem>();
    ecsManager.followComponent<RenderSystem, TransformComponent>();
    ecsManager.followComponent<RenderSystem, RenderComponent>();
    
    physicsSystem = ecsManager.registerSystem<PhysicsSystem>();
    ecsManager.followComponent<PhysicsSystem, TransformComponent>();
    ecsManager.followComponent<PhysicsSystem, PhysicsComponent>();
    ecsManager.followComponent<PhysicsSystem, Collider *>();

    //setup default context --- TODO - make a file to read this from on startup
    defaultContext = ecsManager.registerSystem<InputContext>();
    ecsManager.followComponent<InputContext, PhysicsComponent>();
    ecsManager.followComponent<InputContext, Tag>();

    inputManager.addContext(defaultContext);

    SceneLoader sceneLoader;
    sceneLoader.readFile("scene1copy.json", ecsManager, entities);

    //createPaddles();
    //createWalls();
    //createBalls();


};  

void GameManager::ProcessInput(){
    inputManager.processInput();
}

void GameManager::Update(float deltaTime){

    physicsSystem->Update(deltaTime);
}

void GameManager::Render(SDL_Renderer * renderer){
    
    renderSystem->Render(renderer);
}

void GameManager::createWalls(){
    //left wall
    int currentIndex = ecsManager.getLivingEntityCount();
    entities[currentIndex] = ecsManager.createEntity();

    TransformComponent leftWall;
    leftWall.width = 30;
    leftWall.height = 600;
    leftWall.x = 0 - leftWall.width / 2;
    leftWall.y = 0 + leftWall.height / 2;
    ecsManager.addComponent<TransformComponent>(entities[currentIndex], leftWall);
    
    PhysicsComponent leftWallPhys;
    leftWallPhys.velocity.setX(0);
    leftWallPhys.velocity.setY(0);
    leftWallPhys.isKinematic = true;
    leftWallPhys.elasticity = 0;
    leftWallPhys.mass = INFINITY;//FLT_MAX;
    ecsManager.addComponent<PhysicsComponent>(entities[currentIndex], leftWallPhys);
    
    BoxCollider *leftWallCollider = new BoxCollider(leftWall);
    ecsManager.addComponent<Collider *>(entities[currentIndex], leftWallCollider); 

    //right wall
    currentIndex = ecsManager.getLivingEntityCount();
    entities[currentIndex] = ecsManager.createEntity();

    TransformComponent rightWall;
    rightWall.width = 30;
    rightWall.height = 600;
    rightWall.x = 800 + rightWall.width / 2;
    rightWall.y = 0 + rightWall.height / 2;
    ecsManager.addComponent<TransformComponent>(entities[currentIndex], rightWall);
    
    PhysicsComponent rightWallPhys;
    rightWallPhys.velocity.setX(0);
    rightWallPhys.velocity.setY(0);
    rightWallPhys.isKinematic = true;
    rightWallPhys.elasticity = 0;
    rightWallPhys.mass = INFINITY;//FLT_MAX;
    ecsManager.addComponent<PhysicsComponent>(entities[currentIndex], rightWallPhys);
    
    BoxCollider *rightWallCollider = new BoxCollider(rightWall);
    ecsManager.addComponent<Collider *>(entities[currentIndex], rightWallCollider);

    //top wall
    currentIndex = ecsManager.getLivingEntityCount();
    entities[currentIndex] = ecsManager.createEntity();

    TransformComponent topWall;
    topWall.width = 800;
    topWall.height = 30;
    topWall.x = 0 + topWall.width / 2;
    topWall.y = 0 - topWall.height / 2;
    ecsManager.addComponent<TransformComponent>(entities[currentIndex], topWall);
    
    PhysicsComponent topWallPhys;
    topWallPhys.velocity.setX(0);
    topWallPhys.velocity.setY(0);
    topWallPhys.isKinematic = true;
    topWallPhys.elasticity = 0;
    topWallPhys.mass = INFINITY;//FLT_MAX;
    ecsManager.addComponent<PhysicsComponent>(entities[currentIndex], topWallPhys);
    
    BoxCollider *topWallCollider = new BoxCollider(topWall);
    ecsManager.addComponent<Collider *>(entities[currentIndex], topWallCollider);

    //bottom wall
    currentIndex = ecsManager.getLivingEntityCount();
    entities[currentIndex] = ecsManager.createEntity();

    TransformComponent bottomWall;
    bottomWall.width = 800;
    bottomWall.height = 30;
    bottomWall.x = 0 + bottomWall.width / 2;
    bottomWall.y = 600 + bottomWall.height / 2;
    ecsManager.addComponent<TransformComponent>(entities[currentIndex], bottomWall);
    
    PhysicsComponent bottomWallPhys;
    bottomWallPhys.velocity.setX(0);
    bottomWallPhys.velocity.setY(0);
    bottomWallPhys.isKinematic = true;
    bottomWallPhys.elasticity = 0;
    bottomWallPhys.mass = INFINITY;//FLT_MAX;
    ecsManager.addComponent<PhysicsComponent>(entities[currentIndex], bottomWallPhys);
    
    BoxCollider *bottomWallCollider = new BoxCollider(bottomWall);
    ecsManager.addComponent<Collider *>(entities[currentIndex], bottomWallCollider);
}

void GameManager::createPaddles(){
    int paddleWidth = 15;
    int paddleHeight = 100;

    //make paddle 1
    int currentIndex = ecsManager.getLivingEntityCount();
    entities[currentIndex] = ecsManager.createEntity();

    TransformComponent t1;
    t1.width = paddleWidth;
    t1.height = paddleHeight;
    t1.x = 20 + t1.width / 2;
    t1.y = 20 + t1.height / 2;
    ecsManager.addComponent<TransformComponent>(entities[currentIndex], t1);
    
    PhysicsComponent phys1;
    phys1.velocity.setX(0);
    phys1.velocity.setY(0);
    phys1.isKinematic = true;
    phys1.elasticity = 0;
    phys1.mass = INFINITY;//FLT_MAX;
    ecsManager.addComponent<PhysicsComponent>(entities[currentIndex], phys1);
    
    RenderComponent rend1;
    rend1.color.red = 0;
    rend1.color.green = 255;
    rend1.color.blue = 0;
    rend1.color.alpha = 255;
    rend1.shape = RECT;
    ecsManager.addComponent<RenderComponent>(entities[currentIndex], rend1);

    BoxCollider *box1 = new BoxCollider(t1);
    ecsManager.addComponent<Collider *>(entities[currentIndex], box1);
    
    //make paddle 2
    currentIndex = ecsManager.getLivingEntityCount();
    entities[currentIndex] = ecsManager.createEntity();
    //ecsManager.setSignature(entities[currentIndex], sig1);

    TransformComponent t2;
    t2.width = paddleWidth;
    t2.height = paddleHeight;
    t2.x = 800 - t2.width / 2 - 20;
    t2.y = 20 + t2.height / 2;
    ecsManager.addComponent<TransformComponent>(entities[currentIndex], t2);
    PhysicsComponent phys2;
    phys2.velocity.setX(0);
    phys2.velocity.setY(0);
    phys2.isKinematic = true;
    phys2.elasticity = 0;
    phys2.mass = INFINITY;//FLT_MAX;
    ecsManager.addComponent<PhysicsComponent>(entities[currentIndex], phys2);
    RenderComponent rend2;
    rend2.color.red = 0;
    rend2.color.green = 0;
    rend2.color.blue = 255;
    rend2.color.alpha = 255;
    rend2.shape = RECT;
    ecsManager.addComponent<RenderComponent>(entities[currentIndex], rend2);
    
    BoxCollider *box2 = new BoxCollider(t2);
    ecsManager.addComponent<Collider *>(entities[currentIndex], box2);
}

void GameManager::createBalls(){
    //create balls
    for(int i = 0; i < 5; i++)
    {
        int currentIndex = ecsManager.getLivingEntityCount();
        entities[currentIndex] = ecsManager.createEntity();

        TransformComponent ballTransform;
        ballTransform.width = 50;
        ballTransform.height = 50;
        ballTransform.x = rand() % 700 + 50;//400 - ballTransform.width / 2;
        ballTransform.y = rand() % 500 + 50;//300 - ballTransform.height / 2;
        ecsManager.addComponent<TransformComponent>(entities[currentIndex], ballTransform);

        PhysicsComponent ballPhysics;
        ballPhysics.velocity.setX(rand() % 50 + 200);//xVelocity = (rand() % 50 + 200);// * (rand() % 1 - ); //randomize direction
        ballPhysics.velocity.setY(rand() % 50 + 50); //yVelocity = rand() % 50 + 50;
        ballPhysics.isKinematic = false;
        ballPhysics.elasticity = 1;
        ballPhysics.mass = 1;
        ecsManager.addComponent<PhysicsComponent>(entities[currentIndex], ballPhysics);

        RenderComponent ballRender;
        ballRender.color.red = 255;
        ballRender.color.green = 255;
        ballRender.color.blue = 255;
        ballRender.color.alpha = 255;
        ballRender.shape = CIRCLE;
        ecsManager.addComponent<RenderComponent>(entities[currentIndex], ballRender);

        CircleCollider *ballCollider = new CircleCollider(ballTransform);
        ecsManager.addComponent<Collider *>(entities[currentIndex], ballCollider);
    }
}

void GameManager::deletePaddles(){
    ecsManager.deleteEntity(entities[0]);
    ecsManager.deleteEntity(entities[1]);
}

void GameManager::saveScene(){
    SceneSaver sceneSaver;
    sceneSaver.writeFile("scene1copy.json", ecsManager, entities, ecsManager.getLivingEntityCount());
}