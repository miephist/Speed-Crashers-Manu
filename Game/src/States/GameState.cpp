#include "GameState.h"
#include "../Game/Game.h"

GameState::GameState(){

    Init();

}

GameState::~GameState(){


    // Destruimos la IA
    for(unsigned int i = 0; i < ia.size(); i++){
        delete ia.at(i);
    } 
    // Destruimos Jugadores
    for(unsigned int i = 0; i < coop.size(); i++){
        delete coop.at(i);
    }

    ia.clear();

    movements.clear();

    // Destruimos los equipos
    delete red;
    delete blue;

    // Destruimos la pelota
    delete Pelota::getInstancia();

    // Destruimos el audio
    delete CAudioEngine::getInstancia();

    // Destruimos la camara
     
    /*for(unsigned int i = 0;i < cameras.size(); i++){
        delete cameras.at(i);
    }*/

    // Destruimos las fisicas (se incluyen los nitros aqui)
    delete PhysicsEngine::getInstancia();

     
    // Destruimos la escena actual
    ITEngine::getInstancia()->resetScene();

    //destruir shaders 
    delete shader;
    delete shaderHud;
    delete shaderSkybox;
    delete shaderDebug;
}

void GameState::Init(){

    srand(time(NULL));
    voz = 30+rand()%10;

    // Ocultamos el cursor
    glfwSetCursor(ITEngine::getInstancia()->getWindow(), NULL);

    // SKYBOX
    shaderSkybox = ITEngine::getInstancia()->createShader("media/shaders/Skybox/vertexShader.glsl", "media/shaders/Skybox/fragmentShader.glsl");
    ITEngine::getInstancia()->createSkybox();

    // TEXTO
    shaderText = ITEngine::getInstancia()->createShader("media/shaders/Text/vertexShader.glsl", "media/shaders/Text/fragmentShader.glsl");

    // DEBUG
    shaderDebug = ITEngine::getInstancia()->createShader("media/shaders/Debug/vertexShader.glsl", "media/shaders/Debug/fragmentShader.glsl");

    // SHADER LUCES
    shader = ITEngine::getInstancia()->createShader("media/shaders/Lights/vertexShader.glsl", "media/shaders/Lights/fragmentShader.glsl");

    // ---- CREACION DE LUCES ----

    glm::vec4 direc =glm::vec4(-2.f, -1.0f, -2.f, 0);
    glm::vec3 amb =glm::vec3(0.22f, 0.22f, 0.22f);
    glm::vec3 dif =glm::vec3(0.26f, 0.26f, 0.26f);
    glm::vec3 spec= glm::vec3(0.26f, 0.26f, 0.26f);

    ITEngine::getInstancia()->createLight(direc ,amb ,dif ,spec);

    direc =glm::vec4(50.f, 80.0f, 90.f, 1);
    amb =glm::vec3(0.2f, 0.2f, 0.2f);
    dif =glm::vec3(3.f, 3.f, 3.f);
    spec = glm::vec3(3.f, 3.f, 3.f);

    ITEngine::getInstancia()->createLight(direc ,amb ,dif ,spec); 

    amb =glm::vec3(0.3f, 0.3f, 0.3f);
    dif =glm::vec3(0.5f, 0.5f, 0.5f);
    spec = glm::vec3(0.5f, 0.5f, 0.5f);
    
    float cut=35;//15
    float out=47.5;//17.5

    glm::vec3 targ;
    glm::vec3 Pos;
    Pos.y=42;
    targ.y=-25;

   
    int lado,lado2;
//porteria
    for(int z=0;z<4;z++){
        int x=std::remainder(z,2);
        int c;
        //es par
        if(x==0){
            lado=1;
            c=z/2;
            if(c==0){
                lado2=1;
            }
            else{
                lado2=-1;
            }
        }
        else{
            lado=-1;
            c=z/2;
            if(c==0){
                lado2=1;
            }
            else{
                lado2=-1;
            }
        }
        Pos.x=lado*29; 
        Pos.z=lado2*122;
        targ=glm::vec3(0,-1,0);
    
        ITEngine::getInstancia()->createLight(amb, dif ,spec,targ, Pos, cut, out);
    }

    // ---- FIN CREACION DE LUCES ----

    // Creacion Shader del hud
    shaderHud = ITEngine::getInstancia()->createShader("media/shaders/HUD/vertexShader.glsl", "media/shaders/HUD/fragmentShader.glsl");

    // Seteamos las propiedas de OpenGL para el juego
    ITEngine::getInstancia()->setProperties();

    // Pantalla de Carga
    ITEngine::getInstancia()->newHud("ScoreLoading");
    ITEngine::getInstancia()->getActiveHud()->addElement("fondo", "media/GUI/Loading Controls.png");
    
    carga = 0;

    // Debug HUD
    ITEngine::getInstancia()->newHud("DebugHud");
    ITEngine::getInstancia()->getActiveHud()->addElement("Leyenda", "media/Hud/Debug/Leyenda.png");
    ITEngine::getInstancia()->getActiveHud()->scaleElement("Leyenda",0.5,0.5);
    ITEngine::getInstancia()->getActiveHud()->traslateElement("Leyenda", -1.55, 0.6);

    ITEngine::getInstancia()->getActiveHud()->addElement("Interfaz", "media/Hud/Debug/Interfaz.png");
    ITEngine::getInstancia()->getActiveHud()->scaleElement("Interfaz",0.45,0.45);
    ITEngine::getInstancia()->getActiveHud()->traslateElement("Interfaz", 1.675, 1.3);

    ITEngine::getInstancia()->getActiveHud()->addElement("NitroIA", "media/Hud/Debug/Nitro/Turbo0.png");
    ITEngine::getInstancia()->getActiveHud()->scaleElement("NitroIA",0.5,0.5);
    ITEngine::getInstancia()->getActiveHud()->traslateElement("NitroIA", 1.5, 1.55);

    ITEngine::getInstancia()->getActiveHud()->addElement("ZonaIA", "media/Hud/Debug/Zonas/Semaforo Verde.png");
    ITEngine::getInstancia()->getActiveHud()->scaleElement("ZonaIA",0.5,0.5);
    ITEngine::getInstancia()->getActiveHud()->traslateElement("ZonaIA", 1.5, 1.25);

    ITEngine::getInstancia()->getActiveHud()->addElement("PoderIA", "media/Hud/Debug/Poderes/Cooldown.png");
    ITEngine::getInstancia()->getActiveHud()->scaleElement("PoderIA",0.5,0.5);
    ITEngine::getInstancia()->getActiveHud()->traslateElement("PoderIA", 1.5, 0.92);

    ITEngine::getInstancia()->getActiveHud()->addElement("EstadoIA", "media/Hud/Debug/Estados/Ataque.png");
    ITEngine::getInstancia()->getActiveHud()->scaleElement("EstadoIA",0.5,0.5);
    ITEngine::getInstancia()->getActiveHud()->traslateElement("EstadoIA", 1.5, 0.62);

    //Hud - Modo individual y Jugador con teclado en multijugador
    ITEngine::getInstancia()->newHud("GameHud");

    // Marcador
    ITEngine::getInstancia()->getActiveHud()->addElement("Marcador","media/Hud/Marcador.png");
    ITEngine::getInstancia()->getActiveHud()->scaleElement("Marcador",1.1,1.1);
    ITEngine::getInstancia()->getActiveHud()->traslateElement("Marcador", 0, 0.84);

    //Goles Azul
    ITEngine::getInstancia()->getActiveHud()->addElement("Marcador Azul","media/Hud/Contador/0.png");
    ITEngine::getInstancia()->getActiveHud()->scaleElement("Marcador Azul",0.9,0.9);
    ITEngine::getInstancia()->getActiveHud()->traslateElement("Marcador Azul", -0.245, 1.03); 
    

    //Goles Rojo
    ITEngine::getInstancia()->getActiveHud()->addElement("Marcador Rojo","media/Hud/Contador/0.png");
    ITEngine::getInstancia()->getActiveHud()->scaleElement("Marcador Rojo",0.9,0.9);
    ITEngine::getInstancia()->getActiveHud()->traslateElement("Marcador Rojo", 0.245, 1.03);

    // Poder Inicial
    ITEngine::getInstancia()->getActiveHud()->addElement("Power","media/Hud/Poderes/Cooldown.png");
    ITEngine::getInstancia()->getActiveHud()->scaleElement("Power",1,1);
    ITEngine::getInstancia()->getActiveHud()->traslateElement("Power", -0.88, -0.84);

    // Nitros
    ITEngine::getInstancia()->getActiveHud()->addElement("Nitro","media/Hud/Nitro/Turbo0.png");
    ITEngine::getInstancia()->getActiveHud()->traslateElement("Nitro", 0.767, -0.785);

    // Temporizador

    // Minutos
    ITEngine::getInstancia()->getActiveHud()->addElement("TimerMinutos","media/Hud/Contador/0.png");
    ITEngine::getInstancia()->getActiveHud()->scaleElement("TimerMinutos",0.9,0.9);
    ITEngine::getInstancia()->getActiveHud()->traslateElement("TimerMinutos", -0.1, 1.03);

    // Decenas
    ITEngine::getInstancia()->getActiveHud()->addElement("TimerDecenas","media/Hud/Contador/0.png");
    ITEngine::getInstancia()->getActiveHud()->scaleElement("TimerDecenas",0.9,0.9);
    ITEngine::getInstancia()->getActiveHud()->traslateElement("TimerDecenas", 0.06, 1.03);

    // Segundos
    ITEngine::getInstancia()->getActiveHud()->addElement("TimerSegundos","media/Hud/Contador/0.png");
    ITEngine::getInstancia()->getActiveHud()->scaleElement("TimerSegundos",0.9,0.9);
    ITEngine::getInstancia()->getActiveHud()->traslateElement("TimerSegundos", 0.13, 1.03);

    //Hud Jugador con Mando en multijugador
    if(Options::getInstancia()->getCoop()){

        ITEngine::getInstancia()->newHud("GameHudCoop");

        // Marcador
        ITEngine::getInstancia()->getActiveHud()->addElement("Marcador","media/Hud/Marcador.png");
        ITEngine::getInstancia()->getActiveHud()->scaleElement("Marcador",1.1,1.1);
        ITEngine::getInstancia()->getActiveHud()->traslateElement("Marcador", 0, 0.84);

        //Goles Azul
        ITEngine::getInstancia()->getActiveHud()->addElement("Marcador Azul","media/Hud/Contador/0.png");
        ITEngine::getInstancia()->getActiveHud()->scaleElement("Marcador Azul",0.9,0.9);
        ITEngine::getInstancia()->getActiveHud()->traslateElement("Marcador Azul", -0.245, 1.03); 
    

        //Goles Rojo
        ITEngine::getInstancia()->getActiveHud()->addElement("Marcador Rojo","media/Hud/Contador/0.png");
        ITEngine::getInstancia()->getActiveHud()->scaleElement("Marcador Rojo",0.9,0.9);
        ITEngine::getInstancia()->getActiveHud()->traslateElement("Marcador Rojo", 0.245, 1.03);

        // Poder Inicial
        ITEngine::getInstancia()->getActiveHud()->addElement("PowerCoop","media/Hud/Poderes/Cooldown.png");
        ITEngine::getInstancia()->getActiveHud()->scaleElement("PowerCoop",1,1);
        ITEngine::getInstancia()->getActiveHud()->traslateElement("PowerCoop", -0.88, -0.84);

        // Nitros
        ITEngine::getInstancia()->getActiveHud()->addElement("NitroCoop","media/Hud/Nitro/Turbo0.png");
        ITEngine::getInstancia()->getActiveHud()->scaleElement("NitroCoop", 1, 1);
        ITEngine::getInstancia()->getActiveHud()->traslateElement("NitroCoop", 0.767, -0.785);

        // Temporizador
        // Minutos
        ITEngine::getInstancia()->getActiveHud()->addElement("TimerMinutos","media/Hud/Contador/0.png");
        ITEngine::getInstancia()->getActiveHud()->scaleElement("TimerMinutos",0.9,0.9);
        ITEngine::getInstancia()->getActiveHud()->traslateElement("TimerMinutos", -0.1, 1.03);

        // Decenas
        ITEngine::getInstancia()->getActiveHud()->addElement("TimerDecenas","media/Hud/Contador/0.png");
        ITEngine::getInstancia()->getActiveHud()->scaleElement("TimerDecenas",0.9,0.9);
        ITEngine::getInstancia()->getActiveHud()->traslateElement("TimerDecenas", 0.06, 1.03);

        // Segundos
        ITEngine::getInstancia()->getActiveHud()->addElement("TimerSegundos","media/Hud/Contador/0.png");
        ITEngine::getInstancia()->getActiveHud()->scaleElement("TimerSegundos",0.9,0.9);
        ITEngine::getInstancia()->getActiveHud()->traslateElement("TimerSegundos", 0.13, 1.03);
    }

    // Cargamos el nodo del campo
    ITResourceMesh* campo = ITEngine::getInstancia()->createMesh("media/Escenarios/Campo/escenario.obj", "media/Escenarios/Campo/escenario_diffuse.png");
    // Creamos el sistema colisiones
    collide = new TriggerSystem();

    // Cargamos el mundo y le damos una gravedad
    PhysicsEngine::getInstancia()->setWorld("media/Escenarios/Campo/escenario.bullet");

    //Iniciliazacion variables IA
    int idIA = 11;
    position = 0;
    atack = 0;
    vec2f posIA(0, 50);
    ran = 0;
    mitad = Options::getInstancia()->getForwardScenario()/2;
    mitadSup = mitad + (mitad/2);
    mitadInf = mitad/2;
    z = 0;

     // Creacion de los equipos
    std::vector<Baseplayer*> blueTeam;
    std::vector<Baseplayer*> redTeam;

    //**********************************************Zona Coop***********************************************************//
    // Creamos el coche
    
    if(Options::getInstancia()->getCoop()){
        idIA = 12;
        for(int i = 0; i < 2; i++){
            if(i==0){
                 coop.push_back(new Jugador(0,-100,10,"Jugador",'t'));
                 coop.at(i)->InitCollide(PhysicsEngine::getInstancia()->getWorld());
            }
            else{
                coop.push_back(new Jugador(0,100,11,"Jugador",'m'));
                coop.at(i)->getCoche()->setRotation(glm::vec3(0,180,0), 0);
                coop.at(i)->InitCollide(PhysicsEngine::getInstancia()->getWorld());
            }
        }

        // Creamos la IA 
        /**
        * TIPOS DE IA:
        * - 2 vs 2: D , Nuestra D.
        * - 3 vs 3: D,A, Nuestra D y A.
        */

        for(unsigned int i = 0; i < Options::getInstancia()->getNumIAs()-1; i ++){
        
            // 2 VS 2
             if(Options::getInstancia()->getNumIAs() == 3){
                if(i == 0){
                    posIA.x += 50;
                    ia.push_back(new IA(posIA.x,posIA.y,idIA,"JugadorIA",'D'));
                    ia.at(i)->getCoche()->setRotation(glm::vec3(0,180,0), 0);
                    posIA.x = 50;
                    posIA.y = -100;
                }else if(i == 1){
                    ia.push_back(new IA(posIA.x,posIA.y,idIA,"JugadorIA",'D'));
                    ia.at(i)->setEnemy(false);
                    
                }
            
            // 3 VS 3
            }else if(Options::getInstancia()->getNumIAs() == 5){
                if(i <= 1){
                    if(i == 0){
                         posIA.x += 50;
                        ia.push_back(new IA(posIA.x,posIA.y,idIA,"JugadorIA",'D'));
                        ia.at(i)->getCoche()->setRotation(glm::vec3(0,180,0), 0);
                        posIA.x = 50; 
                    }else if(i == 1){
                        ia.push_back(new IA(posIA.x,posIA.y,idIA,"JugadorIA",'A'));
                        ia.at(i)->getCoche()->setRotation(glm::vec3(0,180,0), 0);
                        posIA.x = -50;
                        posIA.y += -200;
                    }              
            
                }else{
                    if(i == 2){
                        ia.push_back(new IA(posIA.x,posIA.y,idIA,"JugadorIA",'D'));
                        ia.at(i)->setEnemy(false);
                        posIA.x += 100;
                    }else if(i == 3){
                        ia.push_back(new IA(posIA.x,posIA.y,idIA,"JugadorIA",'A'));
                        ia.at(i)->setEnemy(false);
                    }
                }
            }
    
            ia.at(i)->InitCollide(PhysicsEngine::getInstancia()->getWorld());
        
            idIA++;

        }
        // Metemos jugadores en equipos distintos
        blueTeam.push_back(coop.at(0));
        redTeam.push_back(coop.at(1));

    // Equipo teclado
        for(unsigned int i = 0; i < ia.size(); i++){  
            if(ia.at(i)->getIsEnemy() == false)
                blueTeam.push_back(ia.at(i));
        }
    
    // Equipo Mando
        for(unsigned int i = 0; i < ia.size(); i++){  
            if(ia.at(i)->getIsEnemy() == true)
                redTeam.push_back(ia.at(i));
        }


    }

    //**********************************************Zona Vs Ia***********************************************************//

    else{
        //Creacion Jugador
        Coche = new Jugador(0,-100,10,"Jugador",'t');
        coop.push_back(Coche);
        Coche->InitCollide(PhysicsEngine::getInstancia()->getWorld());

        // Creamos la IA 
        /**
        * TIPOS DE IA:
        * - 1 vs 1: C.
        * - 2 vs 2: D y A, Nuestra D.
        * - 3 vs 3: Los tres tipos, Nuestra D y A.
        */


         for(unsigned int i = 0; i < Options::getInstancia()->getNumIAs(); i ++){

            // 1 VS 1
            if(Options::getInstancia()->getNumIAs() == 1){
                ia.push_back(new IA(posIA.x,posIA.y,idIA,"JugadorIA",'C'));

                ia.at(i)->getCoche()->setRotation(glm::vec3(0,180,0), 0);
        
            // 2 VS 2
            }else if(Options::getInstancia()->getNumIAs() == 3){
                if(i == 0){
                    ia.push_back(new IA(posIA.x,posIA.y,idIA,"JugadorIA",'D'));
                    ia.at(i)->getCoche()->setRotation(glm::vec3(0,180,0), 0);
                    posIA.x += 50;
                }else if(i == 1){
                    ia.push_back(new IA(posIA.x,posIA.y,idIA,"JugadorIA",'A'));
                    ia.at(i)->getCoche()->setRotation(glm::vec3(0,180,0), 0);
                    posIA.x = 50;
                    posIA.y = -100;
                }else{
                    posIA.y = -120;
                    posIA.x = 2;
                    ia.push_back(new IA(posIA.x,posIA.y,idIA,"JugadorIA",'D'));
                    // Le indicamos que va en nuestro equipo
                    ia.at(i)->setEnemy(false);
                }
            
            // 3 VS 3
            }else if(Options::getInstancia()->getNumIAs() == 5){
                if(i <= 2){
                    if(i == 0){
                        ia.push_back(new IA(posIA.x,posIA.y,idIA,"JugadorIA",'D'));
                        ia.at(i)->getCoche()->setRotation(glm::vec3(0,180,0), 0);
                        posIA.x = 50; 
                    }else if(i == 1){
                        ia.push_back(new IA(posIA.x,posIA.y,idIA,"JugadorIA",'A'));
                        ia.at(i)->getCoche()->setRotation(glm::vec3(0,180,0), 0);
                        posIA.x = -50;
                    }else{
                        ia.push_back(new IA(posIA.x,posIA.y,idIA,"JugadorIA",'C'));
                        ia.at(i)->getCoche()->setRotation(glm::vec3(0,180,0), 0);
                        posIA.y += -200;
                    }               
            
                }else{
                    if(i == 3){
                        ia.push_back(new IA(posIA.x,posIA.y,idIA,"JugadorIA",'D'));
                        ia.at(i)->setEnemy(false);
                        posIA.x += 100;
                    }else if(i == 4){
                        ia.push_back(new IA(posIA.x,posIA.y,idIA,"JugadorIA",'A'));
                        ia.at(i)->setEnemy(false);
                    }
                }
            }
    
            ia.at(i)->InitCollide(PhysicsEngine::getInstancia()->getWorld());
        
            idIA++;

        }
        
        //Equipo Jugador
        blueTeam.push_back(coop.at(0));
        for(unsigned int i = 0; i < ia.size(); i++){  
            if(ia.at(i)->getIsEnemy() == false)
                blueTeam.push_back(ia.at(i));
        }
    
        // Equipo IA
        for(unsigned int i = 0; i < ia.size(); i++){  
            if(ia.at(i)->getIsEnemy() == true)
                redTeam.push_back(ia.at(i));
        }
        

    }
    //-------LOGICA DIFUSA-----------------------

    if(ia.size() == 1){

        FuzzyModule Atacante;

     FuzzyVariable& Campo = Atacante.CreateFLV("Campo");
        
        FzSet Ataque = Campo.AddLeftSet("Ataque",0,72,144);
        FzSet Centro = Campo.AddTriangleSet("Centro",72,144,216);
        FzSet Defensa = Campo.AddRightSet("Defensa",144,216,288);

        FuzzyVariable& Pos = Atacante.CreateFLV("Pos");

        FzSet Atras = Pos.AddLeftSet("Atras",0,90,100);
        FzSet Lado = Pos.AddTriangleSet("Lado",90,100,110);
        FzSet Delante = Pos.AddRightSet("Delante",100,110,200);


        FuzzyVariable& Deseabilidad = Atacante.CreateFLV("Deseabilidad");

        FzSet Poco = Deseabilidad.AddLeftSet("Poco",0,25,50);
        FzSet Deseable = Deseabilidad.AddTriangleSet("Deseable",25,50,75);
        FzSet Muy = Deseabilidad.AddRightSet("Muy",50,75,100);

        FuzzyVariable& Distancia = Atacante.CreateFLV("Distancia");
        FzSet MuyC = Distancia.AddLeftSet("MuyC",0,42.25,84.5);
        FzSet Cerca = Distancia.AddTriangleSet("Cerca",45.25,84.5,169);
        FzSet Lejos = Distancia.AddTriangleSet("Lejos",84.5,169,253.5);
        FzSet MuyL = Distancia.AddRightSet("MuyL",169,253.5,338);
    
       /* FzAND DD(Defensa,Delante);
        FzAND DA(Defensa,Atras);
        FzAND DL(Defensa,Lado);
        Atacante.AddRule(DD,Muy);
        Atacante.AddRule(DA,Poco);
        Atacante.AddRule(DL,Deseable);

        

       
        FzAND AL(Ataque,Lado);
        FzAND AD(Ataque,Delante);
        Atacante.AddRule(AA,Poco);
        Atacante.AddRule(AL,Deseable);
        Atacante.AddRule(AD,Muy);

        FzAND CA(Centro,Atras);
        FzAND CL(Centro,Lado);
        FzAND CD(Centro,Delante);
        Atacante.AddRule(CA,Poco);
        Atacante.AddRule(CL,Deseable);
        Atacante.AddRule(CD,Muy);*/

        
            Atacante.Fuzzify("Distancia",(double)169);
            Atacante.Fuzzify("Pos",(double)110);

            FzAND DMC(Delante,MuyC);
            FzAND DC(Delante,Cerca);
            FzAND DL(Delante,Lejos);
            FzAND DML(Delante,MuyL);

            Atacante.AddRule(DMC,Muy);
            Atacante.AddRule(DC,Muy);
            Atacante.AddRule(DL,Poco);
            Atacante.AddRule(DML,Poco);

            FzAND AMC(Atras,MuyC);
            FzAND AC(Atras,Cerca);
            FzAND AL(Atras,Lejos);
            FzAND AML(Atras,MuyL);

            Atacante.AddRule(AMC,Poco);
            Atacante.AddRule(AC,Poco);
            Atacante.AddRule(AL,Poco);
            Atacante.AddRule(AML,Poco);

            FzAND LMC(Lado,MuyC);
            FzAND LC(Lado,Cerca);
            FzAND LL(Lado,Lejos);
            FzAND LML(Lado,MuyL);

            Atacante.AddRule(LMC,Muy);
            Atacante.AddRule(LC,Deseable);
            Atacante.AddRule(LL,Poco);
            Atacante.AddRule(LML,Poco);

            
            std::cout<<"Primera: "<<Atacante.DeFuzzify("Deseabilidad")<<std::endl;


            Atacante.AddRule(MuyC,Muy);
            Atacante.AddRule(Cerca,Deseable);
            Atacante.AddRule(Lejos,Poco);
            Atacante.AddRule(MuyL,Poco);

            Atacante.Fuzzify("Distancia",42);
            std::cout<<"Segunda: "<<Atacante.DeFuzzify("Deseabilidad")<<std::endl;


    }
    if(ia.size() == 2){

    }
    if(ia.size() == 3){

    }

    else if(ia.size() == 2){

    }

    else if(ia.size() == 3){

    }

    //-------FIN CREACION IAS Y JUGADORES---------

    for(int i =0; i < coop.size();i++){
        cameras.push_back(new Camera());
    }
    
    ataque = true;
    molestar = false;
    blue = new Team(blueTeam,"blue");
    red = new Team(redTeam,"red");

    // Creamos el steering
    for(unsigned int i = 0; i < ia.size(); i++){
        movements.push_back(new SteeringBehaviours(ia.at(i)));
    }

    // Creamos la pelota
    Pelota::getInstancia()->InitCollide(PhysicsEngine::getInstancia()->getWorld());

    // FPS juego
    nbFrames = 0;

    // Iniciamos el temporizador con irrlicht
    // TimeStamp
    then = glfwGetTime();
    
    // MUSICA DE FONDO (CAMBIAR A OTRO SITIO)
    if(!CAudioEngine::getInstancia()->IsEventPlaying("event:/Musica/future_music"))
        CAudioEngine::getInstancia()->StopEvent("event:/Musica/arcade_music");
        CAudioEngine::getInstancia()->PlayEvent("event:/Musica/future_music");

    
    // Creamos los nitros
    int idNitro = 0;
    int secondRow = 0;
    int numNitros = 6;
	nitros.reserve(6);
    glm::vec3 posNitro(-75.f, -29.5f, -200.f);  

    
    //Inicializacion de Nitros y colocacion
    for (int i=0; i<2; i++){
        for(int j=0; j<3; j++){
            posNitro.z += 100;
            Nitro* nitro = new Nitro(posNitro,idNitro);
            nitros.push_back(nitro);
            rigidNitro = nitros.at(j + secondRow)->InitCollide(posNitro);
            idNitro++;
        }
        secondRow = 3;
        posNitro.x = 75.f;
        posNitro.z = -200.f;
    }
    //fin creacion de nitro

    // TEXTO
    // Creamos textos que no se vayan a modificar
    ITEngine::getInstancia()->createText("DEBUG MODE", 20.0f, 550.0f, 1.5f, glm::vec3(0.3f, 0.7f, 0.9f));
    ITEngine::getInstancia()->createText("PARAMETERS IA", 520.0f, 555.0f, 1.5f, glm::vec3(0.3f, 0.7f, 0.9f));
    // Creamos uno por defecto
    tPosIA = ITEngine::getInstancia()->createText("Texto IA", 520.0f, 520.0f);
    tCargasIA = ITEngine::getInstancia()->createText("Texto IA", 520.0f, 480.0f);
    tPowersIA = ITEngine::getInstancia()->createText("Texto IA", 520.0f, 440.0f);
    tStatesIA = ITEngine::getInstancia()->createText("Texto IA", 520.0f, 400.0f);

    // IA DEBUG
    actualIA = 0;
    oldState = GLFW_RELEASE;
    newState = -1;

    change = false;
    // Inicializamos contador
    timer = glfwGetTime();
    lastTime = glfwGetTime();
    // Cuenta Atras
    Options::getInstancia()->setStartTimer(glfwGetTime());
    cuentaAtras = false;
    cuentaAtras2 = false;

    mareoTimer = glfwGetTime();
    // Temporizador ingame
    // Minutos
    newMinutos = Options::getInstancia()->getTimer()/60 - 1;   
    minutos = -1;

    // Decenas
    decenas = -1;
    temporizadorDecenas = glfwGetTime(); 

    // Segundos
    unidades = 9;
    // Temporizador ingame Coop
    // Minutos
    newMinutos2 = Options::getInstancia()->getTimer()/60 - 1;   
    minutos2 = -1;

    // Decenas
    decenas2 = -1;
    temporizadorDecenas2 = glfwGetTime(); 

    // Segundos
    unidades2 = 9;
}

//metodo para respawn nitros

void GameState::checkRespawns(){

    for(int i=0; i < nitros.size(); i++){
        nitros.at(i)->respawn();
    }
}

//obtener nitros
std::vector<Nitro*> GameState::getNitros(){

    return nitros;
}


void GameState::Update(){  

    // Duracion establecida para el partido (para ello cambiar el numero)
    if(glfwGetTime() - timer <= Options::getInstancia()->getTimer()){
        // Actualiza temporizador
        int now = glfwGetTime() * 1000 - then;
        then = glfwGetTime() * 1000;

        if(voz*1000<=then && CAudioEngine::getInstancia()->Silence()){

            CAudioEngine::getInstancia()->Randompnj();
            voz+=(25+rand()%15);
          
        }
        
        // Actualiza fisicas
        Render(now);

        // Updateamos sonidos
        CAudioEngine::getInstancia()->Update();

        // Actualizamos contador
        if(!Options::getInstancia()->getCoop() && !ITEngine::getInstancia()->getIsDebugActive()){
            timerGame();
        }   
  
        // Actualiza jugador
        for(unsigned int i = 0; i < coop.size(); i++){
            if((glfwGetTime() - Options::getInstancia()->getStartTimer()) >= 3){
                // Controlador
                if(i == 0)
                    setGear();
                //Borrador de la cuenta atras
                if(Options::getInstancia()->getCoop() ==  false && cuentaAtras == true){
                    ITEngine::getInstancia()->getActiveHud()->deleteElement("Cuenta Atras");
                    cuentaAtras = false;
                }
                //Seleccionamos un jugador aleatorio del equipo enemigo para que el jugador le aplique el poder
                if(coop.at(i)->getTeam()=="red"){
                    randB = rand()%blue->getPlayers().size();
                    coop.at(i)->movement(blue->getPlayers().at(randB));
                }
                else{
                    randR = rand()%red->getPlayers().size();
                    coop.at(i)->movement(red->getPlayers().at(randR));
                }
            }else if(Options::getInstancia()->getCoop() == false && !ITEngine::getInstancia()->getIsDebugActive()){
                countDown(coop.at(i)->getPantalla());
            }
                
            coop.at(i)->updateWheels();
            coop.at(i)->calculateSpeed();
        }

        // Actualiza IA
        for(unsigned int i = 0; i < ia.size(); i++){
            ia.at(i)->updateWheels();
            if((glfwGetTime() - Options::getInstancia()->getStartTimer())>= 3){
                //UpdateIA(ia.at(i), movements.at(i));
               FuzzyUpdate(ia.at(i),movements.at(i));
            }
        }

        // Actualiza colisiones
        collide->checkCollides(getNitros(), red, blue);

        // Respawn de los nitros (meter en un futuro el de los players tambien aqui)
        checkRespawns();

        // FPS actuales
        setWindowFPS();

        // Crea las lineas y texto del escenario para el debug
        if(ITEngine::getInstancia()->getIsDebugActive()){
            setLinesEscenario();
            setTextEscenario();
        }

        // Actualiza camara y viewport
        for(unsigned int i = 0; i < coop.size(); i++){
            // para i == 0 Pantalla tiene que ser t
            // para i == 1 Pantalla tiene que ser m
            if(Options::getInstancia()->getCoop()){
        
                if(i == 0){
                    //Cambiamos viewport y seteamos el hud
                    ITEngine::getInstancia()->setViewport(0,0,ITEngine::getInstancia()->getWidth(),ITEngine::getInstancia()->getHeight()/2);
                    ITEngine::getInstancia()->setActiveHud("GameHud");
                      if((glfwGetTime() - Options::getInstancia()->getStartTimer()) >= 3 && cuentaAtras == true){
                        ITEngine::getInstancia()->getActiveHud()->deleteElement("Cuenta Atras");
                        cuentaAtras = false;
                      }
                      // Actualizamos contador
                    timerGame();
                }else if(i == 1){
                    // Igual que arriba para el otro jugador
                    ITEngine::getInstancia()->setViewport(0,ITEngine::getInstancia()->getHeight()/2,ITEngine::getInstancia()->getWidth(),ITEngine::getInstancia()->getHeight()/2);
                    ITEngine::getInstancia()->setActiveHud("GameHudCoop");
                     
                    if((glfwGetTime() - Options::getInstancia()->getStartTimer()) >= 3 && cuentaAtras2 == true){
                        ITEngine::getInstancia()->getActiveHud()->deleteElement("Cuenta Atras");
                        cuentaAtras2 = false;
                    }
                    // Actualizamos contador
                        timerGameCoop();
                }
            }

            cameras.at(i)->setActivate(true);

            obtainActualIA();

            cameras.at(i)->updateCamera(coop.at(i)->getAngle(),
                                        coop.at(i)->getAngleCamera(),
                                        coop.at(i)->getCoche(),
                                        coop.at(i)->getCameraHeight(),
                                        coop.at(i)->getPivote(),
                                        coop.at(i)->getPantalla(),
                                        ia.at(actualIA)->getCoche());                     
            
            //countdown para pantalla partida   
            if(((glfwGetTime() - Options::getInstancia()->getStartTimer()) < 3) && !ITEngine::getInstancia()->getIsDebugActive()){
                countDown(coop.at(i)->getPantalla());
            }
            

            // Dibujado
            ITEngine::getInstancia()->draw(shader); 
            ITEngine::getInstancia()->drawSkybox(shaderSkybox);
            
            if(ITEngine::getInstancia()->getIsDebugActive()){
                ia.at(actualIA)->updateDebugHud();
                ITEngine::getInstancia()->drawLines(shaderDebug);
                //ITEngine::getInstancia()->drawText(shaderText);
            }

            ITEngine::getInstancia()->drawHudMenus(shaderHud);
                
            cameras.at(i)->setActivate(false);
        }

    // Cambiamos de estado a score
    }else{
        // Seteamos el nuevo hud solo en la primera iteracion
        if(carga == 0){
            ITEngine::getInstancia()->setViewport(0,0,ITEngine::getInstancia()->getWidth(),ITEngine::getInstancia()->getHeight());
            Options::getInstancia()->setFinalScore(blue->getScore(), red->getScore());
            ITEngine::getInstancia()->setActiveHud("ScoreLoading");
        }

        // Incrementamos iteracion
        carga++;
        
        // Dibujamos la pantalla de carga
        ITEngine::getInstancia()->drawHudMenus(shaderHud);

        // Cambiamos al estado score en la tercera iteracion
        if(carga == 3)
            Game::getInstancia()->changeState(Auxiliar::states::ScoreState);
    }
}

void GameState::setWindowFPS(){

    double currentfps = glfwGetTime();
    double delta = currentfps - lastTime;

    nbFrames++;

    if(delta >= 1.0){

        int fps = nbFrames/delta;

        std::stringstream ss;
        ss << "Speed Crashers" << " " << "[" << fps << " FPS]";

        glfwSetWindowTitle(ITEngine::getInstancia()->getWindow(), ss.str().c_str());

        nbFrames = 0;
        lastTime = currentfps;
    }
}


void GameState::Render(int TDeltaTime){

    // UpdatePhysics y UpdateRender
    PhysicsEngine *bullet = PhysicsEngine::getInstancia();
	btDynamicsWorld *mundo = bullet->getWorld();
	mundo->stepSimulation(TDeltaTime * 0.001f, 30);

    std::vector<btRigidBody *> objects = bullet->getObjects();

	for(int i=0; i<objects.size(); i++) {
		
		UpdateRender(objects.at(i));
	}	
}

void GameState::UpdateRender(btRigidBody *TObject) {
	
	ITResourceMesh *Node = static_cast<ITResourceMesh*>(TObject->getUserPointer());

	// Cambiamos la posicion
	btVector3 Point = TObject->getCenterOfMassPosition();

	if(strcmp(Node->getResource()->getNickname(),"Jugador") == 0 || strcmp(Node->getResource()->getNickname(),"JugadorIA") == 0){
	    Node->setPosition(glm::vec3((float)Point[0],(float)Point[1]+1.25,(float)Point[2]));
    }else{
	    Node->setPosition(glm::vec3((float)Point[0],(float)Point[1],(float)Point[2]));
    }
    
    // Cambiamos la rotacion
    const btQuaternion& TQuat = TObject->getOrientation();
	glm::vec3 axis(TQuat.getAxis().getX(), TQuat.getAxis().getY(), TQuat.getAxis().getZ());
	float angle = TQuat.getAngle() * (180.0f / M_PI);
	Node->setRotation(axis, angle);
}


void GameState::setGear(){

    // Indicamos controlador
    if(coop.size() == 1 && glfwJoystickPresent(GLFW_JOYSTICK_1) == 1 && change == false){
        coop.at(0)->setPantalla('m');
        change = true;
    }else if(coop.size() == 1 && glfwJoystickPresent(GLFW_JOYSTICK_1) != 1 && change == true){
        coop.at(0)->setPantalla('t');
        change = false;
    }
}

void GameState::setCoopHud(){
    if(Options::getInstancia()->getCoop()){
        if(z == 0){
            ITEngine::getInstancia()->setActiveHud("GameHud");
        }else{
            ITEngine::getInstancia()->setActiveHud("GameHudCoop");
        }
        if(z == 1){
            z=-1;
        }
        z++;
    }
   
}

void GameState::countDown(char x){
    //-------------------Zona individual o teclado--------------------------------
    if((x == 't' && Options::getInstancia()->getCoop() )|| (!Options::getInstancia()->getCoop() && x != 'c') ){
  
        if((glfwGetTime() - Options::getInstancia()->getStartTimer()) > 0 && (glfwGetTime() - Options::getInstancia()->getStartTimer()) < 1 && cuentaAtras == false){
            ITEngine::getInstancia()->setActiveHud("GameHud");
            ITEngine::getInstancia()->getActiveHud()->addElement("Cuenta Atras","media/Hud/Cuenta Atras/3.png");
            ITEngine::getInstancia()->getActiveHud()->scaleElement("Cuenta Atras", 0.8, 0.8);
            cuentaAtras = true;
        }else if((glfwGetTime() - Options::getInstancia()->getStartTimer()) > 1 && (glfwGetTime() - Options::getInstancia()->getStartTimer()) < 2 && cuentaAtras == true){
            ITEngine::getInstancia()->setActiveHud("GameHud");
            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("Cuenta Atras","media/Hud/Cuenta Atras/2.png");
            cuentaAtras = false;
        }else if((glfwGetTime() - Options::getInstancia()->getStartTimer()) > 2 && (glfwGetTime() - Options::getInstancia()->getStartTimer()) < 3 && cuentaAtras == false){
            ITEngine::getInstancia()->setActiveHud("GameHud");
            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("Cuenta Atras","media/Hud/Cuenta Atras/1.png");
            cuentaAtras = true;
        }
    }
    //-------------------Zona multijugador-----------------------------------------
    else if(x == 'm' && Options::getInstancia()->getCoop()){
       
        if((glfwGetTime() - Options::getInstancia()->getStartTimer()) > 0 && (glfwGetTime() - Options::getInstancia()->getStartTimer()) < 1 && cuentaAtras2 == false){
            ITEngine::getInstancia()->setActiveHud("GameHudCoop");
            ITEngine::getInstancia()->getActiveHud()->addElement("Cuenta Atras","media/Hud/Cuenta Atras/3.png");
            ITEngine::getInstancia()->getActiveHud()->scaleElement("Cuenta Atras", 0.8, 0.8);
            
            cuentaAtras2 = true;
        }else if((glfwGetTime() - Options::getInstancia()->getStartTimer()) > 1 && (glfwGetTime() - Options::getInstancia()->getStartTimer()) < 2 && cuentaAtras2 == true){
            ITEngine::getInstancia()->setActiveHud("GameHudCoop");
            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("Cuenta Atras","media/Hud/Cuenta Atras/2.png");
            cuentaAtras2 = false;
        }else if((glfwGetTime() - Options::getInstancia()->getStartTimer()) > 2 && (glfwGetTime() - Options::getInstancia()->getStartTimer()) < 3 && cuentaAtras2 == false){
            ITEngine::getInstancia()->setActiveHud("GameHudCoop");
            ITEngine::getInstancia()->getActiveHud()->changeTextureElement("Cuenta Atras","media/Hud/Cuenta Atras/1.png");
            cuentaAtras2 = true;
        }
    }
   
}


void GameState::timerGame(){

    // Decenas
    newDecenas = ((int)glfwGetTime() - (int)temporizadorDecenas)/10;
    newUnidades = ((int)glfwGetTime() - (int)temporizadorDecenas)%10;

    if(decenas != newDecenas){
        switch(newDecenas){
            case 0: ITEngine::getInstancia()->getHud("GameHud")->changeTextureElement("TimerDecenas", "media/Hud/Contador/5.png"); break;
            case 1: ITEngine::getInstancia()->getHud("GameHud")->changeTextureElement("TimerDecenas", "media/Hud/Contador/4.png"); break;
            case 2: ITEngine::getInstancia()->getHud("GameHud")->changeTextureElement("TimerDecenas", "media/Hud/Contador/3.png"); break;
            case 3: ITEngine::getInstancia()->getHud("GameHud")->changeTextureElement("TimerDecenas", "media/Hud/Contador/2.png"); break;
            case 4: ITEngine::getInstancia()->getHud("GameHud")->changeTextureElement("TimerDecenas", "media/Hud/Contador/1.png"); break;
            case 5: ITEngine::getInstancia()->getHud("GameHud")->changeTextureElement("TimerDecenas", "media/Hud/Contador/0.png"); break;
            case 6: ITEngine::getInstancia()->getHud("GameHud")->changeTextureElement("TimerDecenas", "media/Hud/Contador/5.png");
                    newMinutos--;
                    temporizadorDecenas = glfwGetTime(); break;
        }

        // Actualizamos decenas
        decenas = newDecenas;
    }

    // Segundos
    if(unidades != newUnidades){
        switch(newUnidades){
            case 0: ITEngine::getInstancia()->getHud("GameHud")->changeTextureElement("TimerSegundos", "media/Hud/Contador/9.png"); break;
            case 1: ITEngine::getInstancia()->getHud("GameHud")->changeTextureElement("TimerSegundos", "media/Hud/Contador/8.png"); break;
            case 2: ITEngine::getInstancia()->getHud("GameHud")->changeTextureElement("TimerSegundos", "media/Hud/Contador/7.png"); break;
            case 3: ITEngine::getInstancia()->getHud("GameHud")->changeTextureElement("TimerSegundos", "media/Hud/Contador/6.png"); break;
            case 4: ITEngine::getInstancia()->getHud("GameHud")->changeTextureElement("TimerSegundos", "media/Hud/Contador/5.png"); break;
            case 5: ITEngine::getInstancia()->getHud("GameHud")->changeTextureElement("TimerSegundos", "media/Hud/Contador/4.png"); break;
            case 6: ITEngine::getInstancia()->getHud("GameHud")->changeTextureElement("TimerSegundos", "media/Hud/Contador/3.png"); break;
            case 7: ITEngine::getInstancia()->getHud("GameHud")->changeTextureElement("TimerSegundos", "media/Hud/Contador/2.png"); break;
            case 8: ITEngine::getInstancia()->getHud("GameHud")->changeTextureElement("TimerSegundos", "media/Hud/Contador/1.png"); break;
            case 9: ITEngine::getInstancia()->getHud("GameHud")->changeTextureElement("TimerSegundos", "media/Hud/Contador/0.png"); break;
        }
        unidades = newUnidades;
    }

    // Minutos
    if(minutos != newMinutos){
        switch(newMinutos){
            case 0: ITEngine::getInstancia()->getHud("GameHud")->changeTextureElement("TimerMinutos", "media/Hud/Contador/0.png"); break;
            case 1: ITEngine::getInstancia()->getHud("GameHud")->changeTextureElement("TimerMinutos", "media/Hud/Contador/1.png"); break;
            case 2: ITEngine::getInstancia()->getHud("GameHud")->changeTextureElement("TimerMinutos", "media/Hud/Contador/2.png"); break;
            case 3: ITEngine::getInstancia()->getHud("GameHud")->changeTextureElement("TimerMinutos", "media/Hud/Contador/3.png"); break;
            case 4: ITEngine::getInstancia()->getHud("GameHud")->changeTextureElement("TimerMinutos", "media/Hud/Contador/4.png"); break;
            case 5: ITEngine::getInstancia()->getHud("GameHud")->changeTextureElement("TimerMinutos", "media/Hud/Contador/5.png"); break;
        }
        minutos = newMinutos;
    }
}
void GameState::timerGameCoop(){
     // Decenas
    newDecenas2 = ((int)glfwGetTime() - (int)temporizadorDecenas2)/10;
    newUnidades2 = ((int)glfwGetTime() - (int)temporizadorDecenas2)%10;

    if(decenas2 != newDecenas2){
        switch(newDecenas2){
            case 0: ITEngine::getInstancia()->getHud("GameHudCoop")->changeTextureElement("TimerDecenas", "media/Hud/Contador/5.png"); break;
            case 1: ITEngine::getInstancia()->getHud("GameHudCoop")->changeTextureElement("TimerDecenas", "media/Hud/Contador/4.png"); break;
            case 2: ITEngine::getInstancia()->getHud("GameHudCoop")->changeTextureElement("TimerDecenas", "media/Hud/Contador/3.png"); break;
            case 3: ITEngine::getInstancia()->getHud("GameHudCoop")->changeTextureElement("TimerDecenas", "media/Hud/Contador/2.png"); break;
            case 4: ITEngine::getInstancia()->getHud("GameHudCoop")->changeTextureElement("TimerDecenas", "media/Hud/Contador/1.png"); break;
            case 5: ITEngine::getInstancia()->getHud("GameHudCoop")->changeTextureElement("TimerDecenas", "media/Hud/Contador/0.png"); break;
            case 6: ITEngine::getInstancia()->getHud("GameHudCoop")->changeTextureElement("TimerDecenas", "media/Hud/Contador/5.png");
                    newMinutos2--;
                    temporizadorDecenas2 = glfwGetTime(); break;
        }

        // Actualizamos decenas
        decenas2 = newDecenas2;
    }

    // Segundos
    if(unidades2 != newUnidades2){
        switch(newUnidades2){
            case 0: ITEngine::getInstancia()->getHud("GameHudCoop")->changeTextureElement("TimerSegundos", "media/Hud/Contador/9.png"); break;
            case 1: ITEngine::getInstancia()->getHud("GameHudCoop")->changeTextureElement("TimerSegundos", "media/Hud/Contador/8.png"); break;
            case 2: ITEngine::getInstancia()->getHud("GameHudCoop")->changeTextureElement("TimerSegundos", "media/Hud/Contador/7.png"); break;
            case 3: ITEngine::getInstancia()->getHud("GameHudCoop")->changeTextureElement("TimerSegundos", "media/Hud/Contador/6.png"); break;
            case 4: ITEngine::getInstancia()->getHud("GameHudCoop")->changeTextureElement("TimerSegundos", "media/Hud/Contador/5.png"); break;
            case 5: ITEngine::getInstancia()->getHud("GameHudCoop")->changeTextureElement("TimerSegundos", "media/Hud/Contador/4.png"); break;
            case 6: ITEngine::getInstancia()->getHud("GameHudCoop")->changeTextureElement("TimerSegundos", "media/Hud/Contador/3.png"); break;
            case 7: ITEngine::getInstancia()->getHud("GameHudCoop")->changeTextureElement("TimerSegundos", "media/Hud/Contador/2.png"); break;
            case 8: ITEngine::getInstancia()->getHud("GameHudCoop")->changeTextureElement("TimerSegundos", "media/Hud/Contador/1.png"); break;
            case 9: ITEngine::getInstancia()->getHud("GameHudCoop")->changeTextureElement("TimerSegundos", "media/Hud/Contador/0.png"); break;
        }
        unidades2 = newUnidades2;
    }

    // Minutos
    if(minutos2 != newMinutos2){
        switch(newMinutos2){
            case 0: ITEngine::getInstancia()->getHud("GameHudCoop")->changeTextureElement("TimerMinutos", "media/Hud/Contador/0.png"); break;
            case 1: ITEngine::getInstancia()->getHud("GameHudCoop")->changeTextureElement("TimerMinutos", "media/Hud/Contador/1.png"); break;
            case 2: ITEngine::getInstancia()->getHud("GameHudCoop")->changeTextureElement("TimerMinutos", "media/Hud/Contador/2.png"); break;
            case 3: ITEngine::getInstancia()->getHud("GameHudCoop")->changeTextureElement("TimerMinutos", "media/Hud/Contador/3.png"); break;
            case 4: ITEngine::getInstancia()->getHud("GameHudCoop")->changeTextureElement("TimerMinutos", "media/Hud/Contador/4.png"); break;
            case 5: ITEngine::getInstancia()->getHud("GameHudCoop")->changeTextureElement("TimerMinutos", "media/Hud/Contador/5.png"); break;
        }
        minutos2 = newMinutos2;
    }

}

void GameState::FuzzyUpdate(IA* ia,SteeringBehaviours* movements){
    vec2f posIA;
    vec2f nitroPos;
    vec2f bola;

    posIA.x = ia->getCoche()->getPosition().x;
    posIA.y = ia->getCoche()->getPosition().z;
      

    bola.x = Pelota::getInstancia()->getNode()->getPosition().x;
    bola.y = Pelota::getInstancia()->getNode()->getPosition().z;
    if(  glfwGetTime() -ia->getRepetir() > 2 && (posIA.x > 88.3 || posIA.x < -88.9|| abs(posIA.y) > 147.8)){
        if(ia->getWho() == 'D'){
            if(abs(posIA.x) > 26){
                ia->MarchaAtras();
            }
            else if(abs(posIA.x)<=26 && abs(posIA.y) > 150){
                ia->setGiro(0.5);
                ia->MarchaAtras();
            }
        }
        else{
            ia->MarchaAtras();
        }
    }
    else if( glfwGetTime() -ia->getRepetir() > 1){
        switch (ia->getWho())
        {
            case 'A':
            {
                
                double centro = FuzzyEstado(posIA.y,ia);
                if(centro < 35){
                    vec2f centr;
                    centr.x = 0;
                    centr.y = 0;
                    ia->behaviour(movements->Seek(posIA,centr),centro);
                }
                else{
                if(FuzzyEstado(bola.y,ia) < 35){
                    //std::cout<<"Defensa "<<std::endl;
                    std::vector<double> vec = FuzzyDefender(ia);
                     std::cout<<"cual :"<<vec.at(0)<<std::endl;
                      std::cout<<"posicion :"<<vec.at(1)<<std::endl;
                      
                  
                    
                   
                        if(vec.at(0) == 1){
                            //Usar poder
                            ran = vec.at(1);
                            ia->setEstado2(Auxiliar::IAstate::USING_P);
                            ia->setPowerTimer();

                            if(ia->getTeam() == "red"){

                                ia->UsePowers(blue->getPlayers().at(ran));

                            }
                            else{
                            
                                ia->UsePowers(red->getPlayers().at(ran));

                            }

                        }
                        else if(vec.at(0) == 2){
                            //Molestar
                            vec2f rival;
                            if(ia->getTeam() == "red"){
                                rival.x = blue->getPlayers().at(vec.at(1))->getCoche()->getPosition().x;
                                rival.y = blue->getPlayers().at(vec.at(1))->getCoche()->getPosition().z;
                            }
                            else{
                                rival.x = red->getPlayers().at(vec.at(1))->getCoche()->getPosition().x;
                                rival.y = red->getPlayers().at(vec.at(1))->getCoche()->getPosition().z;
                            }
                            ia->behaviour(movements->Seek(posIA,rival),vec.at(2));

                        }
                        else if(vec.at(0) == 3){
                            //Nitro

                            nitroPos.x = nitros.at((int)vec.at(1))->getNode()->getPosition().x;
                            nitroPos.y = nitros.at((int)vec.at(1))->getNode()->getPosition().z;
                            ia->behaviour(movements->Seek(posIA,nitroPos),vec.at(1));

                        }

                    
                }
                else{

                    //std::cout<<"Ataque "<<std::endl;
                    std::vector<double> vec = FuzzyAtacar(ia);   
                    
                    if(vec.at(0) == 4){
                            
                        double velocidad = FuzzyUsing(ia);
                        
                        if(ia->getCargas() > 0 && velocidad > 60){
                            ia->setEstado2(Auxiliar::IAstate::UTILIZAR_N);
                        }
                        // std::cout<<"Pelota: "<<std::endl;
                        ia->behaviour(movements->Seek(posIA,bola),vec.at(1));
                    
                    }
                    else{
                        
                        // std::cout<<"Nitro: "<<vec.at(0) <<std::endl;
                        nitroPos.x = nitros.at((int)vec.at(0))->getNode()->getPosition().x;
                        nitroPos.y = nitros.at((int)vec.at(0))->getNode()->getPosition().z;
                        ia->behaviour(movements->Seek(posIA,nitroPos),vec.at(1));

                    }
                }
            }
            }
        break;
        
        case 'D':
            {
                
                double porteria = FuzzyEstado(posIA.y,ia);
                vec2f port ;
                   
                if(porteria > 35){
                    
                    
                    port.x = -2;
                    if(ia->getTeam() == "red"){
                        port.y = 130;
                    }
                    else{
                        
                        port.y = -125;
                    }

                    ia->behaviour(movements->Seek(posIA,port),porteria);
                }
                else{
                   
                    if(FuzzyEstado(bola.y,ia) < 35){
                          
                        //Defensa
                           std::cout << "Defensa: "<<ia->getTeam()<<std::endl;
                        std::vector<double> vec = FuzzyDefensa(ia);
                        if(vec.at(0) == 0){
                            std::cout << "Velocidad: "<<vec.at(1)<<std::endl;
                            ia->behaviour(movements->Seek(posIA,bola),vec.at(1));
                        }
                        else if(vec.at(0) == 1){
                            ia->setEstado2(Auxiliar::IAstate::USING_P);
                            ia->setPowerTimer();
                            ia->UsePowers(ia);
                        }
                    }
                    else{
                        port.x = -2;
                        if(ia->getTeam() == "red"){
                              port.y = 130;
                        }
                        else{
                            port.y = -125;
                        }
                      
                        //Ataque
                       // std::cout << "Ataque: "<<porteria<<std::endl;
                        ia->behaviour(movements->Seek(posIA,port),porteria);

                    }

                }

            }
        break;
        
        case 'C':
                if(FuzzyEstado(bola.y,ia) < 35){
                    //defensa
                      std::vector<double> vec = FuzzyDefensa(ia);
                        if(vec.at(0) == 0){
                            ia->behaviour(movements->Seek(posIA,bola),vec.at(1));
                        }

                }
                else{
                    //Ataque

                    std::vector<double> vec = FuzzyAtacar(ia);   
                    
                    if(vec.at(0) == 4){
                            
                        double velocidad = FuzzyUsing(ia);
                        
                        if(ia->getCargas() > 0 && velocidad > 60){
                            ia->setEstado2(Auxiliar::IAstate::UTILIZAR_N);
                        }
                        // std::cout<<"Pelota: "<<std::endl;
                        ia->behaviour(movements->Seek(posIA,bola),vec.at(1));
                    
                    }
                    else{
                        
                        // std::cout<<"Nitro: "<<vec.at(0) <<std::endl;
                        nitroPos.x = nitros.at((int)vec.at(0))->getNode()->getPosition().x;
                        nitroPos.y = nitros.at((int)vec.at(0))->getNode()->getPosition().z;
                        ia->behaviour(movements->Seek(posIA,nitroPos),vec.at(1));

                    }

                }
        break;
    
        default:
            break;
    }
}
if(ia->getEstado2() == Auxiliar::IAstate::USING_P){
  
    if(glfwGetTime() - ia->getPoderTimer() >=5){
        if(ia->getWho() == 'A'){
            ResetarPoderes(ia, ran);
        }
        else if(ia->getWho() == 'D'){
            ia->setCD();
            ia->getPoderes()->Congelar();
            ia->setEstado2(Auxiliar::IAstate::DEFAULT);
        }

    }
} 
}

void GameState::UpdateIA(IA* ia, SteeringBehaviours* movements){
    int usar = 0;
    bool defender = false;

    vec2f posIA;
    vec2f nitroPos;

    posIA.x = ia->getCoche()->getPosition().x;
    posIA.y = ia->getCoche()->getPosition().z;

    vec2f bola;

    bola.x = Pelota::getInstancia()->getNode()->getPosition().x;
    bola.y = Pelota::getInstancia()->getNode()->getPosition().z;
  
    if(ia->getEstado2()!=Auxiliar::IAstate::POWERM){
    if(ia->getWho()!='D'){
        //Setear variable a recoger nitro si esta cercano y hay cargas vacias
        for(int i =0; i<nitros.size();i++){
            if(ia->getCargas()<3 && nitros.at(i)->getNode()->isVisible()){
                if((abs(nitros.at(i)->getNode()->getPosition().x - ia->getCoche()->getPosition().x) )<= 15 && 
                    (abs(nitros.at(i)->getNode()->getPosition().z - ia->getCoche()->getPosition().z) )<= 30){
                  
                    ia->setEstado2(Auxiliar::IAstate::NITRO);
                
                    nitroPos.x = nitros.at(i)->getNode()->getPosition().x;
                    nitroPos.y = nitros.at(i)->getNode()->getPosition().z;
                }
            }
        }
    }
    
    vec2f porteria(0,0);

    /*
        Control de las distintas IAs, condición principal para cambiar su comportamiento.

    */

    switch (ia->getWho())
    {
        case 'A':
        {
            //Comprobamos el equipo, después donde esta la pelota, Al ser la Ia Ataque si esta lejos la pelota cambiara de estado a None.
            if(ia->getTeam()=="red"){
                if(bola.y>=mitadInf){
                    ia->setEstado(Auxiliar::IAstate::NONE);
                    
                }
            }
            else{
                if(bola.y<=-mitadInf){
                    ia->setEstado(Auxiliar::IAstate::NONE);
                }
            }
        }
            break;
        case 'D':
        {
           
             if(ia->getTeam()=="red"){
                  porteria.y=Options::getInstancia()->getForwardScenario();
                if(bola.y<mitadSup){
                   
                   ia->setEstado(Auxiliar::IAstate::NONE);
                }

            }
            else{
                 porteria.y=-Options::getInstancia()->getForwardScenario();
                 if(bola.y>-mitadSup){
                     ia->setEstado(Auxiliar::IAstate::NONE);
                 }
            }
        }
            break;
        case 'C':
                
        {
                usar =rand()%5;
            if(ia->getTeam()=="red"){
                 porteria.y=Options::getInstancia()->getForwardScenario();
                if(bola.y>mitadSup){
                    //Defensa
                    ia->setEstado(Auxiliar::IAstate::DEFENSA);
                
                }
                else{
                    //Ataque
                    ia->setEstado(Auxiliar::IAstate::ATAQUE);
                }
            }
            else{
                porteria.y=-Options::getInstancia()->getForwardScenario();
                if(bola.y<=-mitadSup){
                    ia->setEstado(Auxiliar::IAstate::DEFENSA);
                }
                else{
                    ia->setEstado(Auxiliar::IAstate::ATAQUE);
                }
            }
        }
            break;
        default:
            break;
    }

    
    //--------------------------Zona ATAQUE------------------------------------------------------
    if(ia->getEstado()==Auxiliar::IAstate::ATAQUE){

        if(ia->getCargas()>0){
            if(abs(bola.x - posIA.x)>=20 && abs(bola.y - posIA.y)>=70){
                ia->setEstado2(Auxiliar::IAstate::UTILIZAR_N);
            }
        }   

        if(ia->getEstado2()!=Auxiliar::IAstate::NITRO){
            
            if(abs(posIA.x) > Options::getInstancia()->getWidthMax() || abs(posIA.y) > Options::getInstancia()->getForwardScenario()){
                    ia->behaviour(movements->Seek(posIA, bola), true);
            }else{
                    ia->behaviour(movements->Seek(posIA, bola), false);
            }
        }
        

    }
    //----------------------------Final Ataque--------------------------------------------------
    //----------------------------Zona DEFENSA---------------------------------------------------
    else if(ia->getEstado()==Auxiliar::IAstate::DEFENSA){
              
                if(ia->getEstado2()!=Auxiliar::IAstate::NITRO){
                    if(ia->getTeam()=="red"){
                        if(bola.y >=(Options::getInstancia()->getForwardScenario()-5) && (bola.x > -Options::getInstancia()->getWidthGoal() && bola.x <Options::getInstancia()->getWidthGoal())){
                            if(glfwGetTime() - ia->getPoderTimer() >= 10){
                                ia->UsePowers(ia);
                                ia->setEstado2(Auxiliar::IAstate::USING_P);
                            }
                        }
                        porteria.y=Options::getInstancia()->getForwardScenario();
                        if(bola.y>=mitadSup){
                            
                            if(abs(posIA.x) > Options::getInstancia()->getWidthMax() || abs(posIA.y) > Options::getInstancia()->getForwardScenario()){
                                ia->behaviour(movements->Seek(posIA, bola), true);
                            }else{
                                ia->behaviour(movements->Seek(posIA, bola), false);
                            }
                        }
                    }
                    else{
                         if(bola.y <=(-Options::getInstancia()->getForwardScenario()+5)&&(bola.x > -Options::getInstancia()->getWidthGoal() && bola.x <Options::getInstancia()->getWidthGoal())){
                            if(glfwGetTime() - ia->getPoderTimer() >= 10){
                                ia->UsePowers(ia);
                                ia->setEstado2(Auxiliar::IAstate::USING_P);
                            }
                        }
                          porteria.y=-Options::getInstancia()->getForwardScenario();
                        if(bola.y<=-mitadSup){
                            if(abs(posIA.x) > Options::getInstancia()->getWidthMax() || abs(posIA.y) > Options::getInstancia()->getForwardScenario()){
                                ia->behaviour(movements->Seek(posIA, bola), true);
                            }else{
                                ia->behaviour(movements->Seek(posIA, bola), false);
                            }
                        }
                        
                    }
                    
                }
            
        
    }
    //---------------------------------------Final Defensa----------------------------------------------------------
    //Activacion recogida nitro
    if(ia->getEstado()!=Auxiliar::IAstate::NONE && ia->getEstado2()==Auxiliar::IAstate::NITRO){
           
            ia->behaviour(movements->Seek(posIA, nitroPos), false);
           
    }
    //Zona de comportamientos
    //Atacante tiene bola en defensa pasa a 3 comportamientos
    //1º Molestar rival cercano (dependiendo distancia)
    //2º Recogida de nitro (dependiendo de distancia y carga)
    //3º Uso del poder mareo dependiendo de las anteriores

    //Defensa si bola esta en ataque esperara dando vueltas alrededor porteria
    else if(ia->getEstado()==Auxiliar::IAstate::NONE){
        switch (ia->getWho())
        {
            case 'A':
             {
                vec2f res;
                res.x=0.0;
                res.y=0.0;

                if(ia->getTeam()=="red"){
                    if(ia->getCoche()->getPosition().x<=mitadInf){
                        ia->behaviour(movements->Seek(posIA,res),false);
                    }
                    if(bola.y<mitadInf){
                        ia->setEstado(Auxiliar::IAstate::ATAQUE);
                    }
                    else{
                        for(unsigned int i = 0;i<blue->getPlayers().size();i++){
                            if(abs(ia->getCoche()->getPosition().x - blue->getPlayers().at(i)->getCoche()->getPosition().x) <= 18 && 
                            abs(ia->getCoche()->getPosition().z - blue->getPlayers().at(i)->getCoche()->getPosition().z) <= 18 ){
                                molestar = true;
                            }
                        }
                    }
                }
                else{
                    if(ia->getCoche()->getPosition().x>= -mitadInf){
                        ia->behaviour(movements->Seek(posIA,res),false);
                    
                    }
                    if(bola.y>-mitadInf){
                        ia->setEstado(Auxiliar::IAstate::ATAQUE);
                    }
                    else{
                        for(unsigned int i = 0;i<red->getPlayers().size();i++){
                            if(abs(ia->getCoche()->getPosition().x - red->getPlayers().at(i)->getCoche()->getPosition().x) <= 18 && 
                            abs(ia->getCoche()->getPosition().z - red->getPlayers().at(i)->getCoche()->getPosition().z) <= 18 ){
                                molestar = true;
                            }
                        }
                    }
                }
                //-----------------------------------------Comportamiento molestar rival cercano-----------------------------------
                if(molestar){
                    int cercano = 0; //posicion del player
                    int distancia = 0; //X1 - X2  + Z1 - Z2 (Absoluto) el menor esta más cerca
                    int menordist = 0; //distancia menor
                    vec2f follow; //al que perseguir

                    //Molestar al rival más cercano.
                    if(ia->getTeam()=="red"){
                        for(int i=0;i<blue->getPlayers().size();i++){
                            if(blue->getPlayers().at(i)!=nullptr){
                                distancia = abs(ia->getCoche()->getPosition().x - blue->getPlayers().at(i)->getCoche()->getPosition().x) 
                                + abs(ia->getCoche()->getPosition().z - blue->getPlayers().at(i)->getCoche()->getPosition().z);
                            }
                            if(menordist==0){
                                menordist = distancia;
                            }
                            else if(distancia < menordist){
                                menordist = distancia;
                                cercano = i;
                            }
                        }
                        follow.x = blue->getPlayers().at(cercano)->getCoche()->getPosition().x;
                        follow.y = blue->getPlayers().at(cercano)->getCoche()->getPosition().z;
                    }
                    else{
                        for(int i=0;i<red->getPlayers().size();i++){
                            if(red->getPlayers().at(i)!=nullptr){
                                distancia = abs(ia->getCoche()->getPosition().x - red->getPlayers().at(i)->getCoche()->getPosition().x) 
                                + abs(ia->getCoche()->getPosition().z - red->getPlayers().at(i)->getCoche()->getPosition().z);
                            }
                            if(menordist==0){
                                menordist = distancia;
                            }
                            else if(distancia < menordist){
                                menordist = distancia;
                                cercano = i;
                            }
                        }
                        follow.x = red->getPlayers().at(cercano)->getCoche()->getPosition().x;
                        follow.y = red->getPlayers().at(cercano)->getCoche()->getPosition().z;

                    }

                    if(abs(posIA.x) > Options::getInstancia()->getWidthMax() || abs(posIA.y) > Options::getInstancia()->getForwardScenario()){
                        ia->behaviour(movements->Seek(posIA, follow), true);
                    }else{
                        ia->behaviour(movements->Seek(posIA, follow), false);
                    }

                    molestar = false;
                }
                //----------------------------------------------Comportamieno nitro----------------------------------------
                else if(ia->getEstado2() == Auxiliar::IAstate::NITRO){
                        //Recoger nitro más cercano
                        int cercano = 0; //posicion del player
                        int distancia = 0; //X1 - X2  + Z1 - Z2 (Absoluto) el menor esta más cerca
                        int menordist = 0; //distancia menor
                        if(ia->getCargas()<=2){
                        
                            for(int i =0; i<nitros.size();i++){
                                
                                if(nitros.at(i)!=nullptr){
                                    distancia = abs(ia->getCoche()->getPosition().x - nitros.at(i)->getNode()->getPosition().x) 
                                    + abs(ia->getCoche()->getPosition().z - nitros.at(i)->getNode()->getPosition().z);
                                }
                                if(menordist == 0){
                                    menordist = distancia;
                                }
                                else if(distancia < menordist){
                                    menordist = distancia;
                                    cercano = i;
                                }
                                 
                            }
                            if(nitros.at(cercano)->getNode()->isVisible()){
                                nitroPos.x = nitros.at(cercano)->getNode()->getPosition().x;
                                nitroPos.y = nitros.at(cercano)->getNode()->getPosition().z;
                                if(abs(posIA.x) > 98.5 || abs(posIA.y) > 194.5){
                                    ia->behaviour(movements->Seek(posIA, nitroPos), true);
                                }else{
                                    ia->behaviour(movements->Seek(posIA, nitroPos), false);
                                }
                            }
                    
                        }
                    ia->setEstado2(Auxiliar::IAstate::DEFAULT);

                
                }
                //-------------------------------------------------------Comportamiento uso de poder---------------------------------------------
                else if(molestar == false && ia->getEstado2() != Auxiliar::IAstate::NITRO){
                    // Usar poderes
                    if(glfwGetTime()-mareoTimer >=12){
                        if(ia->getTeam()=="red"){
                            int size = blue->getPlayers().size();
                            ran =rand()%size;
                            if(blue->getPlayers().at(ran)!=nullptr){
                    
                                ia->setEstado2(Auxiliar::IAstate::USING_P);
                                ia->UsePowers(blue->getPlayers().at(ran));
                            
                                position = ran;
                            }
                        }
                        else{
                            int size = red->getPlayers().size();
                            ran =rand()%size;
                            if(red->getPlayers().at(ran)!=nullptr){
                                ia->setEstado2(Auxiliar::IAstate::USING_P);
                                ia->UsePowers(red->getPlayers().at(ran));
                            
                                position = ran;
                             

                            }
                        }
                    }
                }
             }
                break;
            
            case 'D':
            {
                if(ia->getTeam()=="red"){
                    porteria.y = Options::getInstancia()->getForwardScenario()-20;
                    porteria.x = 0;
                    if(bola.y>=mitadSup){
                        ia->setEstado(Auxiliar::IAstate::DEFENSA);
                    }
                    if(posIA.y<mitadSup){
                        
                        ia->setEstado2(Auxiliar::IAstate::DEFENSA_L);
                        ia->behaviour(movements->Seek(posIA,porteria),false);
                    }
                    else{
                        ia->setEstado2(Auxiliar::IAstate::DEFENSA_L);
                        ia->behaviour(movements->Seek(posIA,porteria),false);
                    }

                }
                else{
                    porteria.y = -Options::getInstancia()->getForwardScenario()+20;
                    porteria.x = 0;
                    if(bola.y<=-mitadSup){
                        ia->setEstado(Auxiliar::IAstate::DEFENSA);
                    }
                        ia->setEstado2(Auxiliar::IAstate::DEFENSA_L);
                        ia->behaviour(movements->Seek(posIA,porteria),false);
                    
                   

                }



            }
                break;
            default:
                break;
        }
    }
    }
    if(ia->getWho()=='C' && usar==2){
        //Revisar
        if(ia->getTeam()=="red"){
            int aleatorio = rand()%blue->getPlayers().size();
            ia->UsePowers(blue->getPlayers().at(aleatorio));
        }
        else{
            int aleatorio = rand()%red->getPlayers().size();
            ia->UsePowers(red->getPlayers().at(aleatorio));
        }
    }
    //Uso del poder de mareo por la IA de ataque
    if(ia->getWho()=='A'&&ia->getEstado2()==Auxiliar::IAstate::USING_P){
        if(glfwGetTime() - ia->getPoderTimer() >= 5){   
            if(ia->getTeam()=="red"){

                ia->getPoderes()->ResetMareo(blue->getPlayers().at(ran));
            }
            else{
                ia->getPoderes()->ResetMareo(red->getPlayers().at(ran));
            }
             ia->setEstado2(Auxiliar::IAstate::DEFAULT);
        }
    }
    //TImer poder defensa igualado al de partida
    if(ia->getWho()=='D'&&ia->getEstado2()==Auxiliar::IAstate::USING_P){
        ia->setPowerTimer();
        ia->setEstado2(Auxiliar::IAstate::DEFAULT);
    }

    //Resetear controles a los afectados por el poder de mareo
    if(ia->getEstado2()==Auxiliar::IAstate::POWERM){
        if(glfwGetTime() - ia->getPoderTimer() >= 5){
             
            ia->setEstado2(Auxiliar::IAstate::DEFAULT);
            
        }
        else{
            ia->AfectedM();
        }

    }

    //SALTO DE LA IA
    if(abs(Pelota::getInstancia()->getNode()->getPosition().y - ia->getCoche()->getPosition().y) <=10 && abs(Pelota::getInstancia()->getNode()->getPosition().y - ia->getCoche()->getPosition().y) >4 
    && abs(bola.x - ia->getCoche()->getPosition().x)<=2 && abs(bola.y - ia->getCoche()->getPosition().z)<=2){
        ia->setEstado2(Auxiliar::IAstate::JUMP);
    }

    if(ia->getEstado2()==Auxiliar::IAstate::JUMP){
        ia->jump();
    }

}

void GameState::setLinesEscenario(){

    float x = Options::getInstancia()->getWidthMax();
    float y = -30;
    float z = Options::getInstancia()->getForwardScenario();

    // std::cout << "Medidas escenario: " << x << ", " << y << ", " << z << std::endl;

    // ATAQUE

    glm::vec4 col = glm::vec4(1.0, 0.0, 0.0, 1.0);

    // Lineas verticales
    Lines* at = ITEngine::getInstancia()->createLine(x,y,-z,x,y,-z/3,col);
    at->setAdditionalPoints(-x,y,-z,-x,y,-z/3);

    // Lineas horizontales
    at->setAdditionalPoints(x,y,-z,-x,y,-z);
    at->setAdditionalPoints(x,y,-z/3,-x,y,-z/3);

    // Lineas de altura
    at->setAdditionalPoints(x,y,-z,x,y/2,-z);
    at->setAdditionalPoints(-x,y,-z,-x,y/2,-z);

    at->setAdditionalPoints(x,y,-z/3,x,y/2,-z/3);
    at->setAdditionalPoints(-x,y,-z/3,-x,y/2,-z/3);

    at->setAdditionalPoints(x,y/2,-z,x,y/2,-z/3);
    at->setAdditionalPoints(-x,y/2,-z,-x,y/2,-z/3);    


    // CENTROCAMPO
    col = glm::vec4(1.0, 1.0, 0.0, 1.0);

    // Lineas verticales
    Lines* ct = ITEngine::getInstancia()->createLine(x,y,-z/3,x,y,z/3,col);
    ct->setAdditionalPoints(-x,y,-z/3,-x,y,z/3);

    // Lineas horizontales
    ct->setAdditionalPoints(x,y,z/3,-x,y,z/3);

    // Lineas de altura
    ct->setAdditionalPoints(x,y,z/3,x,y/2,z/3);
    ct->setAdditionalPoints(-x,y,z/3,-x,y/2,z/3);

    ct->setAdditionalPoints(x,y/2,-z/3,x,y/2,z/3);
    ct->setAdditionalPoints(-x,y/2,-z/3,-x,y/2,z/3);


    // DEFENSA
    col = glm::vec4(0.0, 1.0, 0.0, 1.0);

    // Lineas verticales
    Lines* def = ITEngine::getInstancia()->createLine(x,y,z/3,x,y,z,col);
    def->setAdditionalPoints(-x,y,z/3,-x,y,z);

    // Lineas horizontales
    def->setAdditionalPoints(x,y,z,-x,y,z);

    // Lineas de altura
    def->setAdditionalPoints(x,y,z,x,y/2,z);
    def->setAdditionalPoints(-x,y,z,-x,y/2,z);

    def->setAdditionalPoints(x,y/2,z/3,x,y/2,z);
    def->setAdditionalPoints(-x,y/2,z/3,-x,y/2,z);

}


void GameState::setTextEscenario(){

    // Posicion IA
    std::stringstream ss;
    ss << "X: " << std::fixed << std::setprecision(2) << ia.at(0)->getCoche()->getPosition().x
    << ", Y: " << ia.at(0)->getCoche()->getPosition().y
    << ", Z: " << ia.at(0)->getCoche()->getPosition().z;

    tPosIA->setText(ss.str());

    // Cargas IA
    std::stringstream sc;
    sc << "Cargas: " << ia.at(0)->getCargas();

    tCargasIA->setText(sc.str());

    // Poder IA
    std::stringstream sp;
    sp << "Power: " << ia.at(0)->getPoderes()->getText();

    tPowersIA->setText(sp.str());

    // Estados IA (logica difusa)
    std::stringstream st;
    st << "States: " << ia.at(0)->getEstado() << ", " << ia.at(0)->getEstado2();

    tStatesIA->setText(st.str());


}

void GameState::obtainActualIA(){

    // Tecla para cambiar de jugador

    newState = glfwGetKey(ITEngine::getInstancia()->getWindow(), GLFW_KEY_X);

    if(newState == GLFW_RELEASE && oldState == GLFW_PRESS && ITEngine::getInstancia()->getIsDebugActive()){
        if(ia.size() - 1 > actualIA){
            actualIA++;
        }else
            actualIA = 0;
    }

    oldState = newState;
}

double GameState::FuzzyEstado(double pos, IA* ia){

    FuzzyModule Atacante;
    double primer = 31;
    if(pos+144 >= 288){
        pos = 270-144;
    }
    if(pos+144 <= 0){
        pos = 5-144;
    }
     FuzzyVariable& Deseabilidad = Atacante.CreateFLV("Deseabilidad");

        FzSet Poco = Deseabilidad.AddLeftSet("Poco",0,25,50);
        FzSet Deseable = Deseabilidad.AddTriangleSet("Deseable",25,50,75);
        FzSet Muy = Deseabilidad.AddRightSet("Muy",50,75,100);

        FuzzyVariable& Campo = Atacante.CreateFLV("Campo");
        if(ia->getIsEnemy() == true){
            FzSet Ataque = Campo.AddLeftSet("Ataque",0,72,144);
            FzSet Centro = Campo.AddTriangleSet("Centro",72,144,216);
            FzSet Defensa = Campo.AddRightSet("Defensa",144,216,288);

            Atacante.AddRule(Defensa,Poco);
            Atacante.AddRule(Ataque,Muy);
            Atacante.AddRule(Centro,Deseable);
             Atacante.Fuzzify("Campo", pos+144);
              primer = Atacante.DeFuzzify("Deseabilidad");

        }

        if(ia->getIsEnemy() == false){

            FzSet Defensa = Campo.AddLeftSet("Defensa",0,72,144);
            FzSet Centro = Campo.AddTriangleSet("Centro",72,144,216);
            FzSet Ataque = Campo.AddRightSet("Ataque",144,216,288);
             Atacante.AddRule(Defensa,Poco);
            Atacante.AddRule(Ataque,Muy);
            Atacante.AddRule(Centro,Deseable);
             Atacante.Fuzzify("Campo", pos+144);
              primer = Atacante.DeFuzzify("Deseabilidad");
        }

       


       
        return primer;
}

std::vector<double> GameState::FuzzyNitroso(IA* ia){
    std::vector<double> retorno;
    double cercano = 337;
    FuzzyModule Atacante;

     FuzzyVariable& Campo = Atacante.CreateFLV("Campo");
        
        FzSet Ataque = Campo.AddLeftSet("Ataque",0,72,144);
        FzSet Centro = Campo.AddTriangleSet("Centro",72,144,216);
        FzSet Defensa = Campo.AddRightSet("Defensa",144,216,288);

        FuzzyVariable& Deseabilidad = Atacante.CreateFLV("Deseabilidad");

        FzSet Poco = Deseabilidad.AddLeftSet("Poco",0,25,50);
        FzSet Deseable = Deseabilidad.AddTriangleSet("Deseable",25,50,75);
        FzSet Muy = Deseabilidad.AddRightSet("Muy",50,75,100);

        FuzzyVariable& Distancia = Atacante.CreateFLV("Distancia");
        FzSet MuyC = Distancia.AddLeftSet("MuyC",0,42.25,84.5);
        FzSet Cerca = Distancia.AddTriangleSet("Cerca",45.25,84.5,169);
        FzSet Lejos = Distancia.AddTriangleSet("Lejos",84.5,169,253.5);
        FzSet MuyL = Distancia.AddRightSet("MuyL",169,253.5,338);

        int pos = 0;
            if(ia->getCargas()<3){
                cercano =sqrt(pow(abs((nitros.at(0)->getNode()->getPosition().x) - (ia->getCoche()->getPosition().x)),2) + pow(abs((nitros.at(0)->getNode()->getPosition().z)),2));
                for(int i =0; i<nitros.size();i++){           
                    double calculo = abs(nitros.at(i)->getNode()->getPosition().x - ia->getCoche()->getPosition().x) + abs(nitros.at(i)->getNode()->getPosition().z - ia->getCoche()->getPosition().z);
                    if(nitros.at(i)->getNode()->isVisible() && calculo < cercano){                  
                                cercano = calculo;
                                pos = i;
                    
                    }
                }
            }
            Atacante.Fuzzify("Distancia",cercano);
            Atacante.AddRule(MuyC,Muy);
            Atacante.AddRule(Cerca,Poco);
            Atacante.AddRule(Lejos,Poco);
            Atacante.AddRule(MuyL,Poco);

            double segundo = Atacante.DeFuzzify("Deseabilidad");

            retorno.push_back(pos);
            retorno.push_back(segundo);

        return retorno;
}

std::vector<double> GameState::FuzzyDefensa(IA* ia){
    
    std::vector<double> retorno;

    vec2f porteria;
    porteria.x = 0;
    porteria.y = 144;

    vec2d bola;
    bola.x = Pelota::getInstancia()->getNode()->getPosition().x;
    bola.y = Pelota::getInstancia()->getNode()->getPosition().z;

    FuzzyModule Defensa;
    
    FuzzyVariable& Pos = Defensa.CreateFLV("Pos");

        FzSet Atras = Pos.AddLeftSet("Atras",0,90,100);
        FzSet Lado = Pos.AddTriangleSet("Lado",90,100,110);
        FzSet Delante = Pos.AddRightSet("Delante",100,110,200);

         
    FuzzyVariable& Deseabilidad = Defensa.CreateFLV("Deseabilidad");

        FzSet Poco = Deseabilidad.AddLeftSet("Poco",0,25,50);
        FzSet Deseable = Deseabilidad.AddTriangleSet("Deseable",25,50,75);
        FzSet Muy = Deseabilidad.AddRightSet("Muy",50,75,100);

    FuzzyVariable& Distancia = Defensa.CreateFLV("Distancia");
        
        FzSet MuyC = Distancia.AddLeftSet("MuyC",0,42.25,84.5);
        FzSet Cerca = Distancia.AddTriangleSet("Cerca",45.25,84.5,169);
        FzSet Lejos = Distancia.AddTriangleSet("Lejos",84.5,169,253.5);
        FzSet MuyL = Distancia.AddRightSet("MuyL",169,253.5,338);
    double iaZ = ia->getCoche()->getPosition().z;
    double iaX = ia->getCoche()->getPosition().x;
    double distPelota = abs((bola.x) - (iaX) + abs((bola.y) - (iaZ)));
    double distDelante = (abs(144-ia->getCoche()->getPosition().z) - abs(144-bola.y)) + 100;
    if(distDelante < 0){
        distDelante = 0;
    }
    if(distDelante > 200){
        distDelante = 200;
    }
    double distPort = (abs(135-bola.y) + abs(0-bola.x)) + 100;

    Defensa.Fuzzify("Distancia",distPelota);
    Defensa.Fuzzify("Pos",distDelante);

    FzAND DMC(Delante,MuyC);
    FzAND DC(Delante,Cerca);
    FzAND DL(Delante,Lejos);
    FzAND DML(Delante,MuyL);

    Defensa.AddRule(DMC,Muy);
    Defensa.AddRule(DC,Deseable);
    Defensa.AddRule(DL,Poco);
    Defensa.AddRule(DML,Poco);

    FzAND AMC(Atras,MuyC);
    FzAND AC(Atras,Cerca);
    FzAND AL(Atras,Lejos);
    FzAND AML(Atras,MuyL);

    Defensa.AddRule(AMC,Poco);
    Defensa.AddRule(AC,Poco);
    Defensa.AddRule(AL,Poco);
    Defensa.AddRule(AML,Poco);

    FzAND LMC(Lado,MuyC);
    FzAND LC(Lado,Cerca);
    FzAND LL(Lado,Lejos);
    FzAND LML(Lado,MuyL);

    Defensa.AddRule(LMC,Deseable);
    Defensa.AddRule(LC,Deseable);
    Defensa.AddRule(LL,Poco);
    Defensa.AddRule(LML,Poco);

    double primer = Defensa.DeFuzzify("Deseabilidad");

    Defensa.Fuzzify("Distancia",distPort);
    Defensa.Fuzzify("Pos",distDelante);


    Defensa.AddRule(DMC,Muy);
    Defensa.AddRule(DC,Deseable);
    Defensa.AddRule(DL,Poco);
    Defensa.AddRule(DML,Poco);

    Defensa.AddRule(AMC,Muy);
    Defensa.AddRule(AC,Deseable);
    Defensa.AddRule(AL,Poco);
    Defensa.AddRule(AML,Poco);

    Defensa.AddRule(LMC,Muy);
    Defensa.AddRule(LC,Poco);
    Defensa.AddRule(LL,Poco);
    Defensa.AddRule(LML,Poco);

    double segund = Defensa.DeFuzzify("Deseabilidad");
    //std::cout<<"Primer: "<<primer<<std::endl;
    //std::cout<<"Segund: "<<segund<<std::endl;
    if(primer > segund){
        retorno.push_back(0);
        retorno.push_back(primer);
    }
    else if(segund > primer && segund >= 30){
        retorno.push_back(1);
        retorno.push_back(segund);
    }
    else{
        retorno.push_back(0);
        retorno.push_back(primer);
    }

    return retorno;
}

std::vector<double> GameState::FuzzyAtacar(IA* ia){

    std::vector<double> retorno;

    FuzzyModule Atacante;

        FuzzyVariable& Pos = Atacante.CreateFLV("Pos");

        FzSet Atras = Pos.AddLeftSet("Atras",0,90,100);
        FzSet Lado = Pos.AddTriangleSet("Lado",90,100,110);
        FzSet Delante = Pos.AddRightSet("Delante",100,110,200);

        if(ia->getIsEnemy() == false){
            FzSet Atras = Pos.AddLeftSet("Delante",0,90,100);
            FzSet Lado = Pos.AddTriangleSet("Lado",90,100,110);
            FzSet Delante = Pos.AddRightSet("Atras",100,110,200);
        }

        FuzzyVariable& Deseabilidad = Atacante.CreateFLV("Deseabilidad");

        FzSet Poco = Deseabilidad.AddLeftSet("Poco",0,25,50);
        FzSet Deseable = Deseabilidad.AddTriangleSet("Deseable",25,50,75);
        FzSet Muy = Deseabilidad.AddRightSet("Muy",50,75,100);

        FuzzyVariable& Distancia = Atacante.CreateFLV("Distancia");
        FzSet MuyC = Distancia.AddLeftSet("MuyC",0,42.25,84.5);
        FzSet Cerca = Distancia.AddTriangleSet("Cerca",45.25,84.5,169);
        FzSet Lejos = Distancia.AddTriangleSet("Lejos",84.5,169,253.5);
        FzSet MuyL = Distancia.AddRightSet("MuyL",169,253.5,338);
       
                        
                        
                
            vec2d bola;
            bola.x = Pelota::getInstancia()->getNode()->getPosition().x;
            bola.y = Pelota::getInstancia()->getNode()->getPosition().z;
            double distPelota = abs((bola.x) - (ia->getCoche()->getPosition().x)) + abs((bola.y) - (ia->getCoche()->getPosition().z));
            double distDelante = (abs(144-ia->getCoche()->getPosition().z) - abs(144-bola.y)) + 100;

            Atacante.Fuzzify("Distancia",distPelota);
            Atacante.Fuzzify("Pos",distDelante);

            FzAND DMC(Delante,MuyC);
            FzAND DC(Delante,Cerca);
            FzAND DL(Delante,Lejos);
            FzAND DML(Delante,MuyL);

            Atacante.AddRule(DMC,Muy);
            Atacante.AddRule(DC,Deseable);
            Atacante.AddRule(DL,Poco);
            Atacante.AddRule(DML,Poco);

            FzAND AMC(Atras,MuyC);
            FzAND AC(Atras,Cerca);
            FzAND AL(Atras,Lejos);
            FzAND AML(Atras,MuyL);

            Atacante.AddRule(AMC,Poco);
            Atacante.AddRule(AC,Poco);
            Atacante.AddRule(AL,Poco);
            Atacante.AddRule(AML,Poco);

            FzAND LMC(Lado,MuyC);
            FzAND LC(Lado,Cerca);
            FzAND LL(Lado,Lejos);
            FzAND LML(Lado,MuyL);

            Atacante.AddRule(LMC,Muy);
            Atacante.AddRule(LC,Deseable);
            Atacante.AddRule(LL,Poco);
            Atacante.AddRule(LML,Poco);

            double primer = Atacante.DeFuzzify("Deseabilidad");
            double cercano = 337;
            
            //0 pelota -------- 1 Nitro
           // std::cout<<"Primer: "<<primer<<std::endl;
         
            std::vector<double> nitroso = FuzzyNitroso(ia);
            int pos = nitroso.at(0);
            double segundo = nitroso.at(1);

            if(primer >= segundo){
                retorno.push_back(4.0);
                retorno.push_back(primer);
            }
            else if(segundo< primer){
                 retorno.push_back(pos);        
                 retorno.push_back(segundo);      
            }
            else{
                retorno.push_back(4.0);
                retorno.push_back(primer);
            }
            
            
    return retorno;
}

std::vector<double> GameState::FuzzyDefender(IA* ia){
    std::vector<double> retorno;
    vec2d bola;
        bola.x = Pelota::getInstancia()->getNode()->getPosition().x;
        bola.y = Pelota::getInstancia()->getNode()->getPosition().z;
    double cercPelota = 337;
    double cerRival = 337;
    int rivPos = -1;

    FuzzyModule Atacante;

        FuzzyVariable& Deseabilidad = Atacante.CreateFLV("Deseabilidad");

        FzSet Poco = Deseabilidad.AddLeftSet("Poco",0,25,50);
        FzSet Deseable = Deseabilidad.AddTriangleSet("Deseable",25,50,75);
        FzSet Muy = Deseabilidad.AddRightSet("Muy",50,75,100);

        FuzzyVariable& Distancia = Atacante.CreateFLV("Distancia");
        FzSet MuyC = Distancia.AddLeftSet("MuyC",0,42.25,84.5);
        FzSet Cerca = Distancia.AddTriangleSet("Cerca",45.25,84.5,169);
        FzSet Lejos = Distancia.AddTriangleSet("Lejos",84.5,169,253.5);
        FzSet MuyL = Distancia.AddRightSet("MuyL",169,253.5,338);

        
        if(ia->getTeam()=="red"){
            
            for(int i = 0;i < blue->getPlayers().size(); ++i){
                double calculo = abs(blue->getPlayers().at(i)->getCoche()->getPosition().x - bola.x) + abs(blue->getPlayers().at(i)->getCoche()->getPosition().z - bola.y);
                if(calculo < cercPelota){
                    cercPelota = calculo;
                    rivPos = i;
                }
            }
            cerRival = abs(blue->getPlayers().at(rivPos)->getCoche()->getPosition().x - ia->getCoche()->getPosition().x) + abs(blue->getPlayers().at(rivPos)->getCoche()->getPosition().z - ia->getCoche()->getPosition().z);

        }
        else{

            for(int i = 0;i < red->getPlayers().size(); ++i){
                double calculo = abs(red->getPlayers().at(i)->getCoche()->getPosition().x - bola.x) + abs(red->getPlayers().at(i)->getCoche()->getPosition().z - bola.y);
                if(calculo < cercPelota){
                    cercPelota = calculo;
                    rivPos = i;
                }
            }
            cerRival = abs(red->getPlayers().at(rivPos)->getCoche()->getPosition().x - ia->getCoche()->getPosition().x) + abs(red->getPlayers().at(rivPos)->getCoche()->getPosition().z - ia->getCoche()->getPosition().z);


        }
        if(glfwGetTime() - ia->getCD() < 10){
            cercPelota = 337;
        }

        Atacante.Fuzzify("Distancia",cercPelota);

            Atacante.AddRule(MuyC,Muy);
            Atacante.AddRule(Cerca,Deseable);
            Atacante.AddRule(Lejos,Poco);
            Atacante.AddRule(MuyL,Poco);

        double primer = Atacante.DeFuzzify("Deseabilidad");

        Atacante.Fuzzify("Distancia",cerRival);

            Atacante.AddRule(MuyC,Poco);
            Atacante.AddRule(Cerca,Poco);
            Atacante.AddRule(Lejos,Deseable);
            Atacante.AddRule(MuyL,Muy);

        double segundo = Atacante.DeFuzzify("Deseabilidad");

        double poder = (primer + segundo) /2;

        std::vector<double> nitroso = FuzzyNitroso(ia);
        int pos = nitroso.at(0);
        double nitro = nitroso.at(1);

         Atacante.Fuzzify("Distancia",cercPelota);

            Atacante.AddRule(MuyC,Poco);
            Atacante.AddRule(Cerca,Poco);
            Atacante.AddRule(Lejos,Deseable);
            Atacante.AddRule(MuyL,Muy);

        double cuarto = Atacante.DeFuzzify("Deseabilidad");

        Atacante.Fuzzify("Distancia",cerRival);

            Atacante.AddRule(MuyC,Muy);
            Atacante.AddRule(Cerca,Deseable);
            Atacante.AddRule(Lejos,Poco);
            Atacante.AddRule(MuyL,Poco);

        double quinto = Atacante.DeFuzzify("Deseabilidad");

        double molestar = (cuarto + quinto) / 2;

        if(poder > nitro && poder > molestar){
            retorno.push_back(1);
            retorno.push_back(rivPos);
            retorno.push_back(poder);
        }
        else if(nitro > poder && nitro > molestar){
            retorno.push_back(2);
            retorno.push_back(rivPos);
            retorno.push_back(molestar);
        }
        else if(molestar > poder && molestar > nitro){
            retorno.push_back(3);
            retorno.push_back(pos);
            retorno.push_back(nitro);
        }
        else{
            retorno.push_back(2);
            retorno.push_back(0);
            retorno.push_back(molestar);

        }
    return retorno;
}
void GameState::ResetarPoderes(IA* ia, double pos){

    if(ia->getWho() == 'A'){
        if(ia->getTeam() == "red"){
            ia->getPoderes()->ResetMareo(blue->getPlayers().at(pos));
        }
        else{
            ia->getPoderes()->ResetMareo(red->getPlayers().at(pos));
        }
        ia->setCD();
    }
    else if(ia->getWho() == 'D'){

    }
    else if(ia->getWho() == 'C'){

    }

    ia->setEstado2(Auxiliar::IAstate::DEFAULT);


}

double GameState::FuzzyUsing(IA* ia){

    FuzzyModule Atacante;

        FuzzyVariable& Deseabilidad = Atacante.CreateFLV("Deseabilidad");

        FzSet Poco = Deseabilidad.AddLeftSet("Poco",0,25,50);
        FzSet Deseable = Deseabilidad.AddTriangleSet("Deseable",25,50,75);
        FzSet Muy = Deseabilidad.AddRightSet("Muy",50,75,100);

        FuzzyVariable& Distancia = Atacante.CreateFLV("Distancia");
        FzSet MuyC = Distancia.AddLeftSet("MuyC",0,42.25,84.5);
        FzSet Cerca = Distancia.AddTriangleSet("Cerca",45.25,84.5,169);
        FzSet Lejos = Distancia.AddTriangleSet("Lejos",84.5,169,253.5);
        FzSet MuyL = Distancia.AddRightSet("MuyL",169,253.5,338);


        vec2d bola;
        bola.x = Pelota::getInstancia()->getNode()->getPosition().x;
        bola.y = Pelota::getInstancia()->getNode()->getPosition().z;
        double distPelota = abs((bola.x) - (ia->getCoche()->getPosition().x)) + abs((bola.y) - (ia->getCoche()->getPosition().z));

        Atacante.Fuzzify("Distancia",distPelota);

        Atacante.AddRule(MuyC,Poco);
        Atacante.AddRule(Cerca,Poco);
        Atacante.AddRule(Lejos,Deseable);
        Atacante.AddRule(MuyL,Muy);

        double retorno = Atacante.DeFuzzify("Deseabilidad");

        return retorno;

}