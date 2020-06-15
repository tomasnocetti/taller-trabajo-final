#ifndef ACTIVE_PLAYERS_H
#define ACTIVE_PLAYERS_H

#include <map>
#include <stdio.h>
#include <mutex>
#include <vector>

#include "../common/BlockingQueue.h"
#include "../DataDefinitions.h"


using UpDateClientsBQ = FixedBlockingQueue<PlayerGameModelData>;

class ActivePlayers{
  private:
    std::map<size_t, UpDateClientsBQ&> models;
    size_t id;
    std::mutex m;
  public:
    explicit ActivePlayers(size_t id);
    ~ActivePlayers();
    ActivePlayers(const ActivePlayers&) = delete;
    ActivePlayers& operator=(const ActivePlayers&) = delete;
    /* Agrega un jugador al mapa con su respectiva BQ, luego de contrastar
    con los datos de los archivos. Si el jugdor ya existe, devuelve su id
    asociado, caso contrario devuelve accede a los archios para dar de alta
    un nuevo jugador, y devuelve el id generado. */
    size_t authenticate(UpDateClientsBQ &clientBQ);
    /* Elimina al jugador del mapa de jugadores activos. */
    void deAuthenticate(size_t id);
    /* Actualiza las colas de los clientes que quiera.
    Va a recibir por parámetro una lista con los jugadores a los que
    quiere pushearles el modelo, y el modelo actualizado. */
    void updateModel(size_t id, PlayerGameModelData playerModel);
    /* Devuelve una lista de los ids jugadores activos. */
    std::vector<size_t> getActivePlayers();
};

#endif
