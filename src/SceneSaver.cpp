#include "SceneSaver.h"

void writeKey(std::ofstream &sceneFile, std::string key){
    sceneFile << "\"" << key << "\": "; 
}

//JSON convention uses 4 spaces instead of tabs
void writeNumTabs(std::ofstream &sceneFile, int numTabs){
    std::string tabs = "";
    for(int i = 0; i < numTabs; i++){
        tabs += "    ";
    }
    sceneFile << tabs;
}

void SceneSaver::addQuotesAndColon(std::string text){

}
void SceneSaver::addEndLineComma(std::ofstream &sceneFile){
    sceneFile << ",\n";
}

void SceneSaver::writeTransform(std::ofstream &sceneFile, TransformComponent transform){
    sceneFile << "{\n";
    
    writeNumTabs(sceneFile, 3);
    writeKey(sceneFile, "width");
    sceneFile << transform.width << ",\n";

    writeNumTabs(sceneFile, 3);
    writeKey(sceneFile, "height");
    sceneFile << transform.height << ",\n";

    writeNumTabs(sceneFile, 3);
    writeKey(sceneFile, "x");
    sceneFile << transform.x << ",\n";

    writeNumTabs(sceneFile, 3);
    writeKey(sceneFile, "y");
    sceneFile << transform.y << "\n";

    writeNumTabs(sceneFile, 3);
    sceneFile << "}";
}
void SceneSaver::writeRigidbody(std::ofstream &sceneFile, PhysicsComponent rb){

    sceneFile << "{\n";
    
    writeNumTabs(sceneFile, 3);
    writeKey(sceneFile, "velocityX");
    sceneFile << rb.velocity.x << ",\n";

    writeNumTabs(sceneFile, 3);
    writeKey(sceneFile, "velocityY");
    sceneFile << rb.velocity.y << ",\n";

    writeNumTabs(sceneFile, 3);
    writeKey(sceneFile, "isKinematic");
    //output bool as string, otherwise outputs 1 or 0
    if(rb.isKinematic)
    {
        sceneFile << "true";
    }
    else{
        sceneFile << "false";
    }
    sceneFile << ",\n";

    writeNumTabs(sceneFile, 3);
    writeKey(sceneFile, "elasticity");
    sceneFile << rb.elasticity << ",\n";

    writeNumTabs(sceneFile, 3);
    writeKey(sceneFile, "mass");
    if (rb.mass != INFINITY)
    {
        sceneFile << rb.mass << "\n";
    }
    else{
        sceneFile << "\"INFINITY\"\n";
    }

    writeNumTabs(sceneFile, 3);
    sceneFile << "}";

}
void SceneSaver::writeRender(std::ofstream &sceneFile, RenderComponent r){
    sceneFile << "{\n";

    writeNumTabs(sceneFile, 3);
    writeKey(sceneFile, "shape");

    if(r.mShape == IMAGE){
        sceneFile << "\"IMAGE\"";
        sceneFile << ",\n";

        writeNumTabs(sceneFile, 3);
        writeKey(sceneFile, "fileName");
        sceneFile << "\"" << r.mImage.mFileName << "\"\n";
    }
    else{
        if(r.mShape == RECT){
            sceneFile << "\"RECT\"";
        }
        else if(r.mShape == CIRCLE){
            sceneFile << "\"CIRCLE\"";
        }

        sceneFile << ",\n";

        writeNumTabs(sceneFile, 3);
        writeKey(sceneFile, "red");
        sceneFile << r.mColor.red << ",\n";

        writeNumTabs(sceneFile, 3);
        writeKey(sceneFile, "green");
        sceneFile << r.mColor.green << ",\n";

        writeNumTabs(sceneFile, 3);
        writeKey(sceneFile, "blue");
        sceneFile << r.mColor.blue << ",\n";

        writeNumTabs(sceneFile, 3);
        writeKey(sceneFile, "alpha");
        sceneFile << r.mColor.alpha << "\n";
    }
    
    writeNumTabs(sceneFile, 3);
    sceneFile << "}";
}
void SceneSaver::writeBoxCollider(std::ofstream &sceneFile){

}
void SceneSaver::writeCircleCollider(std::ofstream &sceneFile){

}
void SceneSaver::writeTag(std::ofstream &sceneFile){

}

void SceneSaver::writeObject(std::ofstream &sceneFile, ECSManager &ecsManager, Entity entities[], uint8_t numEntities){
    
    std::string text;

    //write open brace {
    sceneFile << "{\n";

    //for each entity, 
    //  1. go through each component type
    //  2. see if the entity has that component
    //  3. if so, write out component data
    //don't know of a better way than brute force since
    //entities don't have references to their components
    //shouldn't be an issue with a small amount of entities
    //--- TODO - maybe consider a "serialization" component
    //to just save certain entities
    for(int i = 0; i < numEntities; i++){
        Entity entity = entities[i];
        //write out entity ID
        writeNumTabs(sceneFile, 1);
        //have to cast uint8_t to unsigned int, otherwise << simply outputs ascii value, which isn't what we want
        sceneFile << "\"" << unsigned(entity) << "\": {\n";

        //keep track of if a comma is needed in between components
        bool needComma = false;

        //if entity has a transform
        if(ecsManager.doesEntityHaveComponent<TransformComponent>(entity)){
            TransformComponent t = ecsManager.getComponent<TransformComponent>(entity);
            writeNumTabs(sceneFile, 2);
            writeKey(sceneFile, "transform");
            writeTransform(sceneFile, t);
            
            //tell next component (if one exists) that comma is needed first
            needComma = true;
        }

        //if entity has a rigidbody
        if(ecsManager.doesEntityHaveComponent<PhysicsComponent>(entity)){
            
            if(needComma){
                addEndLineComma(sceneFile);
            }
            
            PhysicsComponent rb = ecsManager.getComponent<PhysicsComponent>(entity);
            writeNumTabs(sceneFile, 2);
            writeKey(sceneFile, "rigidbody");
            writeRigidbody(sceneFile, rb);

            needComma = true;
        }

        //if entity has a collider
        if(ecsManager.doesEntityHaveComponent<Collider *>(entity)){
            
            if(needComma){
                addEndLineComma(sceneFile);
            }
            
            Collider *c = ecsManager.getComponent<Collider *>(entity);
            writeNumTabs(sceneFile, 2);
            if(typeid(*c) == typeid(BoxCollider)){
                writeKey(sceneFile, "boxCollider");
            }
            else if(typeid(*c) == typeid(CircleCollider)){
                writeKey(sceneFile, "circleCollider");
            }

            sceneFile << "true"; //---TODO- this is causing commas to be on the next line and messing up the loader

            needComma = true;
        }

        //if entity has a renderer
        if(ecsManager.doesEntityHaveComponent<RenderComponent>(entity)){
            
            if(needComma){
                addEndLineComma(sceneFile);
            }
            
            RenderComponent r = ecsManager.getComponent<RenderComponent>(entity);
            writeNumTabs(sceneFile, 2);
            writeKey(sceneFile, "render");
            writeRender(sceneFile, r);

            needComma = true;
        }
        //if entity has a tag
        if(ecsManager.doesEntityHaveComponent<Tag>(entity)){
            
            if(needComma){
                addEndLineComma(sceneFile);
            }
            
            Tag t = ecsManager.getComponent<Tag>(entity);
            writeNumTabs(sceneFile, 2);
            writeKey(sceneFile, "tag");

            sceneFile << "\"" << t.tag << "\"";

            needComma = true;
        }
        //if entity has a script
        if(ecsManager.doesEntityHaveComponent<Script>(entity)){
            if(needComma){
                addEndLineComma(sceneFile);
            }

            Script s = ecsManager.getComponent<Script>(entity);
            writeNumTabs(sceneFile, 2);
            writeKey(sceneFile, "script");

            sceneFile << "\"" << s.name << "\"";

            needComma = true;
        }

        sceneFile << "\n";
        writeNumTabs(sceneFile, 2);
        sceneFile << "}";

        if(i < numEntities - 1){
            sceneFile << ",";
        }

        sceneFile << "\n";
    }
    
    //write close brace }
    sceneFile << "}\n";

}

void SceneSaver::writeFile(std::string file, ECSManager &ecsManager, Entity entities[], uint8_t numEntities){
    
    std::string fileDirectory = "scenes/" + file;
    std::ofstream sceneFile(fileDirectory);

    if(!sceneFile){
        //throw error
    }
    else{
        writeObject(sceneFile, ecsManager, entities, numEntities);
    }

    sceneFile.close();
}