// Fichero de pruebas para SFML, Irrlicht y C++

#include <iostream>
#include <irrlicht/irrlicht.h>
#include <irrlicht/driverChoice.h>

using namespace std;
using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui; 


enum
{
    // I use this ISceneNode ID to indicate a scene node that is
    // not pickable by getSceneNodeAndCollisionPointFromRay()
    ID_IsNotPickable = 0,

    // I use this flag in ISceneNode IDs to indicate that the
    // scene node can be picked by ray selection.
    IDFlag_IsPickable = 1 << 0,

    // I use this flag in ISceneNode IDs to indicate that the
    // scene node can be highlighted.  In this example, the
    // homonids can be highlighted, but the level mesh can't.
    IDFlag_IsHighlightable = 1 << 1
};

int main(){

    // Al tener el include driverChoice.h podemos llamar a la funcion
    // driverChoiceConsole() para que nos haga la eleccion de drivers 
    E_DRIVER_TYPE driverType=driverChoiceConsole();
    if (driverType==EDT_COUNT)
        return 1;

    // Creamos el objeto principal para usar el motor
    IrrlichtDevice *device =
        createDevice(driverType, dimension2d<u32>(640, 480), 16, false);

    // Si no podemos crearlo con el driver seleccionado devolvemos 1
    if (device == 0)
        return 1;

    // Cambiamos la ruta en la que nos coge los archivos
    device->getFileSystem()->changeWorkingDirectoryTo("../ejemplo7");

    // Cargamos el driver y la escena
    IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();

    // Cargamos el zip con todo el mapeado
    device->getFileSystem()->addFileArchive("../ejemplo7/resources/map-20kdm2.pk3");

    // Obtenemos el mapa
    IAnimatedMesh* q3levelmesh = smgr->getMesh("20kdm2.bsp");
    IMeshSceneNode* q3node = 0;

    // La malla de Quake es seleccionable pero no se resalta
    if (q3levelmesh)
        q3node = smgr->addOctreeSceneNode(q3levelmesh->getMesh(0), 0, IDFlag_IsPickable);
    
    // Creamos un selector de triangulos
    scene::ITriangleSelector* selector = 0;

    // Al pasar por encima de cualquier elemento del mapa
    // se nos resaltara un triangulo    
    if (q3node)
    {
        q3node->setPosition(vector3df(-1350,-130,-1400));

        selector = smgr->createOctreeTriangleSelector(
                q3node->getMesh(), q3node, 128);
        q3node->setTriangleSelector(selector);
        // We're not done with this selector yet, so don't drop it.
    }

    // Set a jump speed of 3 units per second, which gives a fairly realistic jump
    // when used with the gravity of (0, -10, 0) in the collision response animator.
    ICameraSceneNode* camera =
        smgr->addCameraSceneNodeFPS(0, 100.0f, .3f, ID_IsNotPickable, 0, 0, true, 3.f);
    camera->setPosition(vector3df(50,50,-60));
    camera->setTarget(vector3df(-70,30,-60));

    // Anyadimos las colisiones con gravedad (0, -10, 0)
    if (selector)
    {
        ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
            selector, // Selector de triángulos que especifica todas las colisiones posibles del mapa
            camera, // El objeto (nodo de la escena) es que afectado por la colision
            vector3df(30,50,30), // Especifica el tamanyo del objeto
            vector3df(0,-10,0), // Direccion y velocidad de la gravedad, poner a (0,0,0) para desactivarla
            vector3df(0,30,0)); // Traslacion del objeto para dar perspectiva de humano (por eso lo trasladamos 30 posiciones en el eje Y)
        selector->drop(); // As soon as we're done with the selector, drop it.
        camera->addAnimator(anim);
        anim->drop();  // And likewise, drop the animator when we're done referring to it.
    }

    // Now I create three animated characters which we can pick, a dynamic light for
    // lighting them, and a billboard for drawing where we found an intersection.

    // First, let's get rid of the mouse cursor.  We'll use a billboard to show
    // what we're looking at.
    device->getCursorControl()->setVisible(false);

    // Add the billboard.
    // Creamos el señalador con textura en sustitucion al del raton
    IBillboardSceneNode * bill = smgr->addBillboardSceneNode();
    bill->setMaterialType(EMT_TRANSPARENT_ADD_COLOR );
    bill->setMaterialTexture(0, driver->getTexture("../ejemplo7/resources/particle.bmp"));
    bill->setMaterialFlag(EMF_LIGHTING, false);
    bill->setMaterialFlag(EMF_ZBUFFER, false);
    bill->setSize(dimension2d<f32>(20.0f, 20.0f));
    bill->setID(ID_IsNotPickable); // This ensures that we don't accidentally ray-pick it

    IAnimatedMeshSceneNode* node = 0;

    SMaterial material;

    // Add an MD2 node, which uses vertex-based animation.
    node = smgr->addAnimatedMeshSceneNode(smgr->getMesh("../ejemplo7/resources/faerie.md2"),
                        0, IDFlag_IsPickable | IDFlag_IsHighlightable);
    node->setPosition(vector3df(-90,-15,-140)); // Put its feet on the floor.
    node->setScale(vector3df(1.6f)); // Make it appear realistically scaled
    node->setMD2Animation(EMAT_POINT);
    node->setAnimationSpeed(20.f);
    material.setTexture(0, driver->getTexture("../ejemplo7/resources/faerie2.bmp"));
    material.Lighting = true;
    material.NormalizeNormals = true;
    node->getMaterial(0) = material;

    // Now create a triangle selector for it.  The selector will know that it
    // is associated with an animated node, and will update itself as necessary.
    selector = smgr->createTriangleSelector(node);
    node->setTriangleSelector(selector);
    selector->drop(); // We're done with this selector, so drop it now.

    
    // And this B3D file uses skinned skeletal animation.
    node = smgr->addAnimatedMeshSceneNode(smgr->getMesh("../ejemplo7/resources/ninja.b3d"),
                        0, IDFlag_IsPickable | IDFlag_IsHighlightable);
    node->setScale(vector3df(10));
    node->setPosition(vector3df(-75,-66,-80));
    node->setRotation(vector3df(0,90,0));
    node->setAnimationSpeed(8.f);
    node->getMaterial(0).NormalizeNormals = true;
    node->getMaterial(0).Lighting = true;
    // Just do the same as we did above.
    selector = smgr->createTriangleSelector(node);
    node->setTriangleSelector(selector);
    selector->drop();


    // This X files uses skeletal animation, but without skinning.
    node = smgr->addAnimatedMeshSceneNode(smgr->getMesh("../ejemplo7/resources/dwarf.x"),
                        0, IDFlag_IsPickable | IDFlag_IsHighlightable);
    node->setPosition(vector3df(-70,-66,-30)); // Put its feet on the floor.
    node->setRotation(vector3df(0,-90,0)); // And turn it towards the camera.
    node->setAnimationSpeed(20.f);
    node->getMaterial(0).Lighting = true;
    selector = smgr->createTriangleSelector(node);
    node->setTriangleSelector(selector);
    selector->drop();


    // And this mdl file uses skinned skeletal animation.
    node = smgr->addAnimatedMeshSceneNode(smgr->getMesh("../ejemplo7/resources/yodan.mdl"),
                        0, IDFlag_IsPickable | IDFlag_IsHighlightable);
    node->setPosition(vector3df(-90,-25,20));
    node->setScale(vector3df(0.8f));
    node->getMaterial(0).Lighting = true;
    node->setAnimationSpeed(20.f);

    // Just do the same as we did above.
    selector = smgr->createTriangleSelector(node);
    node->setTriangleSelector(selector);
    selector->drop();

    material.setTexture(0, 0);
    material.Lighting = false;

    
    // Add a light, so that the unselected nodes aren't completely dark.
    ILightSceneNode * light = smgr->addLightSceneNode(0, vector3df(-60,100,400),
        SColorf(1.0f,1.0f,1.0f,1.0f), 600.0f);
    light->setID(ID_IsNotPickable); // Make it an invalid target for selection.

    // Remember which scene node is highlighted
    ISceneNode* highlightedSceneNode = 0;
    ISceneCollisionManager* collMan = smgr->getSceneCollisionManager();
    int lastFPS = -1;

    // draw the selection triangle only as wireframe
    material.Wireframe=true;


    while(device->run())
    if (device->isWindowActive())
    {
        driver->beginScene(true, true, 0);
        smgr->drawAll();

        // Unlight any currently highlighted scene node
        if (highlightedSceneNode)
        {
            highlightedSceneNode->setMaterialFlag(EMF_LIGHTING, true);
            highlightedSceneNode = 0;
        }

        // All intersections in this example are done with a ray cast out from the camera to
        // a distance of 1000.  You can easily modify this to check (e.g.) a bullet
        // trajectory or a sword's position, or create a ray from a mouse click position using
        // ISceneCollisionManager::getRayFromScreenCoordinates()
        line3d<f32> ray;
        ray.start = camera->getPosition();
        ray.end = ray.start + (camera->getTarget() - ray.start).normalize() * 1000.0f;

        // Tracks the current intersection point with the level or a mesh
        vector3df intersection;
        // Used to show with triangle has been hit
        triangle3df hitTriangle;

        // This call is all you need to perform ray/triangle collision on every scene node
        // that has a triangle selector, including the Quake level mesh.  It finds the nearest
        // collision point/triangle, and returns the scene node containing that point.
        // Irrlicht provides other types of selection, including ray/triangle selector,
        // ray/box and ellipse/triangle selector, plus associated helpers.
        // See the methods of ISceneCollisionManager
        ISceneNode * selectedSceneNode =
            collMan->getSceneNodeAndCollisionPointFromRay(
                    ray,
                    intersection, // This will be the position of the collision
                    hitTriangle, // This will be the triangle hit in the collision
                    IDFlag_IsPickable, // This ensures that only nodes that we have
                            // set up to be pickable are considered
                    0); // Check the entire scene (this is actually the implicit default)


        // If the ray hit anything, move the billboard to the collision position
        // and draw the triangle that was hit.
        if(selectedSceneNode)
        {
            bill->setPosition(intersection);

            // We need to reset the transform before doing our own rendering.
            driver->setTransform(ETS_WORLD, core::matrix4());
            driver->setMaterial(material);
            driver->draw3DTriangle(hitTriangle, SColor(0,255,0,0));

            // We can check the flags for the scene node that was hit to see if it should be
            // highlighted. The animated nodes can be highlighted, but not the Quake level mesh
            if((selectedSceneNode->getID() & IDFlag_IsHighlightable) == IDFlag_IsHighlightable)
            {
                highlightedSceneNode = selectedSceneNode;

                // Highlighting in this case means turning lighting OFF for this node,
                // which means that it will be drawn with full brightness.
                highlightedSceneNode->setMaterialFlag(EMF_LIGHTING, false);
            }
        }

        // We're all done drawing, so end the scene.
        driver->endScene();

        int fps = driver->getFPS();

        if (lastFPS != fps)
        {
            core::stringw str = L"Collision detection example - Irrlicht Engine [";
            str += driver->getName();
            str += "] FPS:";
            str += fps;

            device->setWindowCaption(str.c_str());
            lastFPS = fps;
        }
    }

    device->drop();

    return 0;

}