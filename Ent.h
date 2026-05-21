#include <SFML/Graphics.hpp>
#include "../Gerenciadores/Gerenciador_Grafico.h"


class Ent{
    protected:
        int id;

        Gerenciador_Grafico* pGG;
    public:
        Ent(int id);
        ~Ent();


};