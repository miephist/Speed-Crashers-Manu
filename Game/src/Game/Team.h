#pragma once
#include "../Engines/structs.h"
#include "../Player/Baseplayer.h"

class Team{

    public:

        Team(std::vector<Baseplayer*> playersTeam, std::string t);
        ~Team();

        void respawn();
        void addGoal(){score++;};
        std::vector<Baseplayer*> getPlayers()     {return team;};
        unsigned int getScore() const{return score;};
        

    private:
        
        // Marcador
        unsigned int score;

        // Jugadores
        std::vector<Baseplayer*> team;

};