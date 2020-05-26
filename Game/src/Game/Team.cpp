#include "Team.h"

Team::Team(std::vector<Baseplayer*> playersTeam, std::string t){

    score = 0;

    team = playersTeam;
  for(int i=0; i<team.size(); i++){
      if(team.at(i)!=nullptr){
        team.at(i)->setTeam(t);
      }
    }
}

Team::~Team(){

    // Limpiamos el vector del equipo
    team.clear();

}

void Team::respawn(){

    // Hacemos respawn
    for(unsigned int i = 0; i < team.size(); i++){
        if(strcmp(team.at(i)->getTeam().c_str(), "blue")){
            team.at(i)->getCoche()->setRotation(glm::vec3(0,180,0), 0);
        }

        team.at(i)->InitCollide(PhysicsEngine::getInstancia()->getWorld());
    }
}

