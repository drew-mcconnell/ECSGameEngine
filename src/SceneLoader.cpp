#include "SceneLoader.h"

std::string SceneLoader::removeQuotesAndColon(std::string text){
    std::size_t firstQuotePos = text.find("\"");        
    std::size_t secondQuotePos = text.find("\"", firstQuotePos+1);
    
    return text.substr(firstQuotePos+1, secondQuotePos - firstQuotePos-1);
}

std::string SceneLoader::removeEndComma(std::string text){
    //will return from beginning to before comma
    //if no comma found, find(",") will return last() and therefore will include all characters
    return text.substr(0, text.find(","));
}

TransformComponent SceneLoader::readTransform(std::ifstream &sceneFile){
    TransformComponent t;

    std::string text;

    //get open brace {
    sceneFile >> text;
    assert(text == "{");

    //use loop so variables can be in any order or left out
    while(true){
        sceneFile >> text;
        text = removeQuotesAndColon(text);

        if(text.find("}") != -1){
            break;
        }

        std::string num;
        sceneFile >> num;

        if(text == "width"){  
            t.width = std::stof(num);
        }
        else if(text == "height"){
            t.height = std::stof(num);
        }
        else if(text == "x"){
            t.x = std::stof(num);
        }
        else if(text == "y"){
            t.y = std::stof(num);
        }
    }

    return t;
}

PhysicsComponent SceneLoader::readRigidbody(std::ifstream &sceneFile){
    PhysicsComponent rb;

    std::string text;

    //get open brace {
    sceneFile >> text;
    assert(text == "{");

    //use loop so variables can be in any order or left out
    while(true){
        sceneFile >> text;
        text = removeQuotesAndColon(text);

        if(text.find("}") != -1){
            break;
        }

        if(text == "velocityX"){  
            std::string num;
            sceneFile >> num;
            rb.velocity.x = std::stof(num);
        }
        else if(text == "velocityY"){
            std::string num;
            sceneFile >> num;
            rb.velocity.y = std::stof(num);
        }
        else if(text == "isKinematic"){
            bool isKin;
            sceneFile >> std::boolalpha >> isKin;
            rb.isKinematic = isKin;

            //get rid of comma after boolean
            sceneFile >> text;
        }
        else if(text == "elasticity"){
            std::string num;
            sceneFile >> num;
            rb.elasticity = std::stof(num);
        }
        else if(text == "mass"){
            std::string num;
            sceneFile >> num;

            if(num == "\"INFINITY\""){
                num = removeQuotesAndColon(num);
            }

            rb.mass = std::stof(num);
        }
    }

    return rb;
}

RenderComponent SceneLoader::readRender(std::ifstream &sceneFile){
    RenderComponent r;

    std::string text;

    //get open brace {
    sceneFile >> text;
    assert(text == "{");

    //use loop so variables can be in any order or left out
    while(true){
        sceneFile >> text;
        text = removeQuotesAndColon(text);

        if(text.find("}") != -1){
            break;
        }

        if(text == "red"){  
            std::string num;
            sceneFile >> num;
            r.color.red = std::stof(num);
        }
        else if(text == "green"){
            std::string num;
            sceneFile >> num;
            r.color.green = std::stof(num);
        }
        else if(text == "blue"){
            std::string num;
            sceneFile >> num;
            r.color.blue = std::stof(num);
        }
        else if(text == "alpha"){
            std::string num;
            sceneFile >> num;
            r.color.alpha = std::stof(num);
        }
        else if(text == "shape"){
            std::string shape;
            sceneFile >> shape;
            shape = removeQuotesAndColon(shape);

            if(shape == "CIRCLE"){
                r.shape = CIRCLE;
            }
            else{
                r.shape = RECT;
            }
        }
    }

    return r;
}

bool SceneLoader::readBoxCollider(std::ifstream &sceneFile){
    
    std::string text;

    bool hasBoxCollider;
    sceneFile >> std::boolalpha >> hasBoxCollider;

    //get rid of comma after boolean
    sceneFile >> text;

    return hasBoxCollider;
}

bool SceneLoader::readCircleCollider(std::ifstream &sceneFile){
    std::string text;

    bool hasCircleCollider;
    sceneFile >> std::boolalpha >> hasCircleCollider;

    //get rid of comma after boolean
    sceneFile >> text;

    return hasCircleCollider;
}

std::string SceneLoader::readTag(std::ifstream &sceneFile){
    std::string text;

    sceneFile >> text;
    return removeQuotesAndColon(text);
}

void SceneLoader::parseObject(std::ifstream &sceneFile, ECSManager &ecsManager, Entity entities[]){
    
    std::string text;

    //get open brace {
    while(text != "{"){
        sceneFile >> text;
    }
    assert(text == "{");

    // while there is text in the file and text isn't ending an object with a brace
    // >> delineates by whitespace
    while(sceneFile >> text && text.find("}") == -1) {
        //std::cout << text << " " << /*text.length() <<*/ std::endl;

        //parse into game objects and components

        int currentIndex = ecsManager.getLivingEntityCount() - 1;
        Entity currentEntity = entities[currentIndex];
        
        //get key by removing quotation marks and colon
        std::string key = removeQuotesAndColon(text);

        if(key == "transform"){
            TransformComponent t = readTransform(sceneFile);
            ecsManager.addComponent<TransformComponent>(currentEntity, t);
        }
        else if(key == "rigidbody"){
            PhysicsComponent rb = readRigidbody(sceneFile);
            ecsManager.addComponent<PhysicsComponent>(currentEntity, rb);
        }
        else if(key == "render"){
            RenderComponent r = readRender(sceneFile);
            ecsManager.addComponent<RenderComponent>(currentEntity, r);
        }
        else if(key == "boxCollider"){
            bool hasBoxCollider = readBoxCollider(sceneFile);
            if(hasBoxCollider){
                //get transform associated with entity to use for Collider instantiation
                TransformComponent t = ecsManager.getComponent<TransformComponent>(currentEntity);
                BoxCollider *bc = new BoxCollider(t);
                ecsManager.addComponent<Collider *>(currentEntity, bc);
            }
        }
        else if(key == "circleCollider"){
            bool hasCircleCollider = readCircleCollider(sceneFile);
            if(hasCircleCollider){
                //get transform associated with entity to use for Collider instantiation
                TransformComponent t = ecsManager.getComponent<TransformComponent>(currentEntity);
                CircleCollider *cc = new CircleCollider(t);
                ecsManager.addComponent<Collider *>(currentEntity, cc);
            }
        }
        else if(key == "tag"){
            Tag tag;
            tag.tag = readTag(sceneFile);
            ecsManager.addComponent<Tag>(currentEntity, tag);
        }
        //else it's not a component, but a new entity, so create new entity, recurse, and look for components
        else{
            int nextIndex = currentIndex + 1;
            entities[nextIndex] = ecsManager.createEntity();
            parseObject(sceneFile, ecsManager, entities);
        }
    }
}

void SceneLoader::readFile(std::string file, ECSManager &ecsManager, Entity entities[]){
    
    std::string fileDirectory = "scenes/" + file;
    std::ifstream sceneFile(fileDirectory);

    if(!sceneFile){
        //throw error
    }
    else{
        parseObject(sceneFile, ecsManager, entities);
    }

    sceneFile.close();
}

