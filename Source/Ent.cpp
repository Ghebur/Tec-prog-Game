#include "../Ent.h"

Gerenciador_Grafico* Ent::pGG = nullptr;

Ent::Ent(int id) : id(id) {}

Ent::~Ent() {}

void Ent::setGG(Gerenciador_Grafico* pG) { pGG = pG; }